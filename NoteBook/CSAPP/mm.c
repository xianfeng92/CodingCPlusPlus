// Basic constants and macros
#define WSIZE
#define DSIZE
#define CHUNKSIZE (1<<12)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
// pack a size and allocated bit into a word
#define PACK(size, alloc) ((size) | (alloc))

// read and write a word at address p
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & ~0x1)

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) -GET_SIZE(((char *)bp) - DSIZE)))


int mem_init(void) {
    // Create the initial empty heap
    if((heap_listp =mem_sbrk(4*WSIZE)) == ((void *)-1)) {
        return -1;
    }

    PUT(heap_listp, 0);
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));
    heap_listp += (2*WSIZE);

    if(extend_heap(CHUNKSIZE / WSIZE) == null) {
        return -1;
    }
    return 0;
}


static void *extend_heap(size_t words) {
    char *bp;
    size_t size;

    //Allocate an even number of words to maintain alignment
    size = (words % 2) ? (words + 1) * WSIZE : words *WSIZE;
    if((long)(bp = mem_sbrk(size)) == -1) {
        return NULL;
    }

    PUT((HDRP(bp), PACK(size, 0));
    PUT((FTRP(bp), PACK(size, 0));
    PUT((HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    return coalesce(bp)
}


void mm_free(void *bp) {
    size_t size = GET_SIZE(HDRP(bp));

    PUT((HDRP(bp), PACK(size, 0));
    PUT((FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

void *mm_malloc(size_t size) {
    size_t asize;
    size_t extendsize;
    char *bp;

    if(size == 0) {
        return NULL;
    }

    if(size <= DSIZE){
        asize = 2 * DSIZE;
    } else {
        asize = DSIZE * ((size + (DSIZE) + (DSIZE -1)) / DSIZE);
    }

    if((bp = find_fit(asize)) != NULL){
        place(bp, asize);
        return bp;
    }

    extendsize = MAX(asize, CHUNKSIZE);
    if((bp = extend_heap(extendsize/WSIZE)) == NULL){
        return NULL;
    }

    place(bp, asize);
    return bp;
}




