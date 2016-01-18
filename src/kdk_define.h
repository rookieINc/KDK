
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

typedef unsigned int kdk_uint32;
typedef int          kdk_int32;
typedef FILE         kdk_file;
typedef char         kdk_char32;
typedef void         kdk_void;
typedef double       kdk_double32;
typedef long         kdk_long32;

#define KDK_NULL        NULL
#define KDK_NULLFOUND   ((kdk_void *)(1))

#define KDK_LINUXERR    -1

#define KDK_SUCCESS     0x0000
#define KDK_FAILURE     0x6001
#define KDK_NULLPTR     0x6002
#define KDK_ERRNO       0x6003
#define KDK_NOTFOUND    0x6004
#define KDK_OVERFLOW    0x6005
#define KDK_INVAL       0x6006
#define KDK_INARG       0x6007

#define malloc MALLOC
#define free   FREE

#define END_TAG '\0'

#define CHECK_NULL_AND_RETURN(x,y)\
    do{\
        if((x) == KDK_NULL)\
            return (y);\
    }while(0)


#endif /* _KDK_DEFINE_H_INCLUDED_ */
