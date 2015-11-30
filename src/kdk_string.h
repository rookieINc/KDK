#ifndef __KDK_STRING_H__
#define __KDK_STRING_H__

int isvarset(int c);

typedef unsigned int kdk_uint32;
typedef int          kdk_int32;
typedef FILE         kdk_file;
typedef char         kdk_char32;
typedef void         kdk_void;
typedef double       kdk_double32;
typedef long         kdk_long32;

#define KDK_NULL        NULL

#define KDK_SUCCESS     0x0000
#define KDK_FAILURE     0x6001
#define KDK_NULLPTR     0x6002
#define KDK_ERRNO       0x6003
#define KDK_NOTFOUND    0x6004
#define KDK_OVERFLOW    0x6005
#define KDK_INVAL       0x6006
#define KDK_INARG       0x6007

#endif
