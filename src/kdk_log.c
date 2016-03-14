
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_log.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2016-02-01 14:05
 * Description : kdk_log.c
 * History     : 
 ***********************************************************/


#include "kdk_log.h"

static kdk_uint32
kdk_log_check_file_size(kdk_file *file_handle, kdk_uint32 size)
{
    kdk_int32       file_no; 
    kdk_int32       ret_code;
    kdk_stat_t      stat_buf; 

    if(file_handle == KDK_NULL)
        return KDK_INARG;

    memset(&stat_buf, 0, sizeof(stat_buf));
    
    file_no = fileno(file_handle);
    if(file_no < 0)
        return KDK_INVAL;

    ret_code = fstat(file_no, &stat_buf);
    if(ret_code != KDK_SUCCESS)
        return KDK_FAILURE;

    if(stat_buf.st_size >= 4294967296 - size)
        return KDK_OVERFLOW;
    
    return KDK_SUCCESS;
}

static kdk_uint32
kdk_log_set_file_date(kdk_log_t *log)
{
    kdk_char32      file_date[9] = {0};

    if(log == KDK_NULL)
        return KDK_INARG;

    kdk_time_get_current_date(file_date);

    if(strcmp(file_date, log->file_date) > 0)
       strncpy(log->file_date, file_date, 8);

    return KDK_SUCCESS;
}

static kdk_uint32
kdk_log_set_file_last(kdk_log_t *log)
{
    if(log == KDK_NULL)
        return KDK_INARG;

    if(isupper(log->file_last[0]) == 0)
        return KDK_FAILURE;
    
    log->file_last[0] = log->file_last[0] + 1;

    if(isupper(log->file_last[0]) == 0)
        return KDK_FAILURE;

    return KDK_SUCCESS;
}

static kdk_uint32
kdk_log_set_file_handle_(kdk_log_t *log)
{
    if(log == KDK_NULL)
        return KDK_INARG;

    kdk_char32  log_path_file[140] = {0};

    memset(log_path_file, 0, sizeof(log_path_file));
    snprintf(log_path_file, 140, "%s%s.%s_%s", log->file_path, log->file_name, log->file_date, log->file_last);

    log->file_handle = fopen(log_path_file, "a+");
    if(log->file_handle == KDK_NULL)
        return KDK_NULLPTR;

    return KDK_SUCCESS;
}

static kdk_uint32
kdk_log_set_file_handle(kdk_log_t *log)
{
    kdk_uint32      ret_code;
    kdk_uint32      init = 0;

    if(log == KDK_NULL)
        return KDK_INARG;

    do
    {
        if(log->file_handle != KDK_NULL)
        {
            fclose(log->file_handle);
            log->file_handle = KDK_NULL;
        }

        if(init != 0)
        {
            ret_code = kdk_log_set_file_last(log);
            if(ret_code) 
                return ret_code;
        }

        init = 1;

        ret_code = kdk_log_set_file_handle_(log);
        if(ret_code)
            return KDK_NULLPTR;
    }
    while(kdk_log_check_file_size(log->file_handle, 0) != KDK_SUCCESS);

    //write date

    return KDK_SUCCESS;
}

kdk_uint32
kdk_log_init(kdk_uint32 mask, kdk_uint32 level, kdk_char32 *file_path, kdk_char32 *file_name)
{
    kdk_uint32      ret_code;
    kdk_uint32      path_len, path_size;
    kdk_char32     *path;
    //in arg

    stc_log.mask = mask;
    stc_log.level = level;

    strncpy(stc_log.file_path, file_path, sizeof(stc_log.file_path));
    strncpy(stc_log.file_name, file_name, sizeof(stc_log.file_name));

    path      = stc_log.file_path;
    path_len  = strlen(path);
    path_size = sizeof(stc_log.file_path);

    if(path_len <= path_size - 2 && path[path_len - 1] != '/')
    {
        path[path_len] = '/';
        path[path_len + 1] = '\0';
    }
    else if(path[path_len - 1] != '/')
    {
        return KDK_FAILURE; 
    }
    else
    {
        // NULL
    }

    ret_code = kdk_log_set_file_date(&stc_log);
    if(ret_code)
        return ret_code;

    ret_code = kdk_log_set_file_handle(&stc_log);
    if(ret_code)
        return ret_code;

    return KDK_SUCCESS;
}

kdk_uint32
kdk_log_write()
{

}

kdk_void
kdk_log_destroy()
{
    if(stc_log.file_handle != KDK_NULL)
        fclose(stc_log.file_handle);

    memset(&stc_log, 0, sizeof(stc_log));

    return ;
}
