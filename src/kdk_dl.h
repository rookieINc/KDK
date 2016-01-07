
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

kdk_void *
kdk_dl_open(kdk_char32 *dl_file, kdk_char32 *func_name);

kdk_void 
kdk_dl_close(kdk_void *handle);

#endif /* _KDK_DL_H_INCLUDED_ */
