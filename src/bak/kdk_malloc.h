#ifndef __KDK_MALLOC_H__
#define __KDK_MALLOC_H__

#include "kdk.h"

void *kdk_malloc(kdk_uint32 size);
void  kdk_free(void *ptr);

#endif
