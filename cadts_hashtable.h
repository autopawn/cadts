#ifndef CADTS_HASHTABLE_H
#define CADTS_HASHTABLE_H

#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
##### DEFINITION:

A hashtable is a data structure that maps keys to values, the keys are hashed
to secure fast access to each key value.

#define CADTS_HASHTABLE(NAME,KEY_STRU,VAL_STRU,A_EQL_B,HASH_A)
^ Where NAME is the name that the ADT will get, KEY_STRU is the datatype of the keys and VAL_STRU is the datatype of the values.
A_EQL_B is a comparison for equality from literal "A" and a literal "B", both of type KEY_STRU, e.g. "A==B" if KEY_STRU is a primitive datatype.
HASH_A is an expresion that uses a literal "A" (a key) of type KEY_STRU, and gives its hash, that then is casted to an unsigned int.

NOTE: Its your responsability that if A_EQL_B implies that x==y replacing A by x and B by y, then HASH_A replacing A by x must be equal to HASH_A replacing A by y.

NOTE: Don't hold more than 1073741822 keys.

##### FUNCTIONS:

NAME *NAME_init()
^ Creates a hashtable.

void NAME_free(NAME *htable)
^ Liberates the memory requested by the hashtable.

void NAME_add(NAME *htable, KEY_STRU key, VAL_STRU val)
^ O(1) Adds a key to the hashtable with the given value. If the key already exists, the current value is replaced.

int NAME_has(NAME *htable, KEY_STRU key)
^ O(1) Checks if a given key exists.

VAL_STRU NAME_get(NAME *htable, KEY_STRU key)
^ O(1) Gets the value of a given key.

VAL_STRU NAME_pop(NAME *htable, KEY_STRU key)
^ O(1) Deletes the given key, returning its associated value.

##### ITERATOR FUNCTIONS:

Iterators are designed for traversing the whole hashtable in O(n).

NOTE: Iterators shouldn't be used after their hashtable is freed.

NAME_iter NAME_begin(NAME *htable)
^ Returns an iterator for the hashtable.

int NAME_iter_done(NAME_iter *iter)
^ Checks if the iterator has finish.

void NAME_iter_next(NAME_iter *iter)
^ Moves the iterator forward.

KEY_STRU NAME_iter_key(NAME_iter *iter)
^ Retrieves the key at the current iterator.

VAL_STRU NAME_iter_val(NAME_iter *iter)
^ Retrieves the value at the current iterator.

int NAME_len(NAME *htable)
^ O(1) Returns the number of items in the hashtable.

##### VARIABLES:

-- NONE --

#####
*/

static const unsigned int PRIMELESSP2[] = {
    3,7,13,31,61,127,251,509,1021,2039,4093,8191,16381,32749,65521,131071,
    262139,524287,1048573,2097143,4194301,8388593,16777213,33554393,67108859,
    134217689,268435399,536870909,1073741789,2147483647};


