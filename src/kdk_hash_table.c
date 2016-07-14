
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_hash_table.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 07:42
 * Description : kdk_hash_table.c
 * History     :     
 ***********************************************************/


#include "kdk_hash_table.h"

extern kdk_hash_node_t *hash_node_curr;

static kdk_uint32 
kdk_djb_hash(kdk_char32 *str, kdk_uint32 *res)
{
    kdk_uint32 hash = 5381;

    if(str == KDK_NULL || res == KDK_NULL)
        return KDK_INARG;

    while(*str)
        hash = ((hash << 5) + hash) + (*str++);

    *res = hash & 0x7FFFFFFF;

    return KDK_SUCCESS;
}


static kdk_hash_node_t *
kdk_hash_node_create(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_void *value, kdk_uint32 value_len)
{
    kdk_hash_node_t    *hash_node;

    if(hash_table == KDK_NULL || key == KDK_NULL || value == KDK_NULL || value_len == 0)
        return KDK_NULL;

    hash_node = (kdk_hash_node_t *)kdk_mem_pool_malloc(hash_table->mem_pool, sizeof(kdk_hash_node_t)); 
    if(hash_node == KDK_NULL)
        return KDK_NULL;

    hash_node->key = (kdk_char32 *)kdk_mem_pool_malloc(hash_table->mem_pool, strlen(key) + 1);
    if(hash_node->key == KDK_NULL)
        return KDK_NULL;

    hash_node->value = kdk_mem_pool_malloc(hash_table->mem_pool, value_len + 1);
    if(hash_node->value == KDK_NULL)
        return KDK_NULL;

    hash_node->value_size = value_len + 1;

    memcpy(hash_node->key, key, strlen(key));
    memcpy(hash_node->value, value, value_len);

    hash_node->next = KDK_NULL;

    return hash_node;
}


kdk_hash_table_t  *
kdk_hash_table_create(kdk_mem_pool_t *mem_pool, kdk_uint32 mem_pool_size, kdk_uint32 prime)
{
    kdk_uint32          mem_pool_type = OTHER_MEM_POOL;
    kdk_hash_table_t   *hash_table;
    kdk_hash_node_t   **board;

    if(prime == 0)
        return KDK_NULL;

    if(mem_pool == KDK_NULL)
    {
        mem_pool = kdk_mem_pool_create(mem_pool_size, mem_pool_size);
        if(mem_pool == KDK_NULL)
            return KDK_NULL;
        mem_pool_type = OWN_MEM_POOL;
    }

    //hash_table = (kdk_hash_table *)kdk_malloc(sizeof(kdk_HashTable)); 
    hash_table = (kdk_hash_table_t *)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_hash_table_t)); 
    if(hash_table == KDK_NULL)
    {
        if(mem_pool_type == OWN_MEM_POOL)
        {
            kdk_mem_pool_destroy(mem_pool);
            mem_pool = KDK_NULL;
        }
        return KDK_NULL;
    }

    board = (kdk_hash_node_t **)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_hash_node_t *) * prime);
    if(board == KDK_NULL) 
    {
        kdk_hash_table_destroy(hash_table);  
        hash_table = KDK_NULL;
        return KDK_NULL;
    }

    hash_table->count         = 0;
    hash_table->prime         = prime;
    hash_table->board         = board;
    hash_table->mem_pool      = mem_pool;
    hash_table->mem_pool_type = mem_pool_type;

    return hash_table;
}

kdk_hash_node_t *
kdk_hash_table_get_same_node(kdk_hash_table_t *hash_table, kdk_char32 *key)
{
    kdk_uint32        pos, res; 
    kdk_hash_node_t  *tmp;

    if(hash_table == KDK_NULL || key == KDK_NULL)
        return KDK_NULL;

    res = kdk_djb_hash(key, &pos);
    if(res)
        return KDK_NULL;

    pos = pos % hash_table->prime;
    tmp = *(hash_table->board + pos);

/*
    fprintf(stderr, "get key:%s\n", key);
    fprintf(stderr, "get pos:%d\n", pos);
    fprintf(stderr, "get tmp:%p\n", tmp);
*/

    while(tmp)
    {
        if(tmp->key != KDK_NULL && strcmp(tmp->key, key) == 0)
            return tmp;

        tmp = tmp->next;
    }

    return KDK_NULLFOUND;
}


kdk_uint32 
kdk_hash_table_set_value(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_void *value, kdk_uint32 value_len)
{
    kdk_uint32       pos, res; 
    kdk_hash_node_t  **tmp, *new, *same;

    if(hash_table == KDK_NULL || key == KDK_NULL || value == KDK_NULL || value_len == 0)
        return KDK_INARG;

    res = kdk_djb_hash(key, &pos);
    if(res)
        return res;

    pos = pos % hash_table->prime;
    tmp = hash_table->board + pos;

/*
    fprintf(stderr, "set key:%s\n", key);
    fprintf(stderr, "set pos:%d\n", pos);
    fprintf(stderr, "set tmp:%p\n", tmp);
*/

    same = kdk_hash_table_get_same_node(hash_table, key);

    if(same == KDK_NULL)
        return KDK_FAILURE;

    if(*tmp == KDK_NULL || same == KDK_NULLFOUND)
    {
        new = kdk_hash_node_create(hash_table, key, value, value_len);
        if(new == KDK_NULL)
            return KDK_FAILURE;

        if(*tmp == KDK_NULL)
        {
            *tmp = new;
        }
        else
        {
            new->next    = (*tmp)->next;
            (*tmp)->next = new;
        }

        (hash_table->count)++;

        return KDK_SUCCESS;
    }

    if(value_len < same->value_size)
    {
        memset(same->value, 0, same->value_size);
        memcpy(same->value, value, value_len);
    }
    else
    { 
        same->value = kdk_mem_pool_malloc(hash_table->mem_pool, value_len + 1);
        if(same->value == KDK_NULL)
            return KDK_NULLPTR;

        same->value_size = value_len + 1;
        memcpy(same->value, value, value_len);
    }

    return KDK_SUCCESS;
}


