#include <stdio.h>

#include "cadts_vector.h"
#include "cadts_heap.h"
#include "cadts_dlinkedlist.h"

// Create floatvec, a struct that is a vector of floats:
CADTS_VECTOR(floatvec,float)

// Create intheap, a struct that is a heap of ints
// the third argument should be a comparison of "A" and "B", which ints in this case.
CADTS_HEAP(intheap,int,A<B)

// Create intdllist, a struct that is a double linked list of ints.
CADTS_DLINKEDLIST(intdllist,int)

int main(int argc, char const *argv[]){
    printf("TESTING VECTOR:\n");
    floatvec fvec;
    floatvec_init(&fvec,0);
    for(int i=0;i<20;i++){
        floatvec_endadd(&fvec,i);
    }
    for(int i=0;i<10;i++){
        floatvec_endpop(&fvec);
    }
    for(int i=0;i<fvec.len;i++){
        // Access by "items" array, this can only be done with vectors.
        printf("%f ",fvec.items[i]);
    }
    printf("\n");
    floatvec_free(&fvec);
    //
    //
    printf("TESTING HEAP:\n");
    intheap heap;
    intheap_init(&heap,0);
    intheap_add(&heap,5);
    intheap_add(&heap,7);
    intheap_add(&heap,1);
    intheap_add(&heap,4);
    intheap_add(&heap,3);
    for(int i=0;i<3;i++){
        printf("heap lowest: %d\n",intheap_poll(&heap));
    }
    intheap_add(&heap,2);
    intheap_add(&heap,10);
    for(int i=0;i<4;i++){
        printf("heap lowest: %d\n",intheap_poll(&heap));
    }
    intheap_free(&heap);
    //
    //
    printf("TESTING DLINKEDLIST:\n");
    intdllist dlink;
    intdllist_init(&dlink,0);
    // Add values
    for(int i=0;i<10;i++){
        intdllist_endadd(&dlink,i);
        intdllist_iniadd(&dlink,-i);
    }
    // Delete 3 consecutive values:
    int *spoint = intdllist_first(&dlink);
    for(int k=0;k<5;k++) spoint = intdllist_next(&dlink,spoint);
    for(int k=0;k<3;k++){
        // Delete and advance pointer
        spoint = intdllist_del(&dlink,spoint);
    }
    // Add some more values
    for(int i=0;i<5;i++){
        intdllist_endadd(&dlink,100+i);
    }
    // Add some more values
    int last = intdllist_endpop(&dlink);
    printf("last: %d\n",last);
    for(int *ip=intdllist_first(&dlink); ip!=NULL; ip=intdllist_next(&dlink,ip)){
        printf("%d ",*ip);
    }
    printf("\n");
    intdllist_free(&dlink);

    return 0;
}
