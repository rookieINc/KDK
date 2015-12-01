
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_malloc.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 07:14
 * Description : kdk_malloc.h
 * History     :     
 ***********************************************************/


#ifndef _KDK_MALLOC_H_INCLUDED_
#define _KDK_MALLOC_H_INCLUDED_

#include "kdk_base.h"

kdk_void *
kdk_malloc(kdk_uint32 size);

kdk_void  
kdk_free(kdk_void *ptr);

#endif /* _KDK_MALLO_H_INCLUDED_ */
