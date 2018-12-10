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
    for(int i=0;i< floatvec_getLength(fvec);i++){
        // Access by "items" array, this can only be done with vectors.
        printf("%f ",floatvec_getItem(fvec, i));
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
    loloctable_add(htable,600000,'B');
    loloctable_add(htable,600002,'O');
    loloctable_add(htable,600003,'O');
    loloctable_add(htable,600004,'K');
    loloctable_add(htable,600005,' ');
    loloctable_add(htable,600006,'K');
    loloctable_add(htable,600007,'E');
    loloctable_add(htable,600008,'E');
    loloctable_add(htable,600009,'P');
    loloctable_add(htable,600010,'E');
    loloctable_add(htable,600011,'R');
    char val = loloctable_pop(htable,600004);
    printf("poped: '%c'\n",val);
    // Test iterator:
    for(loloctable_iter it=loloctable_begin(htable); !loloctable_iter_done(&it); loloctable_iter_next(&it)){
        printf("KEY '%llu' VAL '%c'\n",loloctable_iter_key(&it),loloctable_iter_val(&it));
    }
    // Delete something
    loloctable_pop(htable,600002);
    loloctable_pop(htable,600005);
    loloctable_pop(htable,600006);
    loloctable_pop(htable,600007);
    loloctable_pop(htable,600009);
    loloctable_pop(htable,600010);
    printf("poped several\n");
    // Iterate again:
    for(loloctable_iter it=loloctable_begin(htable); !loloctable_iter_done(&it); loloctable_iter_next(&it)){
        printf("KEY '%llu' VAL '%c'\n",loloctable_iter_key(&it),loloctable_iter_val(&it));
    }

    printf("poped 600004: '%c'\n",val);
    loloctable_free(htable);
    //
    //
    return 0;
}
