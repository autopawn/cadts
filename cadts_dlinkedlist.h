#ifndef CADTS_DLINKEDLIST_H
#define CADTS_DLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

/*
NOTE:
Pointers to STRU also work like iterators, as they are casted to
NAME##_cadts_node, a NULL pointer to STRU can be used to indicate
"before begining" position, also is returned by the "next" when the list is
over.
For unused nodes only the post pointer is used.
On an empty list, "end" is used to find the first unused node on the empty list.
*/

#define CADTS_DLINKEDLIST(NAME,STRU) \
\
typedef struct NAME##_cadts_node NAME##_cadts_node;\
\
struct NAME##_cadts_node {\
    STRU item;\
    NAME##_cadts_node *pre;\
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
void NAME##_init(NAME *dlist, int size){\
    dlist->len = 0;\
    if(size<1) size = 1;\
    dlist->size = size;\
    dlist->nodes = malloc(sizeof(NAME##_cadts_node)*dlist->size);\
    for(int i=0;i<dlist->size-1;i++){\
        dlist->nodes[i].post = &dlist->nodes[i+1];\
    }\
    dlist->end = &dlist->nodes[0];\
    dlist->end->pre = NULL;\
}\
\
void NAME##_free(NAME *dlist){\
    free(dlist->nodes);\
}\
\
STRU *NAME##_first(NAME *dlist){\
    if(dlist->len==0) return NULL;\
    return &dlist->ini->item;\
}\
\
STRU *NAME##_last(NAME *dlist){\
    if(dlist->len==0) return NULL;\
    return &dlist->end->item;\
}\
\
STRU *NAME##_del(NAME *dlist, STRU *posi){\
    if(dlist->len<=0){\
        fprintf(stderr,"ERROR: del on empty dlinkedlist!\n");\
        exit(1);\
    }\
    NAME##_cadts_node *node = (NAME##_cadts_node *) posi;\
    NAME##_cadts_node *bef = node->pre;\
    NAME##_cadts_node *aft = node->post;\
    if(bef!=NULL) bef->post = aft;\
    if(aft!=NULL) aft->pre = bef;\
    if(dlist->len!=1){\
        if(node==dlist->ini) dlist->ini = aft;\
        else if(node==dlist->end){\
            dlist->end = bef;\
            aft = NULL;\
        }\
    }else{\
        aft = NULL;\
    }\
    NAME##_cadts_node *aftend = dlist->end->post;\
    dlist->end->post = node;\
    node->post = aftend;\
    dlist->len -= 1;\
    if(aft==NULL) return NULL;\
    return &aft->item;\
}\
\
void NAME##_afteradd(NAME *dlist, STRU *posi, STRU stru){\
    if(dlist->len==0){\
        if(posi!=NULL){\
            fprintf(stderr,"ERROR: add after not NULL on empty dlinkedlist!\n");\
            exit(1);\
        }\
        dlist->end->item = stru;\
        dlist->ini = dlist->end;\
        dlist->len = 1;\
    }else{\
        if(dlist->len==dlist->size){\
            dlist->size *= 2;\
            dlist->nodes = realloc(dlist->nodes,sizeof(NAME##_cadts_node)*dlist->size);\
            for(int i=dlist->size/2;i<dlist->size-1;i++){\
                dlist->nodes[i].post = &dlist->nodes[i+1];\
            }\
            dlist->end->post = &dlist->nodes[dlist->size/2];\
        }\
        NAME##_cadts_node *new_node = dlist->end->post;\
        dlist->end->post = new_node->post;\
        NAME##_cadts_node *posin = (NAME##_cadts_node *) posi;\
        if(posin==NULL){\
            new_node->pre = NULL;\
            new_node->post = dlist->ini;\
            dlist->ini->pre = new_node;\
            dlist->ini = new_node;\
        }else{\
            new_node->pre = posin;\
            new_node->post = posin->post;\
            posin->post = new_node;\
            new_node->post->pre = new_node;\
            if(new_node->pre==dlist->end) dlist->end = new_node;\
        }\
        new_node->item = stru;\
        dlist->len += 1;\
    }\
}\
\
void NAME##_iniadd(NAME *dlist, STRU stru){\
    NAME##_afteradd(dlist,NULL,stru);\
}\
\
void NAME##_endadd(NAME *dlist, STRU stru){\
    if(dlist->len==0) NAME##_afteradd(dlist,NULL,stru);\
    else NAME##_afteradd(dlist,&dlist->end->item,stru);\
}\
\
STRU NAME##_inipop(NAME *dlist){\
    STRU *item = &dlist->ini->item;\
    NAME##_del(dlist,item);\
    return *item;\
}\
\
STRU NAME##_endpop(NAME *dlist){\
    STRU *item = &dlist->end->item;\
    NAME##_del(dlist,item);\
    return *item;\
}\
STRU *NAME##_next(NAME *dlist, STRU *posi){\
    if(posi==NULL){\
        fprintf(stderr,"ERROR: next on empty pointer!\n");\
        exit(1);\
    }\
    if(dlist->len==0){\
        fprintf(stderr,"ERROR: next on empty dlinkedlist!\n");\
        exit(1);\
    }\
    NAME##_cadts_node *posin = (NAME##_cadts_node *) posi;\
    if(posin==dlist->end) return NULL;\
    return (STRU *) posin->post;\
}\
\
STRU *NAME##_prev(NAME *dlist, STRU *posi){\
    if(posi==NULL){\
        fprintf(stderr,"ERROR: prev on empty pointer!\n");\
        exit(1);\
    }\
    if(dlist->len==0){\
        fprintf(stderr,"ERROR: prev on empty dlinkedlist!\n");\
        exit(1);\
    }\
    NAME##_cadts_node *posin = (NAME##_cadts_node *) posi;\
    return (STRU *) posin->pre;\
}\

#endif
