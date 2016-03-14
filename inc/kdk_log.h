
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_log.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-02-01 14:05
 * Description : kdk_log.h
 * History     : 
 ***********************************************************/


#ifndef _KDK_LOG_H_INCLUDED_
#define _KDK_LOG_H_INCLUDED_

#include "kdk_base.h"
#include "kdk_time.h"

struct kdk_log_s
{
    kdk_file               *file_handle;
    kdk_uint32              mask;
    kdk_uint32              level;
    kdk_char32              file_path[65];
    kdk_char32              file_name[65];
    kdk_char32              file_date[9];
    kdk_char32              file_last[2];
};

typedef struct kdk_log_s kdk_log_t;

#define LOG_INIT {KDK_NULL, 0, 0, {0}, {0}, {0}, {'A', '\0'}}

static kdk_log_t stc_log = LOG_INIT;

static kdk_uint32
kdk_log_check_file_size(kdk_file *file_handle, kdk_uint32 size);

static kdk_uint32
kdk_log_set_file_date(kdk_log_t *log);

static kdk_uint32
kdk_log_set_file_last(kdk_log_t *log);

static kdk_uint32
kdk_log_set_file_handle_(kdk_log_t *log);

static kdk_uint32
kdk_log_set_file_handle(kdk_log_t *log);

kdk_uint32
kdk_log_init(kdk_uint32 mask, kdk_uint32 level, kdk_char32 *file_path, kdk_char32 *file_name);

kdk_void
kdk_log_destroy();


#endif /* _KDK_LOG_H_INCLUDED_ */
