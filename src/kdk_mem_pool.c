
/************************************************************
 * Copyright(C), 2015-2016, QTPAY
 * 
 * FileName    : kdk_mem_pool.c
 * Author      : rookieINc
 * Version     : v0.1.0
 * Date        : 2015-12-01 07:27
 * Description : kdk_mem_pool.c
 * History     :     
 ***********************************************************/


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

    cell->size = ALIGN(size);
    cell->free = ALIGN(size);
    cell->offset = (kdk_void *)cell + MEMCELLALIGNSIZE;
    cell->next = KDK_NULL;

    memset(cell->offset, 0, cell->free);

    return  cell;
}


static kdk_uint32 
kdk_mem_cell_clear(kdk_mem_cell_t *cell)
{
    if(cell == KDK_NULL)
        return KDK_INARG; 

    cell->free = cell->size;
    cell->offset = (kdk_void *)cell + MEMCELLALIGNSIZE;
    memset(cell->offset, 0, cell->free);

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

    head->realloc_size = ALIGN(reallocSize);
    head->clear        = ISNOTCLEAR;
    head->cell_curr    = cell;
    head->cell_list    = cell;

    return  head;
}


kdk_void *
kdk_mem_pool_malloc(kdk_mem_pool_t *head, kdk_uint32 mallocSize)
{
    kdk_uint32      alignSize, initSize;
    kdk_mem_cell_t    *mCellResult;
    kdk_void           *result;

    if(head == KDK_NULL || mallocSize <= 0 || mallocSize > SIZE_MAX - ALIGNNUM)
        return KDK_NULL;

    alignSize = ALIGN(mallocSize);

    if(head->clear == ISCLEAR)
        while(head->cell_curr != KDK_NULL && head->cell_curr->free < alignSize)
            head->cell_curr = head->cell_curr->next;

    if(head->cell_curr == KDK_NULL || head->cell_curr->free < alignSize)
    {
        if(alignSize < ALIGN(head->realloc_size))
            initSize = ALIGN(head->realloc_size);
        else
            initSize = alignSize;

        mCellResult = kdk_mem_cell_create(initSize);
        if(mCellResult == KDK_NULL)
            return KDK_NULL;

        head->cell_curr->next = mCellResult;
        head->cell_curr       = mCellResult;
    }
    else
    {
        mCellResult = head->cell_curr;
    }

    mCellResult->free   -= alignSize;
    result               = mCellResult->offset;
    mCellResult->offset += alignSize;

    //memset(result, 0, alignSize);

    return result;
}


kdk_uint32 
kdk_mem_pool_clear(kdk_mem_pool_t *head)
{
    kdk_mem_cell_t  *cell_curr;

    if(head == KDK_NULL)
        return KDK_INARG; 

    head->clear     = ISCLEAR;
    cell_curr       = head->cell_list;
    head->cell_curr = cell_curr;

    while(cell_curr != KDK_NULL)
    {
        kdk_mem_cell_clear(cell_curr);
        cell_curr = cell_curr->next;
    }

    return KDK_SUCCESS;
}


kdk_void 
kdk_mem_pool_destroy(kdk_mem_pool_t *head)
{
    kdk_mem_cell_t  *currCell;

    if(head == KDK_NULL)
        return; 

    while(head->cell_list != KDK_NULL)
    {
        currCell = head->cell_list;
        head->cell_list = head->cell_list->next;
        kdk_free(currCell);
        currCell = KDK_NULL;
    }

    kdk_free(head);
    head = KDK_NULL;

    return;
}
