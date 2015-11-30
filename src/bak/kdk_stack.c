#include "kdk_stack.h"

kdk_stack_node_t *kdk_stack_node_create(kdk_stack_t *stack, kdk_void *value, kdk_uint32 value_len)
{
    kdk_stack_node_t    *stack_node;

    if(stack == KDK_NULL || value == KDK_NULL)
        return KDK_NULL;

    stack_node = (kdk_stack_node_t *)kdk_mem_pool_malloc(stack->stack_mem_pool, sizeof(kdk_stack_node_t)); 
    if(stack_node == KDK_NULL)
        return KDK_NULL;

    stack_node->stack_node_value = kdk_mem_pool_malloc(stack->stack_mem_pool, value_len);
    if(stack_node->stack_node_value == KDK_NULL)
        return KDK_NULL;

    memcpy(stack_node->stack_node_value, value, value_len);

    stack_node->stack_node_next = KDK_NULL;

    return stack_node;
}

kdk_stack_t *kdk_stack_create(kdk_mem_pool_t *mem_pool)
{
    kdk_stack_t        *stack;
    kdk_uint32          mem_pool_type = 1;

    if(mem_pool == KDK_NULL)
    {
        mem_pool = kdk_mem_pool_create(1024, 1024);
        if(mem_pool == KDK_NULL)
            return KDK_NULL;
        mem_pool_type = 0;
    }

    stack = (kdk_stack_t *)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_stack_t)); 
    if(stack == KDK_NULL)
    {
        if(mem_pool_type == 0)
            kdk_mem_pool_destroy(mem_pool);
        return KDK_NULL;
    }

    stack->stack_mem_pool_type = mem_pool_type;
    stack->stack_count = 0;
    stack->stack_mem_pool = mem_pool;
    stack->stack_node_list = KDK_NULL;

    return stack;
}

kdk_int32 kdk_stack_push(kdk_stack_t *stack, kdk_void *value, kdk_uint32 value_len)
{
    kdk_stack_node_t    *new;

    if(stack == KDK_NULL || value == KDK_NULL) 
        return KDK_NULLPTR;

    new = kdk_stack_node_create(stack, value, value_len);
    if(new == KDK_NULL)
        return KDK_FAILURE;

    new->stack_node_next = stack->stack_node_list;
    stack->stack_node_list = new;

    stack->stack_count++;

    return KDK_SUCCESS;
}

kdk_void *kdk_stack_pop(kdk_stack_t *stack)
{
    kdk_stack_node_t    *result;

    if(stack == KDK_NULL)
        return KDK_NULL;

    if(stack->stack_count == 0 || stack->stack_node_list == KDK_NULL)
        return KDK_NULL;

    result = stack->stack_node_list;
    stack->stack_node_list = stack->stack_node_list->stack_node_next;

    stack->stack_count--;

    return result->stack_node_value;
}

kdk_void *kdk_stack_snoop(kdk_stack_t *stack)
{
    kdk_stack_node_t    *result;

    if(stack == KDK_NULL)
        return KDK_NULL;

    if(stack->stack_count == 0 || stack->stack_node_list == KDK_NULL)
        return KDK_NULL;

    result = stack->stack_node_list;

    return result->stack_node_value;
}

kdk_void kdk_stack_destroy(kdk_stack_t *stack)
{
    if(stack == KDK_NULL) 
        return ;

    if(stack->stack_mem_pool != KDK_NULL && stack->stack_mem_pool == 0)
        kdk_mem_pool_destroy(stack->stack_mem_pool);

    return ;
}
