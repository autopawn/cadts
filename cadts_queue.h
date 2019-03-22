#ifndef CADTS_QUEUE_H
#define CADTS_QUEUE_H

#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdlib.h>
#include <assert.h>

/*
##### DEFINITION:

A queue is a data strictire where elements can be added from one side and retrieved from the other.

It's implemented as an array that keeps track of its first and last element, and resizes as needed.

#define CADTS_QUEUE(NAME,STRU)
^ Where NAME is the name that the ADT will get and STRU is the datatype of its items.

##### FUNCTIONS:

NAME *NAME_init(int size)
^ Creates a queue of the given size (values smaller than 1 are set to 1).

void NAME_free(NAME *queue)
^ Liberates the memory requested by the queue.

void NAME_push(NAME *queue, STRU stru)
^ O(1) Adds an item at the end of the queue. Increasing its length by 1.

STRU NAME_pop(NAME *queue)
^ O(1) Removes the next item from the queue, returning its value.

STRU NAME_front(NAME *queue)
^ O(1) Returns the next item of the queue. It does not remove it.

STRU NAME_back(NAME *queue, int p, STRU stru)
^ O(1) Returns the last item pushed to the queue. It does not remove it.

int NAME_len(NAME *queue)
^ O(1) Returns the number of items in the queue.

##### VARIABLES:

None

#####
*/

#define CADTS_QUEUE(NAME,STRU) \
\
typedef struct {\
    int first;\
    int last;\
    int len;\
    int size;\
    STRU *items;\
} NAME;\
\
static NAME *NAME##_init(int size){\
    NAME *queue = malloc(sizeof(NAME));\
    queue->first = 0;\
    queue->last = -1;\
    queue->len = 0;\
    if(size<1) size = 1;\
    queue->size = size;\
    queue->items = (STRU *) malloc(sizeof(STRU)*queue->size);\
    return queue;\
}\
\
static void NAME##_free(NAME *queue){\
    free(queue->items);\
    free(queue);\
}\
\
static void NAME##_push(NAME *queue, STRU stru){\
    if(queue->len==queue->size){\
        queue->size *= 2;\
        STRU *aux = (STRU *) malloc(sizeof(STRU)*queue->size);\
        for(int i = 0; i < queue->len; ++i){\
            aux[i] = queue->items[(queue->first+i)%queue->len];\
        }\
        free(queue->items);\
        queue->items = aux;\
        queue->last = queue->len-1;\
        queue->first = 0;\
    }\
    queue->len += 1;\
    queue->last = ((queue->last+1)%queue->size);\
    queue->items[queue->last] = stru;\
}\
\
static STRU NAME##_pop(NAME *queue){\
    assert(queue->len>0);\
    STRU element = queue->items[queue->first];\
    queue->len -= 1;\
    queue->first = (queue->first+1)%queue->size;\
    return element;\
}\
\
static STRU NAME##_front(NAME *queue){\
    assert(queue->len>0);\
    return queue->items[queue->first];\
}\
\
static STRU NAME##_back(NAME *queue){\
    assert(queue->len>0);\
    return queue->items[queue->last];\
}\
\
static inline int NAME##_len(NAME *queue){\
    return queue->len;\
}\
\

#endif
