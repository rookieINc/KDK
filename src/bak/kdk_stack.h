#include "kdk.h"

#ifndef __KDK_STACK_H__
#define __KDK_STACK_H__

struct kdk_stack_node_s
{
    kdk_void                *stack_node_value;
    struct kdk_stack_node_s *stack_node_next;
};

typedef struct kdk_stack_node_s kdk_stack_node_t;

struct kdk_stack_s
{
    kdk_uint32          stack_count;
    kdk_stack_node_t   *stack_node_list;
    kdk_uint32          stack_mem_pool_type;
    kdk_mem_pool_t     *stack_mem_pool;
};

typedef struct kdk_stack_s kdk_stack_t;

kdk_stack_node_t *kdk_stack_node_create(kdk_stack_t *stack, kdk_void *value, kdk_uint32 value_len);
kdk_stack_t *kdk_stack_create(kdk_mem_pool_t *mem_pool);
kdk_int32 kdk_stack_push(kdk_stack_t *stack, kdk_void *value, kdk_uint32 value_len);
kdk_void *kdk_stack_pop(kdk_stack_t *stack);
kdk_void *kdk_stack_snoop(kdk_stack_t *stack);
kdk_void kdk_stack_destroy(kdk_stack_t *stack);

#endif
