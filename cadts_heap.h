#ifndef CADTS_HEAP_H
#define CADTS_HEAP_H

#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdio.h>
#include <stdlib.h>

/*
##### DEFINITION:

A heap is a binary tree where each node is smaller (or another propriety) than their children. It can be used to retrieve in O(logn) the smallest item.

#define CADTS_HEAP(NAME,STRU,A_CMP_B)
^ Where NAME is the name that the ADT will get and STRU is the datatype of its items.
A_CMP_B is a comparison between a literal "A" and a literal "B", to use the comparison "smaller", it can be "A<B"

##### FUNCTIONS:

void NAME_init(NAME *heap, int size)
^ Initializes a heap of the given size (values smaller than 1 are set to 1).

void NAME_free(NAME *heap)
^ Liberates the memory requested by the heap.

STRU NAME_peek(NAME *heap)
^ O(1) Get the smaller item.

STRU NAME_poll(NAME *heap)
^ O(logn) Gets the smaller item and deletes it from the heap.

void NAME_add(NAME *heap, STRU val)
^ O(logn) Adds an item to the heap.

##### VARIABLES:

int vect->len
^ The number of items in the heap (read only!)

#####
*/

#define CADTS_HEAP(NAME,STRU,A_CMP_B) \
\
typedef struct {\
    int len;\
    int size;\
    STRU *items;\
} NAME;\
\
static void NAME##_init(NAME *heap, int size){\
    heap->len = 0;\
    if(size<1) size = 1;\
    heap->size = size;\
    heap->items = malloc(sizeof(STRU)*heap->size);\
}\
\
static void NAME##_free(NAME *heap){\
    free(heap->items);\
}\
\
static STRU NAME##_peek(NAME *heap){\
    if(heap->len<=0){\
        fprintf(stderr,"ERROR: peek on empty heap!\n");\
        exit(1);\
    }\
    return heap->items[0];\
}\
static STRU NAME##_poll(NAME *heap){\
    if(heap->len<=0){\
        fprintf(stderr,"ERROR: pool on empty heap!\n");\
        exit(1);\
    }\
    /**/\
    STRU ret = heap->items[0];\
    heap->len -= 1;\
    heap->items[0] = heap->items[heap->len];\
    /* Heapify down: */\
    int i = 0;\
    int c = 2*i+1;\
    while(c<heap->len){\
        STRU A,B;\
        if(c+1<heap->len){\
            A = heap->items[c+1];\
            B = heap->items[c];\
            if(A_CMP_B) c = c+1;\
        }\
        A = heap->items[i];\
        B = heap->items[c];\
        if(A_CMP_B) break;\
        /**/\
        heap->items[i] = B;\
        heap->items[c] = A;\
        /**/\
        i = c;\
        c = 2*i+1;\
    }\
    return ret;\
}\
\
static void NAME##_add(NAME *heap, STRU val){\
    if(heap->len==heap->size){\
        heap->size *= 2;\
        heap->items = realloc(heap->items,sizeof(STRU)*heap->size);\
    }\
    /**/\
    heap->items[heap->len] = val;\
    heap->len += 1;\
    /* Heapify up: */\
    int i = heap->len-1;\
    int p = (i-1)/2;\
    while(1){\
        if(i<=0) break;\
        STRU A,B;\
        A = heap->items[i];\
        B = heap->items[p];\
        if(!(A_CMP_B)) break;\
        /**/\
        heap->items[i] = B;\
        heap->items[p] = A;\
        /**/\
        i = p;\
        p = (i-1)/2;\
    }\
}\

#endif
