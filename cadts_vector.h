#ifndef CADTS_VECTOR_H
#define CADTS_VECTOR_H

#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdlib.h>
#include <assert.h>

/*
##### DEFINITION:

A vector is just an array that resizes once its capacity is not enough to store new values.

#define CADTS_VECTOR(NAME,STRU)
^ Where NAME is the name that the ADT will get and STRU is the datatype of its items.

##### FUNCTIONS:

NAME *NAME_init(int size)
^ Creates a vector of the given size (values smaller than 1 are set to 1).

void NAME_free(NAME *vect)
^ Liberates the memory requested by the vector.

void NAME_endadd(NAME *vect, STRU stru)
^ O(1) Adds an item at the end of the vector. Increasing its length by 1.

STRU NAME_endpop(NAME *vect)
^ O(1) Removes the last item from the vector, returning its value.

STRU NAME_endtop(NAME *vect)
^ O(1) Returns the last item of the vector.

void NAME_add(NAME *vect, int p, STRU stru)
^ O(n-p) Adds an item at position p.

STRU NAME_pop(NAME *vect, int p)
^ O(n-p) Deletes the item on position p, returning its value.

int NAME_len(NAME *vect)
^ O(1) Returns the number of items in the vector.

STRU NAME_item(NAME *vect, int p)
^ O(1) Returns the item at the position p.

##### VARIABLES:

STRU vect->items[k]
^ Access the struct at position k.

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
static NAME *NAME##_init(int size){\
    NAME *vect = malloc(sizeof(NAME));\
    vect->len = 0;\
    if(size<1) size = 1;\
    vect->size = size;\
    vect->items = (STRU *) malloc(sizeof(STRU)*vect->size);\
    return vect;\
}\
\
static void NAME##_free(NAME *vect){\
    free(vect->items);\
    free(vect);\
}\
\
static void NAME##_endadd(NAME *vect, STRU stru){\
    if(vect->len==vect->size){\
        vect->size *= 2;\
        vect->items = (STRU *) realloc(vect->items,sizeof(STRU)*vect->size);\
    }\
    vect->items[vect->len] = stru;\
    vect->len += 1;\
}\
\
static STRU NAME##_endpop(NAME *vect){\
    assert(vect->len>0);\
    vect->len -= 1;\
    return vect->items[vect->len];\
}\
\
static STRU NAME##_endtop(NAME *vect){\
    assert(vect->len>0);\
    return vect->items[vect->len - 1];\
}\
\
static void NAME##_add(NAME *vect, int p, STRU stru){\
    assert(p>=0 && p<=vect->len);\
    if(vect->len==vect->size){\
        vect->size *= 2;\
        vect->items = (STRU *) realloc(vect->items,sizeof(STRU)*vect->size);\
    }\
    for(int i=vect->len-1; p<=i; i--){\
        vect->items[i+1] = vect->items[i];\
    }\
    vect->len += 1;\
    vect->items[p] = stru;\
}\
\
static STRU NAME##_pop(NAME *vect, int p){\
    assert(p>=0 && p<vect->len);\
    STRU ret = vect->items[p];\
    vect->len -= 1;\
    for(int i=p; i<vect->len; i++){\
        vect->items[i] = vect->items[i+1];\
    }\
    return ret;\
}\
\
static inline int NAME##_len(NAME *vect){\
    return vect->len;\
}\
\
static STRU NAME##_item(NAME *vect, int p){\
    assert(p>=0 && p<vect->len);\
    return vect->items[p];\
}\
\

#endif
