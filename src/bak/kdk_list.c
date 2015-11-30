#include "kdk_list.h"

kdk_list_node_t *kdk_list_node_create(kdk_list_t *list, kdk_void *value, kdk_uint32 value_len)
{
    kdk_list_node_t    *list_node;

    if(list == KDK_NULL || value == KDK_NULL)
        return KDK_NULL;

    list_node = (kdk_list_node_t *)kdk_mem_pool_malloc(list->list_mem_pool, sizeof(kdk_list_node_t)); 
    if(list_node == KDK_NULL)
        return KDK_NULL;

    list_node->list_node_value = kdk_mem_pool_malloc(list->list_mem_pool, value_len);
    if(list_node->list_node_value == KDK_NULL)
        return KDK_NULL;

    memcpy(list_node->list_node_value, value, value_len);

    list_node->list_node_next = KDK_NULL;

    return list_node;
}

kdk_list_t *kdk_list_create(kdk_mem_pool_t *mem_pool)
{
    kdk_list_t        *list;
    kdk_uint32          mem_pool_type = 1;

    if(mem_pool == KDK_NULL)
    {
        mem_pool = kdk_mem_pool_create(1024, 1024);
        if(mem_pool == KDK_NULL)
            return KDK_NULL;
        mem_pool_type = 0;
    }

    list = (kdk_list_t *)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_list_t)); 
    if(list == KDK_NULL)
    {
        if(mem_pool_type == 0)
            kdk_mem_pool_destroy(mem_pool);
        return KDK_NULL;
    }

    list->list_mem_pool_type = mem_pool_type;
    list->list_count = 0;
    list->list_mem_pool = mem_pool;
    list->list_node_list = KDK_NULL;

    return list;
}

kdk_int32 kdk_list_add(kdk_list_t *list, kdk_void *value, kdk_uint32 value_len)
{
    kdk_list_node_t    *new;

    if(list == KDK_NULL || value == KDK_NULL) 
        return KDK_NULLPTR;

    new = kdk_list_node_create(list, value, value_len);
    if(new == KDK_NULL)
        return KDK_FAILURE;

    new->list_node_next = list->list_node_list;
    list->list_node_list = new;

    list->list_count++;

    return KDK_SUCCESS;
}

kdk_void *kdk_list_delete(kdk_list_t *list)
{
    kdk_list_node_t    *result;

    if(list == KDK_NULL)
        return KDK_NULL;

    if(list->list_count == 0 || list->list_node_list == KDK_NULL)
        return KDK_NULL;

    result = list->list_node_list;
    list->list_node_list = list->list_node_list->list_node_next;

    list->list_count--;

    return result->list_node_value;
}

kdk_void kdk_list_destroy(kdk_list_t *list)
{
    if(list == KDK_NULL) 
        return ;

    if(list->list_mem_pool != KDK_NULL && list->list_mem_pool == 0)
        kdk_mem_pool_destroy(list->list_mem_pool);

    return ;
}
