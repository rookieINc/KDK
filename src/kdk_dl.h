
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_dl.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-01-07 21:19
 * Description : kdk_dl.h
 * History     : 
 ***********************************************************/


#ifndef _KDK_DL_H_INCLUDED_
#define _KDK_DL_H_INCLUDED_

#include "kdk_base.h"
#include "kdk_mem_pool.h"
#include "kdk_hash_table.h"

#define FUNC_NAME_LEN   48

struct kdk_dl_handle_s
{
    kdk_void   *handle;
    kdk_void   *func;
    kdk_char32  func_name[FUNC_NAME_LEN + 1];
};

typedef struct kdk_dl_handle_s kdk_dl_handle_t;

struct kdk_dl_handle_coll_s
{
    kdk_uint32                mem_pool_type;
    struct kdk_mem_pool_s    *mem_pool;
    struct kdk_hash_table_s  *coll;
};

typedef struct kdk_dl_handle_coll_s kdk_dl_handle_coll_t;


kdk_uint32
kdk_dl_open(kdk_char32 *dl_file, kdk_char32 *func_name, kdk_dl_handle_t *dl_handle);

kdk_void 
kdk_dl_close(kdk_dl_handle_t *dl_handle);

kdk_dl_handle_coll_t *
kdk_dl_handle_coll_create(kdk_mem_pool_t *mem_pool, kdk_uint32 mem_pool_size);

kdk_uint32
kdk_dl_handle_coll_set(kdk_dl_handle_coll_t *dl_handle_coll, kdk_char32 *dl_file, kdk_char32 *func_name);

kdk_uint32
kdk_dl_handle_coll_get(kdk_dl_handle_coll_t *dl_handle_coll, kdk_char32 *func_name, kdk_dl_handle_t *dl_handle);

kdk_void
kdk_dl_handle_coll_destroy(kdk_dl_handle_coll_t *dl_handle_coll);

#endif /* _KDK_DL_H_INCLUDED_ */
