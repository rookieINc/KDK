
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

#define LOG_LINE_SIZE   257

enum
{
    KDK_LOG_LEVEL_DEBUG = 0x00,
    KDK_LOG_LEVEL_INFO  = 0x01,
    KDK_LOG_LEVEL_WARN  = 0x02,
    KDK_LOG_LEVEL_ERROR = 0x03
};

kdk_uint32
kdk_log_init(kdk_uint32 mask, kdk_uint32 level, kdk_char32 *file_path, kdk_char32 *file_name);

kdk_uint32
kdk_log_write(kdk_uint32 level, kdk_char32 *file, kdk_uint32 line, kdk_char32 *fmt, ...);

kdk_void
kdk_log_destroy();


#define PRELOG(level)     KDK_LOG_LEVEL_##level, __FILE__, __LINE__

#define KLOG(level, ...)  kdk_log_write(PRELOG(level), __VA_ARGS__)


#endif /* _KDK_LOG_H_INCLUDED_ */
