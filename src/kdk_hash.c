#include "kdk_hash.h"

kdk_uint32 kdk_djb_hash(kdk_char32 *str, kdk_uint32 *res)
{
    kdk_uint32 hash = 5381;

    if(str == KDK_NULL)
        return KDK_NULLPTR;

    while(*str)
        hash = ((hash << 5) + hash) + (*str++);

    *res = hash & 0x7FFFFFFF;

    return KDK_SUCCESS;
}

kdk_hash_node_t *kdk_hash_node_create(kdk_hash_table_t *hash_table, kdk_char32 *key, void *value, kdk_uint32 value_len)
{
    kdk_hash_node_t    *hash_node;

    if(key == KDK_NULL || value == KDK_NULL)
        return KDK_NULL;

    hash_node = (kdk_hash_node_t *)kdk_mem_pool_malloc(hash_table->hash_table_mem_pool, sizeof(kdk_hash_node_t)); 
    if(hash_node == KDK_NULL)
        return KDK_NULL;

    hash_node->hash_node_key = (kdk_char32 *)kdk_mem_pool_malloc(hash_table->hash_table_mem_pool, strlen(key) + 1);
    if(hash_node->hash_node_key == KDK_NULL)
        return KDK_NULL;

    hash_node->hash_node_value = kdk_mem_pool_malloc(hash_table->hash_table_mem_pool, value_len);
    if(hash_node->hash_node_value == KDK_NULL)
        return KDK_NULL;

    memcpy(hash_node->hash_node_key, key, strlen(key));
    memcpy(hash_node->hash_node_value, value, value_len);

    hash_node->hash_node_next = KDK_NULL;

    return hash_node;
}

kdk_hash_table_t  *kdk_hash_table_create(kdk_mem_pool_t *mem_pool, kdk_uint32 prime)
{
    kdk_hash_table_t   *hash_table;
    kdk_uint32      mem_pool_type = 1;

    if(prime == 0)
        return KDK_NULL;

    if(mem_pool == KDK_NULL)
    {
        mem_pool = kdk_mem_pool_create(1024, 1024);
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

    hash_table->hash_table_mem_pool_type = mem_pool_type;
    hash_table->hash_table_prime = prime;
    hash_table->hash_table_count = 0;
    hash_table->hash_table_mem_pool = mem_pool;
    hash_table->hash_table_board = (kdk_hash_node_t *)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_hash_node_t) * prime);
    if(hash_table->hash_table_board == KDK_NULL) 
    {
        kdk_hash_table_destroy(hash_table);  
        return KDK_NULL;
    }

    return hash_table;
}

kdk_uint32 kdk_hash_table_set_value(kdk_hash_table_t *hash_table, kdk_char32 *key, void *value, kdk_uint32 value_len)
{
    kdk_uint32       pos, res; 
    kdk_hash_node_t  *tmp, *new;

    if(hash_table == KDK_NULL || key == KDK_NULL || value == KDK_NULL)
        return KDK_NULLPTR;

    res = kdk_djb_hash(key, &pos);
    if(res)
        return KDK_FAILURE;

    pos = pos % hash_table->hash_table_prime;
    tmp = hash_table->hash_table_board + pos;

/*
    fprintf(stderr, "set key:%s\n", key);
    fprintf(stderr, "set pos:%d\n", pos);
    fprintf(stderr, "set tmp:%p\n", tmp);
*/

    new = kdk_hash_node_create(hash_table, key, value, value_len);
    if(new == KDK_NULL)
        return KDK_FAILURE;

    if(tmp->hash_node_key == KDK_NULL)
    {
        memcpy(tmp, new, sizeof(kdk_hash_node_t));
    }
    else
    {
        new->hash_node_next = tmp->hash_node_next;
        tmp->hash_node_next = new;
    }

    hash_table->hash_table_count++;

    return KDK_SUCCESS;
}

