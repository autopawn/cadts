#ifndef CADTS_VECTOR_H
#define CADTS_VECTOR_H

#include <stdlib.h>

#define CADTS_VECTOR(NAME,STRU) \
\
typedef struct {\
    int _len;\
    int _size;\
    STRU items[0];\
} NAME;\
\
size_t  NAME##_size(NAME **strup){\
    NAME * stru = *strup;\
    return sizeof(NAME)+sizeof(STRU)*stru->_size;\
}\
NAME *new_##NAME(){\
    NAME *stru = malloc(sizeof(NAME)+sizeof(STRU)*4);\
    stru->_size = 4;\
    stru->_len = 0;\
    return stru;\
}\
void free_##NAME(NAME **strup){\
    free(*strup);\
    strup = NULL;\
}\
void NAME##_push(NAME **strup, STRU val){\
    NAME *stru = *strup;\
    if(stru->_len==stru->_size){\
        stru->_size*=2;\
        *strup = realloc(strup,NAME##_size(strup));\
        stru = *strup;\
    }\
    stru->items[stru->_len] = val;\
    stru->_len++;\
}\
STRU NAME##_pop(NAME **strup){\
    NAME *stru = *strup;\
    stru->_len--;\
    return stru->items[stru->_len];\
}\


#endif
