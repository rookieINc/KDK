#include "kdk.h"

#ifndef __KDK_LIST_H__
#define __KDK_LIST_H__

struct kdk_list_node_s
{
    kdk_void                *list_node_value;
    struct kdk_list_node_s  *list_node_next;
    struct kdk_list_node_s  *list_node_pre;
};

typedef struct kdk_list_node_s kdk_list_node_t;

struct kdk_list_s
{
    kdk_uint32          list_count;
    kdk_list_node_t    *list_node_list;
    kdk_uint32          list_mem_pool_type;
    kdk_mem_pool_t     *list_mem_pool;
};

typedef struct kdk_list_s kdk_list_t;

kdk_list_node_t *kdk_list_node_create(kdk_list_t *list, kdk_void *value, kdk_uint32 value_len);
kdk_list_t *kdk_list_create(kdk_mem_pool_t *mem_pool);
kdk_int32 kdk_list_add(kdk_list_t *list, kdk_void *value, kdk_uint32 value_len);
kdk_int32 kdk_list_delete(kdk_list_t *list, kdk_void *value, kdk_uint32 value_len);
kdk_void kdk_list_destroy(kdk_list_t *list);

#endif
