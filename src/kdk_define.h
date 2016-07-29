
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_define.h
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 06:53
 * Description : kdk_define.h
 * History     :     
 ***********************************************************/


#ifndef _KDK_DEFINE_H_INCLUDED_
#define _KDK_DEFINE_H_INCLUDED_

//typedef unsigned int kdk_uint32;
typedef int          kdk_uint32; //For skdpay
typedef int          kdk_int32;
typedef short        kdk_short32;
//typedef long         kdk_long32;
typedef int          kdk_long32; //For sdkpay
typedef FILE         kdk_file;
typedef char         kdk_char32;
typedef void         kdk_void;
typedef double       kdk_double32;

typedef pid_t        kdk_pid;
typedef time_t       kdk_time;

typedef struct stat  kdk_stat_t;
typedef struct tm    kdk_tm_t;
typedef va_list      kdk_va_list;

#define KDK_NULL        NULL
#define KDK_NULLFOUND   ((kdk_void *)(1))

#define KDK_LINUXERR    -1

enum KDK_RET_CODE
{
    KDK_SUCCESS  = 0x0000,
    KDK_FAILURE  = 0x6001,
    KDK_NULLPTR  = 0x6002,
    KDK_ERRNO    = 0x6003,
    KDK_NOTFOUND = 0x6004,
    KDK_OVERFLOW = 0x6005,
    KDK_INVAL    = 0x6006,
    KDK_INARG    = 0x6007,
    KDK_INIT     = 0x6008
};

#define malloc MALLOC
#define free   FREE

#define END_TAG '\0'

#define CHECK_NULL_AND_RETURN(x,y)\
    do{\
        if((x) == KDK_NULL)\
            return (y);\
    }while(0)

#define PATH_LEN    48
#define NAME_LEN    48
#define ARG_LEN     10

#endif /* _KDK_DEFINE_H_INCLUDED_ */
