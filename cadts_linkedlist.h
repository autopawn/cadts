#ifndef CADTS_LINKEDLIST_H
#define CADTS_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#define CADTS_LINKEDLIST(NAME,STRU) \
\
typedef struct NAME##_cadts_node NAME##_cadts_node;\
\
struct NAME##_cadts_node {\
    STRU item;\
    NAME##_cadts_node *post;\
};\
\
typedef struct {\
    int len;\
    int size;\
    NAME##_cadts_node *ini;\
    NAME##_cadts_node *end;\
    NAME##_cadts_node *nodes;\
} NAME;\
\
void NAME##_init(NAME *llist, int size){\
    llist->len = 0;\
    if(size<1) size = 1;\
    llist->size = size;\
    llist->nodes = malloc(sizeof(NAME##_cadts_node)*llist->size);\
    for(int i=0;i<llist->size-1;i++){\
        llist->nodes[i].post = &llist->nodes[i+1];\
    }\
    llist->end = &llist->nodes[0];\
}\
\
void NAME##_free(NAME *llist){\
    free(llist->nodes);\
}\
\
void _##NAME##_extend(NAME *llist){\
    llist->size *= 2;\
    NAME##_cadts_node *old = llist->nodes;\
    llist->nodes = realloc(llist->nodes,sizeof(NAME##_cadts_node)*llist->size);\
    if(llist->nodes!=old){\
        for(int i=0;i<llist->size/2;i++){\
            llist->nodes[i].post += (llist->nodes-old);\
        }\
        llist->ini += (llist->nodes-old);\
        llist->end += (llist->nodes-old);\
    }\
    for(int i=llist->size/2;i<llist->size-1;i++){\
        llist->nodes[i].post = &llist->nodes[i+1];\
    }\
    llist->end->post = &llist->nodes[llist->size/2];\
}\
\
STRU *NAME##_first(NAME *llist){\
    if(llist->len==0) return NULL;\
    return &llist->ini->item;\
}\
\
void NAME##_endadd(NAME *llist, STRU stru){\
    if(llist->len==0){\
        llist->end->item = stru;\
        llist->ini = llist->end;\
        llist->len = 1;\
    }else{\
        if(llist->len==llist->size) _##NAME##_extend(llist);\
        llist->end = llist->end->post;\
        llist->end->item = stru;\
        llist->len += 1;\
    }\
}\
\
void NAME##_iniadd(NAME *llist, STRU stru){\
    if(llist->len==0){\
        llist->end->item = stru;\
        llist->ini = llist->end;\
        llist->len = 1;\
    }else{\
        if(llist->len==llist->size) _##NAME##_extend(llist);\
        NAME##_cadts_node *new_node = llist->end->post;\
        llist->end->post = new_node->post;\
        new_node->post = llist->ini;\
        llist->ini = new_node;\
        new_node->item = stru;\
        llist->len += 1;\
    }\
}\
\
void NAME##_afterdel(NAME *llist, STRU *posi){\
    if(llist->len==0){\
        fprintf(stderr,"ERROR: afterdel on empty linkedlist!\n");\
        exit(1);\
    }\
    NAME##_cadts_node *posin = (NAME##_cadts_node *) posi;\
    if(posin==llist->end){\
        fprintf(stderr,"ERROR: afterdel on ending item!\n");\
        exit(1);\
    }\
    if(posi==NULL){\
        NAME##_cadts_node *del_node = llist->ini;\
        llist->ini = llist->ini->post;\
        del_node->post = llist->end->post;\
        llist->end->post = del_node;\
    }else{\
        NAME##_cadts_node *del_node = posin->post;\
        posin->post = del_node->post;\
        del_node->post = llist->end->post;\
        llist->end->post = del_node;\
        if(del_node==llist->end) llist->end = posin;\
    }\
    llist->len -= 1;\
}\
\
STRU NAME##_inipop(NAME *llist){\
    if(llist->len<=0){\
        fprintf(stderr,"ERROR: inipop on empty linkedlist!\n");\
        exit(1);\
    }\
    STRU item = llist->ini->item;\
    NAME##_afterdel(llist,NULL);\
    return item;\
}\
\
STRU *NAME##_next(NAME *llist, STRU *posi){\
    if(llist->len==0){\
        fprintf(stderr,"ERROR: next on empty linkedlist!\n");\
        exit(1);\
    }\
    if(posi==NULL){\
        fprintf(stderr,"ERROR: next on null pointer!\n");\
        exit(1);\
    }\
    NAME##_cadts_node *posin = (NAME##_cadts_node *) posi;\
    if(posin==llist->end) return NULL;\
    return (STRU *) posin->post;\
}\


#endif
