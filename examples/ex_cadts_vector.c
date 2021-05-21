#include <stdio.h>

#include "../cadts_vector.h"

// Create floatvec, a struct that is a vector of floats:
CADTS_VECTOR(floatvec,float)

int cmp_floats(const void *a, const void *b){
    return (*(float*)a-*(float*)b);
}


int main(int argc, char const *argv[]){
    //
    printf("VECTOR:\n");
    floatvec *fvec = floatvec_init(0);
    for(int i=0;i<20;i++){
        floatvec_endadd(fvec,20-3*i-2*(i%2));
    }
    for(int i=0;i<10;i++){
        floatvec_endpop(fvec);
    }
    // Print last element
    printf("%.3f\n", floatvec_endtop(fvec));
    // Print vector
    for(int i=0;i< floatvec_len(fvec);i++){
        // Access by "items" array, this can only be done with vectors.
        printf("%.3f ",fvec->items[i]);
    }
    printf("\n");
    // Sort vector acceding by array
    qsort(fvec->items,floatvec_len(fvec),sizeof(float),cmp_floats);
    // Print vector
    for(int i=0;i< floatvec_len(fvec);i++){
        // Access by "items" array, this can only be done with vectors.
        printf("%.3f ",fvec->items[i]);
    }
    printf("\n");
    // Free vector
    floatvec_free(fvec);
    //
    return 0;
}
