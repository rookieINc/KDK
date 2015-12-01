
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_hash.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 07:44
 * Description : kdk_hash.h
 * History     :     
 ***********************************************************/


#ifndef _KDK_HASH_H_INCLUDED_
#define _KDK_HASH_H_INCLUDED_

#include "kdk_base.h"
#include "kdk_mem_pool.h"

struct kdk_hash_node_s
{
    kdk_char32              *key;
    kdk_void                *value;
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

static kdk_uint32          
kdk_djb_hash(kdk_char32 *str, kdk_uint32 *res);

static kdk_hash_node_t *   
kdk_hash_node_create(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_void *value, kdk_uint32 value_len);

kdk_hash_table_t *  
kdk_hash_table_create(kdk_mem_pool_t *mem_pool, kdk_uint32 mem_pool_size, kdk_uint32 prime);

kdk_uint32          
kdk_hash_table_set_value(kdk_hash_table_t *hash_table, kdk_char32 *key, kdk_void *value, kdk_uint32 value_len);

kdk_void *              
kdk_hash_table_get_value(kdk_hash_table_t *hash_table, kdk_char32 *key);

kdk_void                
kdk_hash_table_destroy(kdk_hash_table_t *hash_table);

#endif /* _KDK_HASH_H_INCLUDED_ */
