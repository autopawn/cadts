#include <stdio.h>

#include "../cadts_hashtable.h"

// Create loloctable, a hashmap with unsigned long long's as keys and chars as values
// the third argument checks for equality between "A" and "B".
// the fourth argument hashs the key "A".
CADTS_HASHTABLE(loloctable,unsigned long long,char,A==B,(A>>32)^(A))


int main(int argc, char const *argv[]){
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
        printf("KEY %llu VAL '%c'\n",loloctable_iter_key(&it),loloctable_iter_val(&it));
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
        printf("KEY %llu VAL '%c'\n",loloctable_iter_key(&it),loloctable_iter_val(&it));
    }

    printf("poped 600004: '%c'\n",val);
    loloctable_free(htable);
    //
    return 0;
}
