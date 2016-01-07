
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_dl.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-01-07 21:25
 * Description : kdk_dl.c
 * History     : 
 ***********************************************************/


#include "kdk_dl.h"

kdk_void *kdk_dl_open(kdk_char32 *dl_file, kdk_char32 *func_name)
{
    kdk_void    *handle;

    if(dl_file == KDK_NULL || func_name == KDK_NULL)
        return KDK_NULL;

    handle = dlopen(dl_file, RTLD_NOW | RTLD_GLOBAL);
    if(handle == KDK_NULL)
        return KDK_NULL;

    return dlsym(handle, func_name);
}

kdk_void kdk_dl_close(kdk_void *handle)
{
    dlclose(handle);
    return ;
}

