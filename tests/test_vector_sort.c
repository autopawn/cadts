#include <stdio.h>
#include "../cadts_vector.h"

int incrementOrder(const int * a, const int * b) {
   return *a - *b;
}

int decrementOrder(const int * a, const int * b) {
   return *b - *a;
}

CADTS_VECTOR(intVector, int)



int main(int argc, char **argv){
    int len = 16;
    intVector *iVec = intVector_init(len);

    for(int i = 0; i < len; ++i){
        intVector_endadd(iVec, rand()%128);
    }

    printf("Un-ordered vector\n");
    for(int i = 0; i < iVec->len; ++i){
        printf("%i ", iVec->items[i]);
    }
    printf("\n\n");

    printf("Incremental order vector\n");
    intVector_sort(iVec, incrementOrder);
    for(int i = 0; i < iVec->len; ++i){
        printf("%i ", iVec->items[i]);
    }
    printf("\n\n");

    printf("Decremental order vector\n");
    intVector_sort(iVec, decrementOrder);
    for(int i = 0; i < iVec->len; ++i){
        printf("%i ", iVec->items[i]);
    }
    printf("\n\n");

    return 0;
}