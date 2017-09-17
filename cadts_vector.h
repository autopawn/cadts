#ifndef CADTS_VECTOR_H
#define CADTS_VECTOR_H

#include <stdlib.h>

#define CADTS_VECTOR(NAME,STRU) \
\
typedef struct {\
    int len;\
    int size;\
    STRU *items;\
} NAME;\
\
void NAME##_init(NAME *vect, int size){\
    vect->len = 0;\
    if(size<1) size = 1;\
    vect->size = size;\
    vect->items = malloc(sizeof(STRU)*vect->size);\
}\
\
void NAME##_free(NAME *vect){\
    free(vect->items);\
}\
\
void NAME##_empty(NAME *vect){\
    vect->len = 0;\
}\
\
void NAME##_push(NAME *vect, STRU stru){\
    if(vect->len==vect->size){\
        vect->size *= 2;\
        vect->items = realloc(vect->items,sizeof(STRU)*vect->size);\
    }\
    vect->items[vect->len] = stru;\
    vect->len += 1;\
}\
\
STRU NAME##_pop(NAME *vect){\
    vect->len -= 1;\
    return vect->items[vect->len];\
}\

#endif
