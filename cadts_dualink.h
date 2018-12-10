/*
##### DEFINITION:

A dualink is a data structure that works like a double linked list, but is implemented in an array.
Each element keeps his index for its whole lifetime. The index -1 represents being outside the doble linked list,
used to represent positions before the begining or after the end of it.

#define CADTS_DUALINK(NAME,STRU)
#define CADTS_VECTOR(NAME,STRU)
^ Where NAME is the name that the ADT will get and STRU is the datatype of its items.

NOTE: Unlike a vector, you shouldn't access the items directly.

##### FUNCTIONS:

NAME *NAME_init(int size)
^ Creates a dualink of the given size (values smaller than 1 are set to 1).

void NAME_free(NAME *dlink)
^ Liberates the memory requested by the dualink.

int NAME_next(NAME *dlink, int index)
^ O(1) Gets the index of the next element of the dualink.
If index is the last element, -1 is retrieved.
If index is negative, the index of the first element is retrieved.

int NAME_prev(NAME *dlink, int index)
^ O(1) Gets the index of the previous element of the dualink.
If index is the first element, -1 is retrieved.
If index is negative, the index of the last element is retrieved.

void NAME_befadd(NAME *dlink, int index, STRU val)
^ O(1) Adds an item before the item with the given index.

void NAME_aftadd(NAME *dlink, int index, STRU val)
^ O(1) Adds an item after the item with the given index.

STRU NAME_pop(NAME *dlink, int index)
^ O(1) Deletes the item with the given index, returning its value.
The index shouldn't be used after this.

void NAME_iniadd(NAME *dlink, STRU stru)
^ O(1) Adds an item at the begining of the dualink. Increasing its length by 1.

void NAME_endadd(NAME *dlink, STRU stru)
^ O(1) Adds an item at the end of the dualink. Increasing its length by 1.

##### VARIABLES:

int vect->len
^ The number of items in the vector (read only!).

#####
*/

#define CADTS_DUALINK(NAME,STRU) \
\
typedef struct NAME##_n0de NAME##_n0de;\
struct NAME##_node {\
    int p_pre;\
    int p_pos;\
    STRU val;\
};\
\
typedef struct {\
    int len;\
    int size;\
    NAME##_n0de *nodes;\
    int p_ini;\
    int p_end;\
} NAME;\
\
static NAME *NAME##_init(int size){\
    NAME *dlink = malloc(sizeof(NAME));\
    dlink->len = 0;\
    if(size<1) size = 1;\
    dlink->size = size;\
    \
    dlink->nodes = (NAME##_n0de *) malloc(sizeof(NAME##_n0de)*dlink->size);\
    for(int i=0;i<dlink->size;i++){\
        dlink->nodes[i].p_pre = i-1;\
        dlink->nodes[i].p_pos = i+1;\
        \
    }\
    dlink->nodes[0].p_pre = dlink->size-1;\
    dlink->nodes[dlink->size-1].p_pos = 0;\
    \
    dlink->p_ini = -1;\
    dlink->p_end = -1;\
    return dlink;\
}\
\
static void NAME##_free(NAME *dlink){\
    free(dlink->nodes);\
    free(dlink);\
}\
\
static int NAME##_next(NAME *dlink, int index){\
    if(index<0) return dlink->p_ini;\
    return (index==dlink->p_end)? -1 : dlink->nodes[index]->p_pos;\
}\
\
static int NAME##_prev(NAME *dlink, int index){\
    if(index<0) return dlink->p_end;\
    return (index==dlink->p_ini)? -1 : dlink->nodes[index]->p_pre;\
}\
\
void NAME##_befadd(NAME *dlink, int index, STRU val){\
    assert(dlink->len>0 || index<0);\
    if(dlink->len==dlink->size){\
        dlink->size *= 2;\
        dlink->nodes = (NAME##_n0de *) realloc(dlink->nodes,sizeof(NAME##_n0de)*dlink->size);\
        for(int i=dlink->size/2;i<dlink->size;i++){\
            dlink->nodes[i].p_pre = i-1;\
            dlink->nodes[i].p_pos = i+1;\
        }\
        dlink->nodes[dlink->size/2].p_pre = dlink->p_end;\
        dlink->nodes[dlink->size-1].p_pos = dlink->p_ini;\
        dlink->nodes[dlink->p_ini].p_pre = dlink->size-1;\
        dlink->nodes[dlink->p_end].p_pos = dlink->size/2;\
    }\
    \
    if(index<0){\
        if(dlink->len==0){\
            dlink->p_end = 0;\
            dlink->p_ini = 0;\
        }else{\
            dlink->p_end = dlink->nodes[dlink->p_end]->p_pos;\
        }\
        dlink->nodes[dlink->p_end]->val = val;\
    }else{\
        /*TODO*/ \
    }\
    dlink->len += 1;\
    \
}\