kdk_void *
kdk_hash_table_get_value(kdk_hash_table_t *hash_table, kdk_char32 *key)
{
    kdk_uint32        pos, res; 
    kdk_hash_node_t  *tmp;

    if(hash_table == KDK_NULL || key == KDK_NULL)
        return KDK_NULL;

    res = kdk_djb_hash(key, &pos);
    if(res)
        return KDK_NULL;

    pos = pos % hash_table->prime;
    tmp = *(hash_table->board + pos);

/*
    fprintf(stderr, "get key:%s\n", key);
    fprintf(stderr, "get pos:%d\n", pos);
    fprintf(stderr, "get tmp:%p\n", tmp);
*/

    while(tmp)
    {
        if(tmp->key != KDK_NULL && strcmp(tmp->key, key) == 0)
            return tmp->value;

        tmp = tmp->next;
    }

    return KDK_NULLFOUND;
}

kdk_uint32 
kdk_hash_table_set_string(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_char32 *value)
{
    return kdk_hash_table_set_value(hash_table, key, (kdk_void *)value, strlen(value));
}

kdk_uint32
kdk_hash_table_get_string(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_char32 *value, kdk_uint32 *value_len)
{
    kdk_char32      *offset;
    
    offset = kdk_hash_table_get_value(hash_table, key);
    if(offset == KDK_NULL)
        return KDK_NULLPTR;
    else if(offset == KDK_NULLFOUND)
        return KDK_NOTFOUND;

    strncpy(value, offset, *value_len);
    *value_len = strlen(value);
    
    return KDK_SUCCESS;
}


kdk_uint32 
kdk_hash_table_set_long(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_long32 value)
{
    kdk_char32  str_value[21] = {0};

    snprintf(str_value, 21, "%d", value);

    return kdk_hash_table_set_value(hash_table, key, (kdk_void *)str_value, strlen(str_value));
}

kdk_uint32
kdk_hash_table_get_long(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_long32 *value)
{
    kdk_char32      *offset;
    
    offset = kdk_hash_table_get_value(hash_table, key);
    if(offset == KDK_NULL)
        return KDK_NULLPTR;
    else if(offset == KDK_NULLFOUND)
        return KDK_NOTFOUND;

    *value = atoi(offset);
    
    return KDK_SUCCESS;
}

void
kdk_hash_table_next_reset()
{
    hash_node_curr = KDK_NULL;

    return ;
}

kdk_hash_node_t *
kdk_hash_table_next_node(kdk_hash_table_t *hash_table)
{
    kdk_uint32          pos, ret_code;

    if(hash_table == KDK_NULL)
        return KDK_NULL;

    if(hash_node_curr != KDK_NULL && hash_node_curr->next != KDK_NULL)
    {
        hash_node_curr = hash_node_curr->next;
        return hash_node_curr;
    }
    else
    {
        if(hash_node_curr != KDK_NULL && hash_node_curr->next == KDK_NULL)
        {
            if(hash_node_curr->key == KDK_NULL)
                return KDK_NULL;

            ret_code = kdk_djb_hash(hash_node_curr->key, &pos);
            if(ret_code)
                return KDK_NULL;

            pos = pos % hash_table->prime + 1;

            if(pos >= hash_table->prime)
                return KDK_NULLFOUND;
        }
        else
        {
            pos = 0;
        }

        hash_node_curr = *(hash_table->board + pos);

        while(hash_node_curr == KDK_NULL && pos < hash_table->prime - 1)
        {
            pos++;
            hash_node_curr = *(hash_table->board + pos);
        }

        if(hash_node_curr == KDK_NULL)
            return KDK_NULLFOUND;
        else
            return hash_node_curr;
    }
}

kdk_char32 *
kdk_hash_table_next_key(kdk_hash_table_t *hash_table)
{
    kdk_hash_node_t    *ret_node;

    if(hash_table == KDK_NULL)
        return KDK_NULL;

    ret_node = kdk_hash_table_next_node(hash_table);
    if(ret_node == KDK_NULLFOUND)
        return KDK_NULLFOUND;
    else if(ret_node == KDK_NULL)
        return KDK_NULL;

    return ret_node->key;
}

kdk_void *
kdk_hash_table_next_value(kdk_hash_table_t *hash_table)
{
    kdk_hash_node_t    *ret_node;

    if(hash_table == KDK_NULL)
        return KDK_NULL;

    ret_node = kdk_hash_table_next_node(hash_table);
    if(ret_node == KDK_NULLFOUND)
        return KDK_NULLFOUND;
    else if(ret_node == KDK_NULL)
        return KDK_NULL;

    return ret_node->value;
}


kdk_void 
kdk_hash_table_destroy(kdk_hash_table_t *hash_table)
{
    if(hash_table == KDK_NULL) 
        return ;

    if(hash_table->mem_pool != KDK_NULL && hash_table->mem_pool_type == OWN_MEM_POOL)
    {
        kdk_mem_pool_destroy(hash_table->mem_pool);
        hash_table->mem_pool = KDK_NULL;
    }

    return ;
}