void *kdk_hash_table_get_value(kdk_hash_table_t *hash_table, kdk_char32 *key)
{
    kdk_uint32       pos, res; 
    kdk_hash_node_t  *tmp;

    if(hash_table == KDK_NULL || key == KDK_NULL)
        return KDK_NULL;

    res = kdk_djb_hash(key, &pos);
    if(res)
        return KDK_NULL;

    pos = pos % hash_table->hash_table_prime;
    tmp = hash_table->hash_table_board + pos;
/*
    fprintf(stderr, "get key:%s\n", key);
    fprintf(stderr, "get pos:%d\n", pos);
    fprintf(stderr, "get tmp:%p\n", tmp);
*/

    while(tmp)
    {
        if(tmp->hash_node_key != KDK_NULL && strcmp(tmp->hash_node_key, key) == 0)
            return tmp->hash_node_value;

        tmp = tmp->hash_node_next;
    }

    return KDK_NULL;
}

void kdk_hash_table_destroy(kdk_hash_table_t *hash_table)
{
    if(hash_table == KDK_NULL) 
        return ;

    if(hash_table->hash_table_mem_pool != KDK_NULL && hash_table->hash_table_mem_pool == 0)
    {
        kdk_mem_pool_destroy(hash_table->hash_table_mem_pool);
    }

    return ;
}

void kdk_hash_table_clear(kdk_hash_table_t *hash_table)
{

}

kdk_uint32 kdk_hash_table_print(kdk_hash_table_t *hash_table)
{
    kdk_uint32       i; 
    kdk_hash_node_t  *tmp;

    if(hash_table == KDK_NULL)
        return KDK_NULLPTR;
    
    fprintf(stderr, "=====<print start>=====\n");
    for(i = 0; i < hash_table->hash_table_prime; i++)
    {
        tmp = hash_table->hash_table_board + i;
        if(tmp == KDK_NULL)
            continue;

        fprintf(stderr, "[i:%d]\n", i);
        while(tmp)
        {
            fprintf(stderr, "key:%s", tmp->hash_node_key);
            fprintf(stderr, "\tvalue:%s\n", (kdk_char32 *)tmp->hash_node_value);
            tmp = tmp->hash_node_next;
        }
    }
    fprintf(stderr, "=====<print end>=====\n");

    return KDK_NOTFOUND;
}


/*
int main(int argc, char *argv[])
{
    kdk_hash_table   *hash_table;
    kdk_char32         res;

    hash_table = kdk_HashTableCreate(NULL, 7);
    if(hash_table == KDK_NULL)
    {
        fprintf(stderr, "kdk_HashTableCreate error!\n");
        return KDK_FAILURE;
    }
    
    res = kdk_HashTableSetValue(hash_table, "test", "fortest");
    if(res)
        fprintf(stderr, "set value error!\n");
    
    res = kdk_HashTableSetValue(hash_table, "test1", "fortest1");
    if(res)
        fprintf(stderr, "set value1 error!\n");

    res = kdk_HashTableSetValue(hash_table, "test2", "fortest2");
    if(res)
        fprintf(stderr, "set value2 error!\n");

    res = kdk_HashTableSetValue(hash_table, "test3", "fortest3");
    if(res)
        fprintf(stderr, "set value3 error!\n");

    //kdk_HashTablePrint(hash_table);

    kdk_char32 *tmp;
    kdk_char32 key[30] = "test";
    tmp = kdk_HashTableGetValue(hash_table, key);
    if(tmp == NULL)
        fprintf(stderr, "get value error!\n");
    fprintf(stderr, "test:%s\n", tmp);

    strcat(key, "1");
    tmp = kdk_HashTableGetValue(hash_table, key);
    if(tmp == NULL)
        fprintf(stderr, "get value1 error!\n");
    fprintf(stderr, "test1:%s\n", tmp);

    key[4] = '2';
    tmp = kdk_HashTableGetValue(hash_table, key);
    if(tmp == NULL)
        fprintf(stderr, "get value2 error!\n");
    fprintf(stderr, "test2:%s\n", tmp);

    key[4] = '3';
    tmp = kdk_HashTableGetValue(hash_table, key);
    if(tmp == NULL)
        fprintf(stderr, "get value3 error!\n");
    fprintf(stderr, "test3:%s\n", tmp);

    kdk_HashTableDestroy(hash_table);
    //kdk_HashTablePrint(hash_table);

    return 0;
}
*/
