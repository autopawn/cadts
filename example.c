#include <stdio.h>

#include "cadts_vector.h"
#include "cadts_heap.h"
#include "cadts_hashtable.h"

// Create floatvec, a struct that is a vector of floats:
CADTS_VECTOR(floatvec,float)

// Create intheap, a struct that is a heap of ints
// the third argument should be a comparison of "A" and "B", which are ints in this case.
CADTS_HEAP(intheap,int,A<B)

// Create loloctable, a struct with unsigned long long's as keys and chars as values
// the third argument checks for equality between "A" and "B".
// the fourth argument hashs the key "A".
CADTS_HASHTABLE(loloctable,unsigned long long,char,A==B,(A>>32)^(A))


int main(int argc, char const *argv[]){
    //
    //
    printf("VECTOR:\n");
    floatvec *fvec = floatvec_init(0);
    for(int i=0;i<20;i++){
        floatvec_endadd(fvec,i);
    }
    for(int i=0;i<10;i++){
        floatvec_endpop(fvec);
    }
    for(int i=0;i<fvec->len;i++){
        // Access by "items" array, this can only be done with vectors.
        printf("%f ",fvec->items[i]);
    }
    printf("\n");
    floatvec_free(fvec);
    //
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
    //
    printf("HASHTABLE:\n");
    loloctable *htable = loloctable_init();
    loloctable_add(htable,400000,'B');
    loloctable_add(htable,400002,'O');
    loloctable_add(htable,400003,'O');
    loloctable_add(htable,400004,'K');
    loloctable_add(htable,400005,' ');
    loloctable_add(htable,400006,'K');
    loloctable_add(htable,400007,'E');
    loloctable_add(htable,400008,'E');
    loloctable_add(htable,400009,'P');
    loloctable_add(htable,400010,'E');
    loloctable_add(htable,400011,'R');
    char val = loloctable_pop(htable,400004);
    printf("poped 400004: '%c'\n",val);
    loloctable_free(htable);
    //
    //
    return 0;
}
