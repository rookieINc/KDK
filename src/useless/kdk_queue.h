#include "kdk.h"

#ifndef __KDK_QUEUE_H__
#define __KDK_QUEUE_H__

struct kdk_queue_node_s
{
    kdk_void                *queue_node_value;
    struct kdk_queue_node_s *queue_node_next;
};

typedef struct kdk_queue_node_s kdk_queue_node_t;

struct kdk_queue_s
{
    kdk_uint32          queue_count;
    kdk_queue_node_t   *queue_node_list;
    kdk_queue_node_t   *queue_node_last;
    kdk_uint32          queue_mem_pool_type;
    kdk_mem_pool_t     *queue_mem_pool;
};

typedef struct kdk_queue_s kdk_queue_t;

kdk_queue_node_t *kdk_queue_node_create(kdk_queue_t *queue, kdk_void *value, kdk_uint32 value_len);
kdk_queue_t *kdk_queue_create(kdk_mem_pool_t *mem_pool);
kdk_int32 kdk_queue_in(kdk_queue_t *queue, kdk_void *value, kdk_uint32 value_len);
kdk_void *kdk_queue_out(kdk_queue_t *queue);
kdk_void *kdk_queue_snoop(kdk_queue_t *queue);
kdk_void kdk_queue_destroy(kdk_queue_t *queue);

#endif
