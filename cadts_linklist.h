#ifndef CADTS_LINKLIST_H
#define CADTS_LINKLIST_H

#include <stdio.h>
#include <stdlib.h>

/*
"piter" is the pointer to the node previous to the iterator.
    When piter is NULL is outside the list.
    When it is (NAME##_node *)&llist->ini it is at the begining.
*/

#define CADTS_LINKLIST(NAME,STRU) \
\
typedef struct NAME##_node NAME##_node;\
struct NAME##_node {\
    NAME##_node *next;\
    STRU item;\
};\
\
typedef struct {\
    int len;\
    int size;\
    NAME##_node *nodes;\
    NAME##_node *ini;\
    NAME##_node *end;\
    NAME##_node *piter;\
} NAME;\
\
void NAME##_init(NAME *llist, int size){\
    llist->len = 0;\
    if(size<1) size=1;\
    llist->size = size;\
    llist->nodes = malloc(sizeof(NAME##_node)*llist->size);\
    for(int i=0;i<llist->size-1;i++){\
        llist->nodes[i].next = &llist->nodes[i+1];\
    }\
    llist->nodes[llist->size-1].next = &llist->nodes[llist->size-1];\
    llist->ini = &llist->nodes[0];\
    llist->end = (NAME##_node *)&llist->ini;\
    llist->piter = NULL;\
}\
\
void NAME##_free(NAME *llist){\
    free(llist->nodes);\
}\
\
void NAME##_extend(NAME *llist){\
    llist->size *= 2;\
    NAME##_node *old = llist->nodes;\
    llist->nodes = realloc(llist->nodes,sizeof(NAME##_node)*llist->size);\
    if(llist->nodes!=old){\
        for(int i=0;i<llist->size/2;i++){\
            llist->nodes[i].next += (llist->nodes-old);\
        }\
        llist->ini += (llist->nodes-old);\
        llist->end += (llist->nodes-old);\
        if(llist->piter!=NULL && llist->piter!=(NAME##_node *)&llist->ini){\
            llist->piter += (llist->nodes-old);\
        }\
    }\
    llist->end->next = &llist->nodes[llist->size/2];\
    for(int i=llist->size/2;i<llist->size-1;i++){\
        llist->nodes[i].next = &llist->nodes[i+1];\
    }\
    llist->nodes[llist->size-1].next = &llist->nodes[llist->size-1];\
}\
\
void NAME##_itini(NAME *llist){\
    llist->piter = (NAME##_node *)&llist->ini;\
    if(llist->piter==llist->end) llist->piter=NULL;\
}\
\
void NAME##_itnext(NAME *llist){\
    if(llist->piter==NULL){\
        fprintf(stderr,"ERROR: next with iterator outside.\n");\
        exit(1);\
    }\
    llist->piter = llist->piter->next;\
    if(llist->piter==llist->end) llist->piter = NULL;\
}\
\
void NAME##_itout(NAME *llist){\
    llist->piter = NULL;\
}\
\
int NAME##_itvalid(NAME *llist){\
    return llist->piter!=NULL;\
}\
\
STRU NAME##_itget(NAME *llist){\
    if(!NAME##_itvalid(llist)){\
        fprintf(stderr,"ERROR: get with iterator outside.\n");\
        exit(1);\
    }\
    return llist->piter->next->item;\
}\
\
STRU NAME##_itpop(NAME *llist){\
    if(!NAME##_itvalid(llist)){\
        fprintf(stderr,"ERROR: pop with iterator outside.\n");\
        exit(1);\
    }\
    STRU *retval;\
    if(llist->piter->next == llist->end){\
        retval = &llist->end->item;\
        llist->end = llist->piter;\
        llist->piter = NULL;\
    }else{\
        NAME##_node *del_node = llist->piter->next;\
        retval = &del_node->item;\
        llist->piter->next = del_node->next;\
        del_node->next = llist->end->next;\
        llist->end->next = del_node;\
    }\
    llist->len -=1;\
    return *retval;\
}\
\
STRU NAME##_inipop(NAME *llist){\
    NAME##_node *prepiter = llist->piter;\
    NAME##_itini(llist);\
    STRU retval = NAME##_itpop(llist);\
    llist->piter = prepiter;\
    return retval;\
}\
\
void NAME##_itaddbefore(NAME *llist, STRU val){\
    if(llist->len==llist->size) NAME##_extend(llist);\
    NAME##_node *new_node = llist->end->next;\
    if(llist->piter==NULL){\
        llist->end = new_node;\
    }else{\
        llist->end->next = new_node->next;\
        new_node->next = llist->piter->next;\
        llist->piter->next = new_node;\
    }\
    new_node->item = val;\
    llist->len += 1;\
}\
\
void NAME##_itaddafter(NAME *llist, STRU val){\
    NAME##_node *prepiter = llist->piter;\
    if(llist->piter==NULL){\
        NAME##_itini(llist);\
    }else{\
        NAME##_itnext(llist);\
    }\
    NAME##_itaddbefore(llist,val);\
    llist->piter = prepiter;\
}\
\
void NAME##_endadd(NAME *llist, STRU val){\
    NAME##_node *prepiter = llist->piter;\
    llist->piter = NULL;\
    NAME##_itaddbefore(llist,val);\
    llist->piter = prepiter;\
}\
\
void NAME##_iniadd(NAME *llist, STRU val){\
    NAME##_node *prepiter = llist->piter;\
    NAME##_itini(llist);\
    NAME##_itaddbefore(llist,val);\
    llist->piter = prepiter;\
}\
\

#endif
