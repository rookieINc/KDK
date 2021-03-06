
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_hash_table.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 07:44
 * Description : kdk_hash_table.h
 * History     :     
 ***********************************************************/


#ifndef _KDK_HASH_TABLE_H_INCLUDED_
#define _KDK_HASH_TABLE_H_INCLUDED_

#include "kdk_base.h"
#include "kdk_mem_pool.h"

#define kdk_hash_table_get_string_array(hash_table, key, value) _kdk_hash_table_get_string_array(hash_table, key, value, sizeof(value) - 1)

struct kdk_hash_node_s
{
    kdk_char32              *key;
    kdk_void                *value;
    kdk_uint32               value_size;
    struct kdk_hash_node_s  *next;
};

typedef struct kdk_hash_node_s kdk_hash_node_t;

struct kdk_hash_table_s
{
    kdk_uint32        prime;
    kdk_uint32        count;
    kdk_uint32        mem_pool_type; //0:new 1:from the hell
    kdk_mem_pool_t   *mem_pool;
    kdk_hash_node_t **board;
};

typedef struct kdk_hash_table_s kdk_hash_table_t;

kdk_hash_node_t  *hash_node_curr;

kdk_hash_table_t *  
kdk_hash_table_create(kdk_mem_pool_t *mem_pool, kdk_uint32 mem_pool_size, kdk_uint32 prime);

kdk_uint32          
kdk_hash_table_set_value(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_void *value, kdk_uint32 value_len);

kdk_void *              
kdk_hash_table_get_same_value(kdk_hash_table_t *hash_table, kdk_char32 *key);

kdk_hash_node_t *              
kdk_hash_table_get_node(kdk_hash_table_t *hash_table, kdk_char32 *key);

kdk_void *              
kdk_hash_table_get_value(kdk_hash_table_t *hash_table, kdk_char32 *key);

void
kdk_hash_table_next_reset();

kdk_hash_node_t *
kdk_hash_table_next_node(kdk_hash_table_t *hash_table);

kdk_char32 *              
kdk_hash_table_next_key(kdk_hash_table_t *hash_table);

kdk_void *              
kdk_hash_table_next_value(kdk_hash_table_t *hash_table);

kdk_void                
kdk_hash_table_destroy(kdk_hash_table_t *hash_table);


kdk_uint32          
kdk_hash_table_set_string(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_char32 *value);

kdk_uint32
kdk_hash_table_get_string(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_char32 *value, kdk_uint32 *value_len);

kdk_uint32
_kdk_hash_table_get_string_array(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_char32 *value, kdk_uint32 value_len);

kdk_uint32          
kdk_hash_table_set_long(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_long32 value);

kdk_uint32          
kdk_hash_table_get_long(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_long32 *value);

#endif /* _KDK_HASH_TABLE_H_INCLUDED_ */
