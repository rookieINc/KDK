#include "kdk.h"

void *
kdk_malloc(kdk_uint32 size)
{
#undef  malloc
    void *ptr = malloc(size);
#define malloc MALLOC
    return ptr;
}

void 
kdk_free(void *ptr)
{
#undef  free  
    free(ptr);
#define free   FREE   
    return;
}
