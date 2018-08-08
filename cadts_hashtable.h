#ifndef CADTS_HASHTABLE_H
#define CADTS_HASHTABLE_H

#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdlib.h>
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


##### FUNCTIONS:

void NAME_init(NAME *htable)
^ Initializes a hashtable.

void NAME_free(NAME *htable)
^ Liberates the memory requested by the hashtable.

void NAME_add(NAME *htable, KEY_STRU key, VAL_STRU val)
^ O(1) Adds a key to the hashtable with the given value. If the key already exists, the current value is replaced.

int NAME_has(NAME *htable, KEY_STRU key)
^ O(1) Checks if a given key exists.

##### VARIABLES:

int htable.len
^ The number of items in the hashtable (read only!).

#####
*/

static const unsigned int PRIMELESSP2[] = {
    3,7,13,31,61,127,251,509,1021,2039,4093,8191,16381,32749,65521,131071,
    262139,524287,1048573,2097143,4194301,8388593,16777213,33554393,67108859,
    134217689,268435399,536870909,1073741789,2147483647,4294967291};


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
    int n_active_iters;\
    int len;\
    int sizei;\
    NAME##_node **slots;\
} NAME;\
\
void NAME_init(NAME *htable){\
    htable->n_active_iters = 0;\
    htable->len = 0;\
    htable->sizei = 0;\
    htable->slots = malloc(sizeof(NAME##_node *)*PRIMELESSP2[htable->sizei]);\
    for(int i=0;i<PRIMELESSP2[htable->sizei];i++) htable->slots[i] = NULL;\
}\
\
void NAME_free(NAME *htable){\
    assert(htable->n_active_iters==0);\
    for(int i=0;i<PRIMELESSP2[htable->sizei];i++){\
        NAME##_node *ptr = htable->slots[i];\
        while(ptr!=NULL){\
            NAME##_node *ptrc = ptr;\
            ptr = ptr->next;\
            free(ptrc);\
        }\
    }\
}\
\
void NAME_add(NAME *htable, KEY_STRU key, VAL_STRU val){\
    htable->len += 1;\
    /* Realloc all the nodes in more space */ \
    if(htable->len>=PRIMELESSP2[htable->sizei]/2){\
        NAME##_node **neo_slots = malloc(sizeof(NAME##_node *)*PRIMELESSP2[htable->sizei+1]);\
        for(int i=0;i<PRIMELESSP2[htable->sizei+1];i++) neo_slots[i] = NULL;\
        for(int i=0;i<PRIMELESSP2[htable->sizei];i++){\
            NAME##_node *ptr = htable->slots[i];\
            while(ptr!=NULL){\
                NAME##_node *ptrc = ptr;\
                ptr = ptr->next;\
                /* Add this node in the neo_slots */ \
                KEY_STRU A = ptrc->key;\
                unsigned int hash = ((unsigned int)(HASH_A));\
                unsigned int slot = hash%PRIMELESSP2[htable->sizei+1];\
                ptrc->next = neo_slots[slot];\
                neo_slots[slot] = ptrc;\
            }\
        }\
        free(htable->slots);\
        htable->slots = neo_slots;\
        htable->sizei += 1;\
    }\
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
    /* Create and add new node */ \
    NAME##_node *node = malloc(sizeof(NAME##_node));\
    node->key = key;\
    node->val = val;\
    node->next = htable->slots[slot];\
    htable->slots[slot] = node;\
}\
\
int NAME_has(NAME *htable, KEY_STRU key){\
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

#endif