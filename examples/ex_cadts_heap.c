#include <stdio.h>

#include "../cadts_heap.h"

// Create intheap, a struct that is a heap of ints
// the third argument should be a comparison of "A" and "B", which are ints in this case.
CADTS_HEAP(intheap,int,A<B)

int main(int argc, char const *argv[]){
    //
    printf("HEAP:\n");
    intheap *heap = intheap_init(0);
    intheap_add(heap,5);
    intheap_add(heap,7);
    intheap_add(heap,1);
    intheap_add(heap,4);
    intheap_add(heap,3);
    for(int i=0;i<3;i++){
        printf("heap lowest: %d\n",intheap_poll(heap));
    }
    intheap_add(heap,2);
    intheap_add(heap,10);
    for(int i=0;i<4;i++){
        printf("heap lowest: %d\n",intheap_poll(heap));
    }
    intheap_free(heap);
    //
    return 0;
}
