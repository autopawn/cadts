#ifndef CADTS_VECTOR_H
#define CADTS_VECTOR_H

#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdlib.h>

/*
##### DEFINITION:

A vector is just an array that resizes once its capacity is not enough to store new values.

#define CADTS_VECTOR(NAME,STRU)
^ Where NAME is the name that the ADT will get and STRU is the datatype of its items.

##### FUNCTIONS:

void NAME_init(NAME *vect, int size)
^ Initializes a vector of the given size (values smaller than 1 are set to 1).

void NAME_free(NAME *vect)
^ Liberates the memory requested by the vector.

STRU NAME_get(NAME *vect, int p)
^ O(1) Returns the item at position p.

void NAME_set(NAME *vect, int p, STRU val)
^ O(1) Sets the value val for the item at position p.

void NAME_endadd(NAME *vect, STRU stru)
^ O(1) Adds an item at the end of the vector. Increasing its length by 1.

STRU NAME_endpop(NAME *vect)
^ O(1) Deletes the last item of the vector, returning its value.

int NAME_len(NAME *vect)
^ O(1) Returns the length of the vector.

#####
*/

#define CADTS_VECTOR(NAME,STRU) \
\
typedef struct {\
    int len;\
    int size;\
    STRU *items;\
} NAME;\
\
static void NAME##_init(NAME *vect, int size){\
    vect->len = 0;\
    if(size<1) size = 1;\
    vect->size = size;\
    vect->items = malloc(sizeof(STRU)*vect->size);\
}\
\
static void NAME##_free(NAME *vect){\
    free(vect->items);\
}\
\
static STRU NAME##_get(NAME *vect, int p){\
    return vect->items[p];\
}\
\
static void NAME##_set(NAME *vect, int p, STRU val){\
    vect->items[p] = val;\
}\
\
static void NAME##_endadd(NAME *vect, STRU stru){\
    if(vect->len==vect->size){\
        vect->size *= 2;\
        vect->items = realloc(vect->items,sizeof(STRU)*vect->size);\
    }\
    vect->items[vect->len] = stru;\
    vect->len += 1;\
}\
\
static STRU NAME##_endpop(NAME *vect){\
    vect->len -= 1;\
    return vect->items[vect->len];\
}\
\
static int NAME##_len(NAME *vect){\
    return vect->len;\
}\

#endif
