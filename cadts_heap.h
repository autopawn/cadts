#ifndef CADTS_HEAP_H
#define CADTS_HEAP_H

#include <stdio.h>
#include <stdlib.h>

#define CADTS_HEAP(NAME,STRU,A_CMP_B) \
\
typedef struct {\
    int len;\
    int size;\
    STRU *items;\
} NAME;\
\
void NAME##_init(NAME *heap, int size){\
    heap->len = 0;\
    if(size<1) size = 1;\
    heap->size = size;\
    heap->items = malloc(sizeof(STRU)*heap->size);\
}\
\
STRU NAME##_peek(NAME *heap){\
    if(heap->len<=0){\
        fprintf(stderr,"ERROR: peek on empty heap!\n");\
        exit(1);\
    }\
    return heap->items[0];\
}\
STRU NAME##_poll(NAME *heap){\
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
void NAME##_add(NAME *heap, STRU val){\
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
