#include <stdio.h>

#include "cadts_vector.h"
#include "cadts_heap.h"

// Create floatvec, a struct that is a vector of floats:
CADTS_VECTOR(floatvec,float)

// Create intheap, a struct that is a heap of ints
// the third argument should be a comparison of "A" and "B", which ints in this case.
CADTS_HEAP(intheap,int,A<B)

int main(int argc, char const *argv[]){
    printf("VECTOR:\n");
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
    printf("HEAP:\n");
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

    return 0;
}
