#ifndef CADTS_VECTOR_H
#define CADTS_VECTOR_H

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

void NAME_endadd(NAME *vect, STRU stru)
^ O(1) Adds an item at the end of the vector. Increasing its length by 1.

STRU NAME_endpop(NAME *vect)
^ O(1) Deletes the last item of the vector, returning its value.

##### VARIABLES:

int vect->len
^ The number of items in the vector (read only!)

STRU vect->items[k]
^ Set or get the struct at position k.

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

#endif
