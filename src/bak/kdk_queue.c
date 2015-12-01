#include "kdk_queue.h"

kdk_queue_node_t *kdk_queue_node_create(kdk_queue_t *queue, kdk_void *value, kdk_uint32 value_len)
{
    kdk_queue_node_t    *queue_node;

    if(queue == KDK_NULL || value == KDK_NULL)
        return KDK_NULL;

    queue_node = (kdk_queue_node_t *)kdk_mem_pool_malloc(queue->queue_mem_pool, sizeof(kdk_queue_node_t)); 
    if(queue_node == KDK_NULL)
        return KDK_NULL;

    queue_node->queue_node_value = kdk_mem_pool_malloc(queue->queue_mem_pool, value_len);
    if(queue_node->queue_node_value == KDK_NULL)
        return KDK_NULL;

    memcpy(queue_node->queue_node_value, value, value_len);

    queue_node->queue_node_next = KDK_NULL;

    return queue_node;
}

kdk_queue_t *kdk_queue_create(kdk_mem_pool_t *mem_pool)
{
    kdk_queue_t        *queue;
    kdk_uint32          mem_pool_type = 1;

    if(mem_pool == KDK_NULL)
    {
        mem_pool = kdk_mem_pool_create(1024, 1024);
        if(mem_pool == KDK_NULL)
            return KDK_NULL;
        mem_pool_type = 0;
    }

    queue = (kdk_queue_t *)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_queue_t)); 
    if(queue == KDK_NULL)
    {
        if(mem_pool_type == 0)
            kdk_mem_pool_destroy(mem_pool);
        return KDK_NULL;
    }

    queue->queue_mem_pool_type = mem_pool_type;
    queue->queue_count = 0;
    queue->queue_mem_pool = mem_pool;
    queue->queue_node_list = KDK_NULL;
    queue->queue_node_last = KDK_NULL;

    return queue;
}

kdk_int32 kdk_queue_in(kdk_queue_t *queue, kdk_void *value, kdk_uint32 value_len)
{
    kdk_queue_node_t    *new;

    if(queue == KDK_NULL || value == KDK_NULL) 
        return KDK_NULLPTR;

    new = kdk_queue_node_create(queue, value, value_len);
    if(new == KDK_NULL)
        return KDK_FAILURE;

    if(queue->queue_node_last == KDK_NULL)
        queue->queue_node_list = new;
    else
        queue->queue_node_last->queue_node_next = new;

    queue->queue_node_last = new;
    queue->queue_count++;

    return KDK_SUCCESS;
}

kdk_void *kdk_queue_out(kdk_queue_t *queue)
{
    kdk_queue_node_t    *result;

    if(queue == KDK_NULL)
        return KDK_NULL;

    if(queue->queue_count == 0 || queue->queue_node_list == KDK_NULL)
        return KDK_NULL;

    result = queue->queue_node_list;
    queue->queue_node_list = queue->queue_node_list->queue_node_next;

    queue->queue_count--;

    return result->queue_node_value;
}

kdk_void *kdk_queue_snoop(kdk_queue_t *queue)
{
    kdk_queue_node_t    *result;

    if(queue == KDK_NULL)
        return KDK_NULL;

    if(queue->queue_count == 0 || queue->queue_node_list == KDK_NULL)
        return KDK_NULL;

    result = queue->queue_node_list;

    return result->queue_node_value;
}

kdk_void kdk_queue_destroy(kdk_queue_t *queue)
{
    if(queue == KDK_NULL) 
        return ;

    if(queue->queue_mem_pool != KDK_NULL && queue->queue_mem_pool_type == 0)
        kdk_mem_pool_destroy(queue->queue_mem_pool);

    return ;
}
