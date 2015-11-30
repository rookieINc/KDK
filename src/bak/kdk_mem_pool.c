#include "kdk_mem_pool.h"

static kdk_mem_cell_t *
kdk_mem_cell_create(kdk_uint32 size)
{
    kdk_mem_cell_t     *cell;

    if(size <= 0 || size > SIZE_MAX - MEMCELLALIGNSIZE - ALIGNNUM)
        return KDK_NULL;

    cell = (kdk_mem_cell_t *)kdk_malloc(ALIGN(size) + MEMCELLALIGNSIZE);
    if(cell == KDK_NULL)
        return KDK_NULL;		

    cell->mem_cell_size = ALIGN(size);
    cell->mem_cell_free = ALIGN(size);
    cell->mem_cell_offset = (void *)cell + MEMCELLALIGNSIZE;
    cell->mem_cell_next = KDK_NULL;

    return  cell;
}

static kdk_uint32 
kdk_mem_cell_clear(kdk_mem_cell_t *cell)
{
    if(cell == KDK_NULL)
        return KDK_NULLPTR; 

    cell->mem_cell_free = cell->mem_cell_size;
    cell->mem_cell_offset = (void *)cell + MEMCELLALIGNSIZE;
    memset(cell->mem_cell_offset, 0, cell->mem_cell_free);

    return KDK_SUCCESS;
}

kdk_mem_pool_t *
kdk_mem_pool_create(kdk_uint32 size, kdk_uint32 reallocSize)
{
    kdk_mem_pool_t     *head;
    kdk_mem_cell_t     *cell;

    if(size <= 0 || size > SIZE_MAX - MEMPOOLALIGNSIZE - ALIGNNUM)
        return KDK_NULL;

    if(reallocSize <= 0 || reallocSize > SIZE_MAX - MEMCELLALIGNSIZE - ALIGNNUM)
        return KDK_NULL;

    cell = (kdk_mem_cell_t *)kdk_mem_cell_create(size);
    if(cell == KDK_NULL)
        return KDK_NULL;		

    head = (kdk_mem_pool_t *)kdk_malloc(MEMPOOLALIGNSIZE);
    if(head == KDK_NULL)
        return KDK_NULL;		

    head->mem_pool_realloc_size = ALIGN(reallocSize);
    head->mem_pool_clear = ISNOTCLEAR;
    head->mem_pool_cell_offset = cell;
    head->mem_pool_cell_list = cell;

    return  head;
}

void *
kdk_mem_pool_malloc(kdk_mem_pool_t *head, kdk_uint32 mallocSize)
{
    kdk_uint32      alignSize, initSize;
    kdk_mem_cell_t    *mCellResult;
    void           *result;

    if(head == KDK_NULL || mallocSize <= 0 || mallocSize > SIZE_MAX - ALIGNNUM)
        return KDK_NULL;

    alignSize = ALIGN(mallocSize);

    if(head->mem_pool_clear == ISCLEAR)
        while(head->mem_pool_cell_offset != KDK_NULL && head->mem_pool_cell_offset->mem_cell_free < alignSize)
            head->mem_pool_cell_offset = head->mem_pool_cell_offset->mem_cell_next;

    if(head->mem_pool_cell_offset == KDK_NULL || head->mem_pool_cell_offset->mem_cell_free < alignSize)
    {
        if(alignSize < ALIGN(head->mem_pool_realloc_size))
            initSize = ALIGN(head->mem_pool_realloc_size);
        else
            initSize = alignSize;

        mCellResult = kdk_mem_cell_create(initSize);
        if(mCellResult == KDK_NULL)
            return KDK_NULL;

        head->mem_pool_cell_offset->mem_cell_next = mCellResult;
        head->mem_pool_cell_offset = mCellResult;
    }
    else
    {
        mCellResult = head->mem_pool_cell_offset;
    }

    mCellResult->mem_cell_free -= alignSize;
    result = mCellResult->mem_cell_offset;
    mCellResult->mem_cell_offset += alignSize;
    memset(result, 0, alignSize);

    return result;
}

kdk_uint32 
kdk_mem_pool_clear(kdk_mem_pool_t *head)
{
    kdk_mem_cell_t  *currCell;

    if(head == KDK_NULL)
        return KDK_NULLPTR; 

    head->mem_pool_clear = ISCLEAR;
    currCell = head->mem_pool_cell_list;
    head->mem_pool_cell_offset = currCell;

    while(currCell != KDK_NULL)
    {
        kdk_mem_cell_clear(currCell);
        currCell = currCell->mem_cell_next;
    }

    return KDK_SUCCESS;
}

void 
kdk_mem_pool_destroy(kdk_mem_pool_t *head)
{
    kdk_mem_cell_t  *currCell;

    if(head == KDK_NULL)
        return; 

    while(head->mem_pool_cell_list != KDK_NULL)
    {
        currCell = head->mem_pool_cell_list;
        head->mem_pool_cell_list = head->mem_pool_cell_list->mem_cell_next;
        kdk_free(currCell);
    }

    kdk_free(head);
    head = KDK_NULL;
    return;
}

kdk_uint32
kdk_mem_pool_print(kdk_mem_pool_t *head)
{
    kdk_uint32      i = 0;

    if(head == KDK_NULL)
        return KDK_NULLPTR;

    kdk_mem_cell_t  sCell;
    head->mem_pool_cell_offset = head->mem_pool_cell_list;
    while(head->mem_pool_cell_offset != KDK_NULL)
    {
        i++;
        fprintf(stderr, "CELL[%08d]:[%s]\n", i, (char *)((void *)(head->mem_pool_cell_offset) + MEMCELLALIGNSIZE)); 
        memcpy(&sCell, head->mem_pool_cell_offset, MEMCELLALIGNSIZE);
        head->mem_pool_cell_offset = sCell.mem_cell_next;
    }

    return KDK_SUCCESS;
}

