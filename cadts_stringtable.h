#ifndef CADTS_STRINGTABLE_H
#define CADTS_STRINGTABLE_H

#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
##### DEFINITION:

The stringtable is a particular version of a hashtable that has string keys, and manages their memory internally.
A hashtable is a data structure that maps keys to values, the keys are hashed
to secure fast access to each key value.

#define CADTS_STRINGTABLE(NAME,VAL_STRU)
^ Where NAME is the name that the ADT will get, VAL_STRU is the datatype of the values.

NOTE: Don't hold more than 1073741822 keys.

NOTE: The hashing method used is djb2, see: http://www.cse.yorku.ca/~oz/hash.html

##### FUNCTIONS:

NAME *NAME_init()
^ Creates a stringtable.

void NAME_free(NAME *htable)
^ Liberates the memory requested by the stringtable.

void NAME_add(NAME *htable, const char *key, VAL_STRU val)
^ O(1) Adds a key to the strintable with the given value. If the key already exists, the current value is replaced.

int NAME_has(const NAME *htable, const char *key)
^ O(1) Checks if a given key exists.

VAL_STRU NAME_get(const NAME *htable, const char *key)
^ O(1) Gets the value of a given key.

VAL_STRU NAME_pop(NAME *htable, const char *key)
^ O(1) Deletes the given key, returning its associated value.

##### ITERATOR FUNCTIONS:

Iterators are designed for traversing the whole stringtable in O(n).

NOTE: Iterators shouldn't be used after their stringtable is freed.

NAME_iter NAME_begin(const NAME *htable)
^ Returns an iterator for the stringtable.

int NAME_iter_done(const NAME_iter *iter)
^ Checks if the iterator has finish.

void NAME_iter_next(NAME_iter *iter)
^ Moves the iterator forward.

const char *NAME_iter_key(const NAME_iter *iter)
^ Retrieves the key at the current iterator.
* NOTE: You should not modify the contents of this string.
* NOTE: You cannot continue using this key if you free the stringtable or pop it from it!

VAL_STRU NAME_iter_val(const NAME_iter *iter)
^ Retrieves the value at the current iterator.

int NAME_len(const NAME *htable)
^ O(1) Returns the number of items in the stringtable.

##### VARIABLES:

-- NONE --

#####
*/

#ifndef PRIMELESSTPOW2ARRAY
#define PRIMELESSTPOW2ARRAY
static const unsigned int PRIMELESSTPOW2[] = {3,7,13,31,61,127,251,509,1021,2039,4093,8191,16381,32749,65521,131071,262139,524287,1048573,2097143,4194301,8388593,16777213,33554393,67108859,134217689,268435399,536870909,1073741789,2147483647};
#endif


