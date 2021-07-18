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

NAME *NAME_init(int capacity)
^ Creates a vector of the given capacity (values smaller than 1 are set to 1).

void NAME_free(NAME *vect)
^ Liberates the memory requested by the vector.

void NAME_endadd(NAME *vect, STRU stru)
^ O(1) Adds an item at the end of the vector. Increasing its length by 1.

STRU NAME_endpop(NAME *vect)
^ O(1) Removes the last item from the vector, returning its value.

STRU NAME_endtop(const NAME *vect)
^ O(1) Returns the last item of the vector.

void NAME_add(NAME *vect, int p, STRU stru)
^ O(n-p) Adds an item at position p.

STRU NAME_pop(NAME *vect, int p)
^ O(n-p) Deletes the item on position p, returning its value.

int NAME_len(const NAME *vect)
^ O(1) Returns the number of items in the vector.

STRU NAME_item(const NAME *vect, int p)
^ O(1) Returns the item at the position p.

STRU NAME_sort(NAME *vect, int (*sortCallback)(const STRU *a, const STRU *b))
^ O(n log n) Sorts the items according to the sort callback.
* The callback must return must return an integer less than, equal to, or
greater than zero if the first argument is considered to be respectively
less than, equal to, or greater than the second.
* Uses qsort as the sorting algorithm.
* See `man qsort` for more info.


##### VARIABLES:

STRU vect->items[k]
^ Access the struct at position k.

#####
*/

#define CADTS_VECTOR(NAME,STRU) \
\
typedef struct {\
    int len;\
    int capacity;\
    STRU *items;\
} NAME;\
\
static NAME *NAME##_init(int capacity){\
    NAME *vect = malloc(sizeof(NAME));\
    vect->len = 0;\
    if(capacity<1) capacity = 1;\
    vect->capacity = capacity;\
    vect->items = (STRU *) malloc(sizeof(STRU)*vect->capacity);\
    return vect;\
}\
\
static void NAME##_free(NAME *vect){\
    free(vect->items);\
    free(vect);\
}\
\
static void NAME##_endadd(NAME *vect, STRU stru){\
    if(vect->len==vect->capacity){\
        vect->capacity *= 2;\
        vect->items = (STRU *) realloc(vect->items,sizeof(STRU)*vect->capacity);\
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
static STRU NAME##_endtop(const NAME *vect){\
    assert(vect->len>0);\
    return vect->items[vect->len - 1];\
}\
\
static void NAME##_add(NAME *vect, int p, STRU stru){\
    assert(p>=0 && p<=vect->len);\
    if(vect->len==vect->capacity){\
        vect->capacity *= 2;\
        vect->items = (STRU *) realloc(vect->items,sizeof(STRU)*vect->capacity);\
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
static inline int NAME##_len(const NAME *vect){\
    return vect->len;\
}\
\
static STRU NAME##_item(const NAME *vect, int p){\
    assert(p>=0 && p<vect->len);\
    return vect->items[p];\
}\
\
static void NAME##_sort(NAME *vect, int (*compar)(const STRU*, const STRU*)){\
    assert(vect->len>0);\
    int (*callback)(const void*, const void*) =  (int (*)(const void*, const void*) ) compar;\
    qsort(vect->items, vect->len, sizeof(STRU), callback);\
}\
\

#endif