#define CADTS_HASHTABLE(NAME,KEY_STRU,VAL_STRU,A_EQL_B,HASH_A) \
\
typedef struct NAME##_node NAME##_node;\
struct NAME##_node {\
    NAME##_node *next;\
    KEY_STRU key;\
    VAL_STRU val;\
};\
\
typedef struct {\
    int n_modifications;\
    int len;\
    int sizei;\
    NAME##_node **slots;\
} NAME;\
\
static NAME *NAME##_init(){\
    NAME *htable = malloc(sizeof(NAME));\
    htable->n_modifications = 0;\
    htable->len = 0;\
    htable->sizei = 0;\
    htable->slots = malloc(sizeof(NAME##_node *)*PRIMELESSP2[htable->sizei]);\
    for(unsigned int i=0;i<PRIMELESSP2[htable->sizei];i++) htable->slots[i] = NULL;\
    return htable;\
}\
\
static void NAME##_free(NAME *htable){\
    for(unsigned int i=0;i<PRIMELESSP2[htable->sizei];i++){\
        NAME##_node *ptr = htable->slots[i];\
        while(ptr!=NULL){\
            NAME##_node *ptrc = ptr;\
            ptr = ptr->next;\
            free(ptrc);\
        }\
    }\
    free(htable->slots);\
    free(htable);\
}\
\
static void NAME##_add(NAME *htable, KEY_STRU key, VAL_STRU val){\
    /* Check for presence of the current key */ \
    KEY_STRU A = key;\
    unsigned int hash = ((unsigned int)(HASH_A));\
    unsigned int slot = hash%PRIMELESSP2[htable->sizei];\
    NAME##_node *ptr = htable->slots[slot];\
    while(ptr!=NULL){\
        NAME##_node *ptrc = ptr;\
        ptr = ptr->next;\
        KEY_STRU B = ptrc->key;\
        /* If key was found */ \
        if(A_EQL_B){\
            ptrc->val = val;\
            return;\
        }\
    }\
    /* Update counters */ \
    htable->n_modifications += 1;\
    htable->len += 1;\
    /* Realloc all the nodes in more space */ \
    if((unsigned int)htable->len>=PRIMELESSP2[htable->sizei]/2){\
        NAME##_node **neo_slots = malloc(sizeof(NAME##_node *)*PRIMELESSP2[htable->sizei+1]);\
        for(unsigned int i=0;i<PRIMELESSP2[htable->sizei+1];i++) neo_slots[i] = NULL;\
        for(unsigned int i=0;i<PRIMELESSP2[htable->sizei];i++){\
            NAME##_node *ptr = htable->slots[i];\
            while(ptr!=NULL){\
                NAME##_node *ptrc = ptr;\
                ptr = ptr->next;\
                /* Add this node in the neo_slots */ \
                KEY_STRU A = ptrc->key;\
                unsigned int hash = ((unsigned int)(HASH_A));\
                unsigned int cslot = hash%PRIMELESSP2[htable->sizei+1];\
                ptrc->next = neo_slots[cslot];\
                neo_slots[cslot] = ptrc;\
            }\
        }\
        free(htable->slots);\
        htable->slots = neo_slots;\
        htable->sizei += 1;\
        /* Recompute slot of the hash */ \
        slot = hash%PRIMELESSP2[htable->sizei];\
    }\
    /* Create and add new node */ \
    NAME##_node *node = malloc(sizeof(NAME##_node));\
    node->key = key;\
    node->val = val;\
    node->next = htable->slots[slot];\
    htable->slots[slot] = node;\
}\
\
static int NAME##_has(NAME *htable, KEY_STRU key){\
    /* Check for presence of the current key */ \
    KEY_STRU A = key;\
    unsigned int hash = ((unsigned int)(HASH_A));\
    unsigned int slot = hash%PRIMELESSP2[htable->sizei];\
    NAME##_node *ptr = htable->slots[slot];\
    while(ptr!=NULL){\
        NAME##_node *ptrc = ptr;\
        ptr = ptr->next;\
        KEY_STRU B = ptrc->key;\
        /* If key was found */ \
        if(A_EQL_B) return 1; \
    }\
    return 0;\
}\
\
static VAL_STRU NAME##_get(NAME *htable, KEY_STRU key){\
    /* Check for presence of the current key */ \
    KEY_STRU A = key;\
    unsigned int hash = ((unsigned int)(HASH_A));\
    unsigned int slot = hash%PRIMELESSP2[htable->sizei];\
    NAME##_node *ptr = htable->slots[slot];\
    while(ptr!=NULL){\
        NAME##_node *ptrc = ptr;\
        ptr = ptr->next;\
        KEY_STRU B = ptrc->key;\
        /* Key was found */ \
        if(A_EQL_B){\
            return ptrc->val;\
        }\
    }\
    /* Key was not found and should have been, return 0-inited struct for deterministic behaviour if assertion is ignored. */ \
    assert(!"Key exists.");\
    VAL_STRU dummy;\
    memset(&dummy,0,sizeof(VAL_STRU));\
    return dummy;\
}\
\
static VAL_STRU NAME##_pop(NAME *htable, KEY_STRU key){\
    /* Check for presence of the current key */ \
    KEY_STRU A = key;\
    unsigned int hash = ((unsigned int)(HASH_A));\
    unsigned int slot = hash%PRIMELESSP2[htable->sizei];\
    NAME##_node **preptr = &htable->slots[slot];\
    while(*preptr!=NULL){\
        NAME##_node *ptrc = *preptr;\
        KEY_STRU B = ptrc->key;\
        /* If key was found */ \
        if(A_EQL_B){\
            /* Update counters */ \
            htable->n_modifications += 1;\
            htable->len -= 1;\
            /* Make previous pointer point to the next node */ \
            *preptr = ptrc->next;\
            VAL_STRU val = ptrc->val;\
            free(ptrc);\
            /* Realloc all the nodes in less space */ \
            if((unsigned int)htable->len<PRIMELESSP2[htable->sizei]/4){\
                NAME##_node **neo_slots = malloc(sizeof(NAME##_node *)*PRIMELESSP2[htable->sizei-1]);\
                for(unsigned int i=0;i<PRIMELESSP2[htable->sizei-1];i++) neo_slots[i] = NULL;\
                for(unsigned int i=0;i<PRIMELESSP2[htable->sizei];i++){\
                    NAME##_node *ptr = htable->slots[i];\
                    while(ptr!=NULL){\
                        NAME##_node *ptrc = ptr;\
                        ptr = ptr->next;\
                        /* Add this node in the neo_slots */ \
                        KEY_STRU A = ptrc->key;\
                        unsigned int hash = ((unsigned int)(HASH_A));\
                        unsigned int cslot = hash%PRIMELESSP2[htable->sizei-1];\
                        ptrc->next = neo_slots[cslot];\
                        neo_slots[cslot] = ptrc;\
                    }\
                }\
                free(htable->slots);\
                htable->slots = neo_slots;\
                htable->sizei -= 1;\
            }\
            /* Return val */ \
            return val;\
        }\
        /* Advance pre pointer */ \
        preptr = &ptrc->next;\
    }\
    /* Key was not found and should have been, return 0-inited struct for deterministic behaviour if assertion is ignored. */ \
    assert(!"Key exists.");\
    VAL_STRU dummy;\
    memset(&dummy,0,sizeof(VAL_STRU));\
    return dummy;\
}\
\
typedef struct {\
    NAME *origin;\
    int n_modifications;\
    int slot;\
    NAME##_node *ptrc;\
} NAME##_iter;\
\
static NAME##_iter NAME##_begin(NAME *htable){\
    NAME##_iter iter;\
    iter.origin = htable;\
    iter.n_modifications = htable->n_modifications;\
    iter.slot = PRIMELESSP2[iter.origin->sizei];\
    for(unsigned int i=0;i<PRIMELESSP2[iter.origin->sizei];i++){\
        if(iter.origin->slots[i]!=NULL){\
            iter.ptrc = iter.origin->slots[i];\
            iter.slot = i;\
            break;\
        }\
    }\
    return iter;\
}\
\
static void NAME##_iter_next(NAME##_iter *iter){\
    if(iter->n_modifications!=iter->origin->n_modifications){\
        assert(!"Hashtable wasn't modified.");\
    }\
    /* Check if iterator is already done */ \
    if((unsigned int)iter->slot==PRIMELESSP2[iter->origin->sizei]) return;\
    /* Move iterator forward until reach end or finding another node */ \
    iter->ptrc = iter->ptrc->next;\
    while(iter->ptrc==NULL){\
        iter->slot += 1;\
        if((unsigned int)iter->slot==PRIMELESSP2[iter->origin->sizei]) break; \
        iter->ptrc = iter->origin->slots[iter->slot];\
    }\
}\
\
static int NAME##_iter_done(NAME##_iter *iter){\
    if(iter->n_modifications!=iter->origin->n_modifications){\
        assert(!"Hashtable wasn't modified.");\
    }\
    return (unsigned int)iter->slot==PRIMELESSP2[iter->origin->sizei];\
}\
\
static KEY_STRU NAME##_iter_key(NAME##_iter *iter){\
    if(iter->n_modifications!=iter->origin->n_modifications){\
        assert(!"Hashtable wasn't modified.");\
    }\
    assert(!NAME##_iter_done(iter));\
    return iter->ptrc->key;\
}\
\
static VAL_STRU NAME##_iter_val(NAME##_iter *iter){\
    if(iter->n_modifications!=iter->origin->n_modifications){\
        assert(!"Hashtable wasn't modified.");\
    }\
    assert(!NAME##_iter_done(iter));\
    return iter->ptrc->val;\
}\
\
static inline int NAME##_len(NAME *htable){\
    return htable->len;\
}\
\

#endif
