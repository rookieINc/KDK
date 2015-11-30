#ifndef __KDK_HASH_H__
#define __KDK_HASH_H__

#include "kdk.h"

struct kdk_hash_node_s
{
    kdk_char32              *hash_node_key;
    kdk_void                *hash_node_value;
    struct kdk_hash_node_s  *hash_node_next;
};

typedef struct kdk_hash_node_s kdk_hash_node_t;

struct kdk_hash_table_s
{
    kdk_uint32       hash_table_mem_pool_type; //0:new 1:from the hell
    kdk_uint32       hash_table_prime;
    kdk_uint32       hash_table_count;
    kdk_hash_node_t *hash_table_board;
    kdk_mem_pool_t  *hash_table_mem_pool;
};

typedef struct kdk_hash_table_s kdk_hash_table_t;

kdk_uint32          kdk_djb_hash(kdk_char32 *str, kdk_uint32 *res);
kdk_hash_node_t *   kdk_hash_node_create(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_void *value, kdk_uint32 value_len);
kdk_hash_table_t *  kdk_hash_table_create(kdk_mem_pool_t *mem_pool, kdk_uint32 prime);
kdk_uint32          kdk_hash_table_set_value(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_void *value, kdk_uint32 value_len);
kdk_void *              kdk_hash_table_get_value(kdk_hash_table_t *hash_table, kdk_char32 *key);
kdk_void                kdk_hash_table_destroy(kdk_hash_table_t *hash_table);
kdk_void                kdk_hash_table_clear(kdk_hash_table_t *hash_table);
kdk_uint32          kdk_hash_table_print(kdk_hash_table_t *hash_table);

#endif
