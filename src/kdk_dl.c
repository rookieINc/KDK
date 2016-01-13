
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_dl.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-01-13 16:41
 * Description : kdk_dl.c
 * History     : 
 ***********************************************************/


#include "kdk_dl.h"


kdk_uint32
kdk_dl_open(kdk_char32 *dl_file, kdk_char32 *func_name, kdk_dl_handle_t *dl_handle)
{
    kdk_void    *handle;

    if(dl_file == KDK_NULL || func_name == KDK_NULL || dl_handle == KDK_NULL)
        return KDK_INARG;

    memset(dl_handle, 0, sizeof(kdk_dl_handle_t));

    strncpy(dl_handle->func_name, func_name, FUNC_NAME_LEN);

    dl_handle->handle = dlopen(dl_file, RTLD_NOW | RTLD_GLOBAL);
    if(dl_handle->handle == KDK_NULL)
        return KDK_NULLPTR;

    dl_handle->func = dlsym(dl_handle->handle, func_name);
    if(dl_handle->func == KDK_NULL)
        return KDK_FAILURE;

    return KDK_SUCCESS;
}


kdk_void 
kdk_dl_close(kdk_dl_handle_t *dl_handle)
{
    if(dl_handle == KDK_NULL)
        return ;

    if(dl_handle->handle != KDK_NULL)
        dlclose(dl_handle->handle);

    memset(dl_handle, 0, sizeof(kdk_dl_handle_t));

    return ;
}


kdk_dl_handle_collection_t *
kdk_dl_handle_collection_create(kdk_mem_pool_t *mem_pool, kdk_uint32 mem_pool_size)
{
    kdk_uint32                      mem_pool_type = OTHER_MEM_POOL;
    kdk_dl_handle_collection_t     *collection;

    if(mem_pool == KDK_NULL)
    {
        mem_pool = kdk_mem_pool_create(mem_pool_size, mem_pool_size);
        if(mem_pool == KDK_NULL)
            return KDK_NULL;
        mem_pool_type = OWN_MEM_POOL;
    }

    collection = (kdk_dl_handle_collection_t *)kdk_mem_pool_malloc(mem_pool, sizeof(kdk_dl_handle_collection_t));
    if(collection == KDK_NULL)
    {
        if(mem_pool_type == OWN_MEM_POOL)
            kdk_mem_pool_destroy(mem_pool);
        return KDK_NULL;
    }

    collection->mem_pool_type = mem_pool_type;
    collection->mem_pool      = mem_pool;
    collection->dl_handle_collection = kdk_hash_table_create(collection->mem_pool, 0, 103);
    if(collection->dl_handle_collection == KDK_NULL)
    {
        kdk_dl_handle_collection_destroy(collection);
        return KDK_NULL;
    }

    return collection;
}


kdk_uint32
kdk_dl_handle_collection_set(kdk_char32 *dl_file, kdk_char32 *func_name, kdk_dl_handle_collection_t *collection)
{
    kdk_uint32          ret_code;
    kdk_dl_handle_t    *dl_handle;

    if(collection == KDK_NULL)
        return KDK_INARG;

    dl_handle = (kdk_dl_handle_t *)kdk_mem_pool_malloc(collection->mem_pool, sizeof(kdk_dl_handle_t));
    if(dl_handle == KDK_NULL)
        return KDK_NULLPTR;
    
    ret_code = kdk_dl_open(dl_file, func_name, dl_handle);
    if(ret_code)
        return KDK_FAILURE;

    return kdk_hash_table_set_value(collection->dl_handle_collection, func_name, dl_handle, sizeof(kdk_dl_handle_t));
}


kdk_uint32
kdk_dl_handle_collection_get(kdk_dl_handle_collection_t *collection, kdk_char32 *func_name, kdk_dl_handle_t *dl_handle)
{
    kdk_dl_handle_t     *ret_dl_handle;

    if(collection == KDK_NULL || func_name == KDK_NULL || dl_handle == KDK_NULL)
        return KDK_INARG;

    ret_dl_handle = kdk_hash_table_get_value(collection->dl_handle_collection, func_name);    
    if(ret_dl_handle == KDK_NULL)
        return KDK_NULLPTR; 
    else if(ret_dl_handle == KDK_NULLFOUND)
        return KDK_NOTFOUND;

    memcpy(dl_handle, ret_dl_handle, sizeof(kdk_dl_handle_t));

    return KDK_SUCCESS;
}


kdk_void
kdk_dl_handle_collection_destroy(kdk_dl_handle_collection_t *collection)
{
    kdk_dl_handle_t     *dl_handle;

    if(collection == KDK_NULL)
        return ;

    dl_handle = kdk_hash_table_next_value(collection->dl_handle_collection);

    while(dl_handle != KDK_NULLFOUND)
    {
        kdk_dl_close(dl_handle);
        dl_handle = kdk_hash_table_next_value(collection->dl_handle_collection);
    }

    kdk_hash_table_destroy(collection->dl_handle_collection);

    kdk_mem_pool_destroy(collection->mem_pool);

    return ;
}
