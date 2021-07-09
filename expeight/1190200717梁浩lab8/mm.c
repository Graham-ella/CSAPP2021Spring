/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

 /*********************************************************
  * NOTE TO STUDENTS: Before you do anything else, please
  * provide your team information in the following struct.
  ********************************************************/
team_t team = {
    /* Team name */
    "1190200717",
    /* First member's full name */
    "Liang Hao",
    /* First member's email address */
    "1190200717@qq.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};


/*Basic constants and macros*/
#define WSIZE       4       /* Word and header/footer size (bytes) */  
#define DSIZE       8       /* Double word size (bytes) */
#define CHUNKSIZE  (1<<12)  /* Extend heap by this amount (bytes) */

#define MAX(x, y) ((x) > (y)? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))
#define PUT(p, val)  (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)  
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8//选择8字节对齐

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))


static char* heap_listp;  /* pointer to first block */


/* function prototypes for internal helper routines */
static void* extend_heap(size_t words);
static void place(void* bp, size_t asize);
static void* find_fit(size_t asize);
static void* coalesce(void* bp);
//void checkheap(int verbose);
static void checkBlock(void* bp);
static void printBlock(void* bp);



/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    //堆的初始化
    //返回值：0表示正常，-1表示有错误

    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void*)-1)
        return -1;
    PUT(heap_listp, 0);                        /* Alignment padding */
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));  /* Prologue header */
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));  /* Prologue footer */
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));   /* Epilogue header */
    heap_listp += (2 * WSIZE);

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;
    return 0;
}


/*
 * extend_heap - Extend heap with free block and return its block pointer
 */
 /* $begin mmextendheap */
static void* extend_heap(size_t words)
{
    char* bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* free block header */
    PUT(FTRP(bp), PACK(size, 0));         /* free block footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* new epilogue header */

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}
/* $end mmextendheap */

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void* mm_malloc(size_t size)
{

    //申请有效载荷至少是参数“size”指定大小的内存块，返回
    //该内存块地址首地址（可以使用的区域首地址）。申请的整个
    //块应该在堆的区间内，并且不能与其他已经分配的块重叠。
    //返回的地址应该是8字节对齐的（地址%8==0）

    /*
    int newsize = ALIGN(size + SIZE_T_SIZE);//newsize是利用地址8字节对齐后得到的新的内存大小
    void* p = mem_sbrk(newsize);//将堆增加incr字节，参数incr是正整数,函数返回新增加堆区域的首字节地址
    if (p == (void*)-1)
        return NULL;
    else {
        *(size_t*)p = size;
        return (void*)((char*)p + SIZE_T_SIZE);
    }
    */
    size_t asize;/*Adjusted block size */
    size_t extendsize;/* Amount to extend heap if no fit */
    char* bp;

    /* Ignore spurious requests */
    if (size == 0)
        return NULL;

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= DSIZE)
        asize = 2 * DSIZE;
    else
        asize = DSIZE * ((size + (DSIZE)+(DSIZE - 1)) / DSIZE);

    /* Search the free list for a fit*/
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void* bp)
{
    //释放参数“ptr”指向的已分配内存块，没有返回值。
    //指针值ptr应该是之前调用mm_malloc或mm_realloc返回的值，并且没有释放过。
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void* mm_realloc(void* ptr, size_t size)
{
    size_t oldSize;//获取原来的大小
    void* newptr;
    if ((newptr = mm_malloc(size)) == NULL) {
        printf("ERROR: mm_malloc failed in mm_realloc\n");
        exit(1);
    }
    oldSize = GET_SIZE(HDRP(ptr));
    if (size < oldSize)//如果现在申请的大小<原来的大小
        oldSize = size;//赋值的时候只需要赋值现在的大小那么多
    memcpy(newptr, ptr, oldSize);
    mm_free(ptr);
    return newptr;
}





/*
 * place - Place block of asize bytes at start of free block bp
 *         and split if remainder would be at least minimum block size
 */
 /* $begin mmplace */
 /* $begin mmplace-proto */
static void place(void* bp, size_t asize)
/* $end mmplace-proto */
{
    size_t csize = GET_SIZE(HDRP(bp));

    if ((csize - asize) >= (DSIZE + DSIZE)) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0));
        PUT(FTRP(bp), PACK(csize - asize, 0));
    }
    else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}
/* $end mmplace */

/*
 * find_fit - Find a fit for a block with asize bytes
 */
static void* find_fit(size_t asize)
{
    /* first fit search */
    void* bp;

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            return bp;
        }
    }
    return NULL; /* no fit */

}

/*
 * coalesce - boundary tag coalescing. Return ptr to coalesced block
 */
static void* coalesce(void* bp)
{
    size_t  prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));//获得前一个块的已分配标记位

    size_t  next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));//获得后一个块的已分配标记位

    size_t size = GET_SIZE(HDRP(bp));//获得bp所指向的块的大小

    //下面对应书中提到的4种合并情况：

    /* 1.前后均为allocated块，不做合并，直接返回 */
    if (prev_alloc && next_alloc)  
    {
        return bp;
    }

    /* 2.前面的块是allocated，但是后面的块是free的，这时将两个free块合并 */
    else if (prev_alloc && !next_alloc)  
    {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }

    /* 3.后面的块是allocated，但是前面的块是free的，这时将两个free块合并 */
    else if (!prev_alloc && next_alloc)   
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    /* 4.前后两个块都是free块，这时将三个块同时合并 */
    else
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    return bp;
}

static void printBlock(void* bp)
{
    size_t hsize, halloc, fsize, falloc;

    hsize = GET_SIZE(HDRP(bp));
    halloc = GET_ALLOC(HDRP(bp));
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));

    if (hsize == 0) {
        printf("%p: EOL\n", bp);
        return;
    }

    printf("%p: header: [%d:%c] footer: [%d:%c]\n", bp,
        hsize, (halloc ? 'a' : 'f'),
        fsize, (falloc ? 'a' : 'f'));
}

static void checkBlock(void* bp)
{
    //1、检查是否双字对齐 
    if ((size_t)bp % 8)
        printf("Error: %p is not doubleword aligned\n", bp);

    //2、获得p所指块的头部和脚部指针，判断两者是否匹配，不匹配的话就返回错误信息
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
        printf("Error: header does not match footer\n");
}

/*
 * mm_checkheap - Check the heap for consistency
 */
void mm_checkheap(int verbose)
{
    char* bp = heap_listp;//定义指针 bp，初始化为指向序言块的全局变量heap_listp

    if (verbose) {
        printf("Heap (%p):\n", heap_listp);
    }
       
    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) {
        printf("Bad prologue header\n");//当序言块不是8字节的已分配块，就会打印Bad prologue header
    }
    checkBlock(heap_listp);
    
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {//检查所有size > 0的块
        if (verbose) {
            printBlock(bp);
        }
        checkBlock(bp);
    }


    //检查结尾块。当结尾块不是一个大小为 0 的已分配块，就会打印 Bad epilogueheader
    if (verbose) {
        printBlock(bp);
    }
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp)))) {
        printf("Bad epilogue header\n");
    }
        
}



