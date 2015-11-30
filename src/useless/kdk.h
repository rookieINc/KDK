#ifndef __KDK_H__
#define __KDK_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#define malloc MALLOC
#define free   FREE

#include "kdk_string.h"
#include "kdk_mem_pool.h"
#include "kdk_hash.h"
#include "kdk_malloc.h"
#include "kdk_stack.h"
#include "kdk_queue.h"

#define CHECK_NULL_AND_RETURN(x,y)\
    do{\
        if((x) == KDK_NULL)\
            return (y);\
    }while(0)


#endif