#define CADTS_STRINGTABLE(NAME,VAL_STRU) \
\
typedef struct NAME##_node NAME##_node;\
struct NAME##_node {\
    NAME##_node *next;\
    char *key;\
    VAL_STRU val;\
    unsigned int hash;\
};\
\
typedef struct {\
    int n_modifications;\
    int len;\
    int sizei;\
    NAME##_node **slots;\
} NAME;\
\
static unsigned int _##NAME##_hash(const unsigned char *str){\
    assert(str!=NULL);\
    unsigned int hash = 5381;\
    unsigned int c;\
    while((c=*str++)) hash = ((hash << 5) + hash) ^ c; /* hash * 33 ^ c */\
    return hash;\
}\
\
static NAME *NAME##_init(){\
    NAME *htable = malloc(sizeof(NAME));\
    htable->n_modifications = 0;\
    htable->len = 0;\
    htable->sizei = 0;\
    htable->slots = malloc(sizeof(NAME##_node *)*PRIMELESSTPOW2[htable->sizei]);\
    for(unsigned int i=0;i<PRIMELESSTPOW2[htable->sizei];i++) htable->slots[i] = NULL;\
    return htable;\
}\
\
static void NAME##_free(NAME *htable){\
    for(unsigned int i=0;i<PRIMELESSTPOW2[htable->sizei];i++){\
        NAME##_node *ptr = htable->slots[i];\
        while(ptr!=NULL){\
            NAME##_node *ptrc = ptr;\
            ptr = ptr->next;\
            free(ptrc->key);\
            free(ptrc);\
        }\
    }\
    free(htable->slots);\
    free(htable);\
}\
\
static void NAME##_add(NAME *htable, const char *key, VAL_STRU val){\
    /* Check for presence of the current key */ \
    unsigned int hash = _##NAME##_hash((const unsigned char *) key);\
    unsigned int slot = hash%PRIMELESSTPOW2[htable->sizei];\
    NAME##_node *ptr = htable->slots[slot];\
    while(ptr!=NULL){\
        NAME##_node *ptrc = ptr;\
        ptr = ptr->next;\
        /* If key was found */ \
        if(hash==ptrc->hash && strcmp(key,ptrc->key)==0){\
            ptrc->val = val;\
            return;\
        }\
    }\
    /* Update counters */ \
    htable->n_modifications += 1;\
    htable->len += 1;\
    /* Realloc all the nodes in more space */ \
    if((unsigned int)htable->len>=PRIMELESSTPOW2[htable->sizei]/2){\
        NAME##_node **neo_slots = malloc(sizeof(NAME##_node *)*PRIMELESSTPOW2[htable->sizei+1]);\
        for(unsigned int i=0;i<PRIMELESSTPOW2[htable->sizei+1];i++) neo_slots[i] = NULL;\
        for(unsigned int i=0;i<PRIMELESSTPOW2[htable->sizei];i++){\
            NAME##_node *ptr = htable->slots[i];\
            while(ptr!=NULL){\
                NAME##_node *ptrc = ptr;\
                ptr = ptr->next;\
                /* Add this node in the neo_slots */ \
                unsigned int hash = ptrc->hash;\
                unsigned int cslot = hash%PRIMELESSTPOW2[htable->sizei+1];\
                ptrc->next = neo_slots[cslot];\
                neo_slots[cslot] = ptrc;\
            }\
        }\
        free(htable->slots);\
        htable->slots = neo_slots;\
        htable->sizei += 1;\
        /* Recompute slot of the hash */ \
        slot = hash%PRIMELESSTPOW2[htable->sizei];\
    }\
    /* Create and add new node */ \
    NAME##_node *node = malloc(sizeof(NAME##_node));\
    node->key = malloc(sizeof(unsigned char)*(strlen(key)+1));\
    strcpy(node->key,key);\
    node->val = val;\
    node->hash = hash;\
    node->next = htable->slots[slot];\
    htable->slots[slot] = node;\
}\
\
static int NAME##_has(const NAME *htable, const char *key){\
    /* Check for presence of the current key */ \
    unsigned int hash = _##NAME##_hash((const unsigned char *) key);\
    unsigned int slot = hash%PRIMELESSTPOW2[htable->sizei];\
    NAME##_node *ptr = htable->slots[slot];\
    while(ptr!=NULL){\
        NAME##_node *ptrc = ptr;\
        ptr = ptr->next;\
        /* If key was found */ \
        if(hash==ptrc->hash && strcmp(key,ptrc->key)==0){\
            return 1; \
        };\
    }\
    return 0;\
}\
\
static VAL_STRU NAME##_get(const NAME *htable, const char *key){\
    /* Check for presence of the current key */ \
    unsigned int hash = _##NAME##_hash((const unsigned char *) key);\
    unsigned int slot = hash%PRIMELESSTPOW2[htable->sizei];\
    NAME##_node *ptr = htable->slots[slot];\
    while(ptr!=NULL){\
        NAME##_node *ptrc = ptr;\
        ptr = ptr->next;\
        /* Key was found */ \
        if(hash==ptrc->hash && strcmp(key,ptrc->key)==0){\
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
static VAL_STRU NAME##_pop(NAME *htable, const char *key){\
    /* Check for presence of the current key */ \
    unsigned int hash = _##NAME##_hash((const unsigned char *) key);\
    unsigned int slot = hash%PRIMELESSTPOW2[htable->sizei];\
    NAME##_node **preptr = &htable->slots[slot];\
    while(*preptr!=NULL){\
        NAME##_node *ptrc = *preptr;\
        /* If key was found */ \
        if(hash==ptrc->hash && strcmp(key,ptrc->key)==0){\
            /* Update counters */ \
            htable->n_modifications += 1;\
            htable->len -= 1;\
            /* Make previous pointer point to the next node */ \
            *preptr = ptrc->next;\
            VAL_STRU val = ptrc->val;\
            /* Free node memory */ \
            free(ptrc->key);\
            free(ptrc);\
            /* Realloc all the nodes in less space */ \
            if((unsigned int)htable->len<PRIMELESSTPOW2[htable->sizei]/4){\
                NAME##_node **neo_slots = malloc(sizeof(NAME##_node *)*PRIMELESSTPOW2[htable->sizei-1]);\
                for(unsigned int i=0;i<PRIMELESSTPOW2[htable->sizei-1];i++) neo_slots[i] = NULL;\
                for(unsigned int i=0;i<PRIMELESSTPOW2[htable->sizei];i++){\
                    NAME##_node *ptr = htable->slots[i];\
                    while(ptr!=NULL){\
                        NAME##_node *ptrc = ptr;\
                        ptr = ptr->next;\
                        /* Add this node in the neo_slots */ \
                        unsigned int hash = ptrc->hash;\
                        unsigned int cslot = hash%PRIMELESSTPOW2[htable->sizei-1];\
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
    const NAME *origin;\
    int n_modifications;\
    int slot;\
    NAME##_node *ptrc;\
} NAME##_iter;\
\
static NAME##_iter NAME##_begin(const NAME *htable){\
    NAME##_iter iter;\
    iter.origin = htable;\
    iter.n_modifications = htable->n_modifications;\
    iter.slot = PRIMELESSTPOW2[iter.origin->sizei];\
    for(unsigned int i=0;i<PRIMELESSTPOW2[iter.origin->sizei];i++){\
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
        assert(!"Hashstring wasn't modified while iterating over it.");\
    }\
    /* Check if iterator is already done */ \
    if((unsigned int)iter->slot==PRIMELESSTPOW2[iter->origin->sizei]) return;\
    /* Move iterator forward until reach end or finding another node */ \
    iter->ptrc = iter->ptrc->next;\
    while(iter->ptrc==NULL){\
        iter->slot += 1;\
        if((unsigned int)iter->slot==PRIMELESSTPOW2[iter->origin->sizei]) break; \
        iter->ptrc = iter->origin->slots[iter->slot];\
    }\
}\
\
static int NAME##_iter_done(const NAME##_iter *iter){\
    if(iter->n_modifications!=iter->origin->n_modifications){\
        assert(!"Hashstring wasn't modified while iterating over it.");\
    }\
    return (unsigned int)iter->slot==PRIMELESSTPOW2[iter->origin->sizei];\
}\
\
static const char *NAME##_iter_key(const NAME##_iter *iter){\
    if(iter->n_modifications!=iter->origin->n_modifications){\
        assert(!"Hashstring wasn't modified while iterating over it.");\
    }\
    assert(!NAME##_iter_done(iter));\
    return iter->ptrc->key;\
}\
\
static VAL_STRU NAME##_iter_val(const NAME##_iter *iter){\
    if(iter->n_modifications!=iter->origin->n_modifications){\
        assert(!"Hashstring wasn't modified while iterating over it.");\
    }\
    assert(!NAME##_iter_done(iter));\
    return iter->ptrc->val;\
}\
\
static inline int NAME##_len(const NAME *htable){\
    return htable->len;\
}\
\

#endif
