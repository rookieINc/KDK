
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName:    kdk_hash.c
 * Author:      rookieINc
 * Version:     v0.1.0
 * Date:        2015-12-01 07:42
 * Description: kdk_hash.c
 * History:     
 ***********************************************************/


#include "kdk_hash.h"

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

    hash_node->value = kdk_mem_pool_malloc(hash_table->mem_pool, value_len);
    if(hash_node->value == KDK_NULL)
        return KDK_NULL;

    memcpy(hash_node->key, key, strlen(key));
    memcpy(hash_node->value, value, value_len);

    hash_node->next = KDK_NULL;

    return hash_node;
}

kdk_hash_table_t  *
kdk_hash_table_create(kdk_mem_pool_t *mem_pool, kdk_uint32 mem_pool_size, kdk_uint32 prime)
{
    kdk_uint32          mem_pool_type = 1;
    kdk_hash_table_t   *hash_table;
    kdk_hash_node_t   **board;

    if(prime == 0 || mem_pool_size == 0)
        return KDK_NULL;

    if(mem_pool == KDK_NULL)
    {
        mem_pool = kdk_mem_pool_create(mem_pool_size, mem_pool_size);
        if(mem_pool == KDK_NULL)
            return KDK_NULL;
        mem_pool_type = 0;
    }

    //hash_table = (kdk_hash_table *)kdk_malloc(sizeof(kdk_HashTable)); 
    hash_table = (kdk_hash_table_t *)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_hash_table_t)); 
    if(hash_table == KDK_NULL)
    {
        if(mem_pool_type == 0)
            kdk_mem_pool_destroy(mem_pool);
        return KDK_NULL;
    }

    board = (kdk_hash_node_t **)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_hash_node_t *) * prime);
    if(board == KDK_NULL) 
    {
        kdk_hash_table_destroy(hash_table);  
        return KDK_NULL;
    }

    hash_table->prime = prime;
    hash_table->count = 0;
    hash_table->mem_pool_type = mem_pool_type;
    hash_table->mem_pool = mem_pool;
    hash_table->board = board;

    return hash_table;
}

kdk_uint32 
kdk_hash_table_set_value(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_void *value, kdk_uint32 value_len)
{
    kdk_uint32       pos, res; 
    kdk_hash_node_t  *tmp, *new;

    if(hash_table == KDK_NULL || key == KDK_NULL || value == KDK_NULL || value_len == 0)
        return KDK_INARG;

    res = kdk_djb_hash(key, &pos);
    if(res)
        return res;

    pos = pos % hash_table->prime;
    tmp = *(hash_table->board + pos);

/*
    fprintf(stderr, "set key:%s\n", key);
    fprintf(stderr, "set pos:%d\n", pos);
    fprintf(stderr, "set tmp:%p\n", tmp);
*/

    new = kdk_hash_node_create(hash_table, key, value, value_len);
    if(new == KDK_NULL)
        return KDK_FAILURE;

    if(tmp->key == KDK_NULL)
    {
        *tmp = *new;
    }
    else
    {
        new->next = tmp->next;
        tmp->next = new;
    }

    hash_table->count++;

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

    return KDK_NULL;
}

kdk_void 
kdk_hash_table_destroy(kdk_hash_table_t *hash_table)
{
    if(hash_table == KDK_NULL) 
        return ;

    if(hash_table->mem_pool != KDK_NULL && hash_table->mem_pool == 0)
    {
        kdk_mem_pool_destroy(hash_table->mem_pool);
    }

    return ;
}
