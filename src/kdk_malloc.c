
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_malloc.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 16:47
 * Description : kdk_malloc.c
 * History     :     
 ***********************************************************/


#include "kdk_malloc.h"

kdk_void *
kdk_malloc(kdk_uint32 size)
{
#undef  malloc
    kdk_void *ptr = malloc(size);
#define malloc MALLOC
    return ptr;
}

kdk_void 
kdk_free(kdk_void *ptr)
{
#undef  free  
    free(ptr);
#define free   FREE   
    return;
}
