
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

static kdk_log_t stc_log = LOG_INIT;

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
    {
        strncpy(log->file_date, file_date, 8);
        return KDK_INIT;
    }

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

    if(log == KDK_NULL)
        return KDK_INARG;

    // Not strong enough
    if(log->file_handle == KDK_NULL)
    {
        ret_code = kdk_log_set_file_handle_(log);
        if(ret_code)
            return ret_code;
    }
    else 
    {
        do
        {
            fclose(log->file_handle);
            log->file_handle = KDK_NULL;

            ret_code = kdk_log_set_file_last(log);
            if(ret_code) 
                return ret_code;

            ret_code = kdk_log_set_file_handle_(log);
            if(ret_code)
                return KDK_NULLPTR;
        }
        while(kdk_log_check_file_size(log->file_handle, 0) != KDK_SUCCESS);
    }

    //write init date

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
    if(ret_code && ret_code != KDK_INIT)
        return ret_code;

    ret_code = kdk_log_set_file_handle(&stc_log);
    if(ret_code)
        return ret_code;

    return KDK_SUCCESS;
}

static kdk_void
kdk_log_write_(kdk_uint32 level, kdk_char32 *file, kdk_uint32 line, kdk_char32 *fmt, kdk_va_list ap)
{
    kdk_time_t      log_time; 
    kdk_char32      log_line[LOG_LINE_SIZE] = {0};
    kdk_char32      log_level[9] = {0};

    memset(&log_time, 0, sizeof(log_time));
    kdk_time_get_date_time(&log_time);

    if(level < stc_log.level)
        return ;

    memset(&log_level, 0, sizeof(log_level));
    switch(level)
    {
        case LOG_LEVEL_ERROR:
            strncpy(log_level, "ERROR", 6);
            break;
        case LOG_LEVEL_WARN:
            strncpy(log_level, "WARN ", 6);
            break;
        case LOG_LEVEL_INFO:
            strncpy(log_level, "INFO ", 6);
            break;
        case LOG_LEVEL_DEBUG:
            strncpy(log_level, "DEBUG", 6);
            break;
        default:
            strncpy(log_level, "     ", 6);
            break;
    }

    memset(log_line, 0, sizeof(log_line));
    snprintf(log_line, LOG_LINE_SIZE, "[%s][%s][%-5d][%s:%d] ", log_time.hms2, log_level, getpid(), file, line);

    vsnprintf(log_line + strlen(log_line), LOG_LINE_SIZE, fmt, ap);

    fprintf(stc_log.file_handle, "%s\n", log_line);
    fflush(stc_log.file_handle);
    
    return ;
}

kdk_uint32
kdk_log_write(kdk_uint32 level, kdk_char32 *file, kdk_uint32 line, kdk_char32 *fmt, ...)
{
    kdk_uint32      ret_code;
    kdk_va_list     ap;

    if(file == KDK_NULL || fmt == KDK_NULL)
        return KDK_INARG;

    ret_code = kdk_log_set_file_date(&stc_log);
    if(ret_code && ret_code != KDK_INIT)
    {
        return ret_code;
    }
    else if(ret_code == KDK_INIT)
    {
        ret_code = kdk_log_set_file_handle(&stc_log);
        if(ret_code)
            return ret_code;
    }
    else
    {
        // NULL
    }

    ret_code = kdk_log_check_file_size(stc_log.file_handle, LOG_LINE_SIZE);
    if(ret_code)
    {
        ret_code = kdk_log_set_file_handle(&stc_log);
        if(ret_code)
            return ret_code;
    }

    va_start(ap,fmt);
    kdk_log_write_(level, file, line, fmt, ap);
    va_end(ap);
    
    return KDK_SUCCESS;
}

kdk_void
kdk_log_destroy()
{
    if(stc_log.file_handle != KDK_NULL)
        fclose(stc_log.file_handle);

    memset(&stc_log, 0, sizeof(stc_log));
    stc_log.file_last[0] = 'A';

    return ;
}
