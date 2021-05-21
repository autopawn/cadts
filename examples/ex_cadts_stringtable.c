#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../cadts_stringtable.h"

#define BUFFERSIZE 8

// Create sitable, a hashmap with string keys and int values
CADTS_STRINGTABLE(sitable,int)

int main(int argc, char const *argv[]){
    char str[BUFFERSIZE];

    sitable *table = sitable_init();

    //Put random values
    for(int i=0;i<20;i++){
        // Generate random string
        int len = rand()%(BUFFERSIZE-1);
        for(int k=0;k<len;k++) str[k] = 'a'+rand()%3;
        str[len] = '\0';


        // Add a random number between 0 and 99
        int val = rand()%100;
        if(sitable_has(table,str)){
            printf("REPLACE \"%s\" with %d\n",str,val);
        }else{
            printf("ADD \"%s\" with %d\n",str,val);
        }
        sitable_add(table,str,val);
    }

    printf("\n");

    { // Iterate and print
        sitable_iter iter = sitable_begin(table);
        while(!sitable_iter_done(&iter)){
            const char *key = sitable_iter_key(&iter);
            int val = sitable_iter_val(&iter);
            printf("KEY \"%s\" VALUE %02d\n",key,val);
            // Assert that the key corresponds to the value
            assert(sitable_get(table,key)==val);
            // Advance iterator
            sitable_iter_next(&iter);
        }
    }

    printf("\n");

    // Delete values form the table
    while(sitable_len(table)>3){
        sitable_iter iter = sitable_begin(table);
        // Ask for the key.
        // Be aware that the string cannot be used after the key is poped (or the stringtable freed).
        const char *key = sitable_iter_key(&iter);
        printf("DELETE \"%s\"\n",key);
        sitable_pop(table,key);
    }

    printf("\n");

    { // Iterate and print
        sitable_iter iter = sitable_begin(table);
        while(!sitable_iter_done(&iter)){
            const char *key = sitable_iter_key(&iter);
            int val = sitable_iter_val(&iter);
            printf("KEY \"%s\" VALUE %02d\n",key,val);
            // Assert that the key corresponds to the value
            assert(sitable_get(table,key)==val);
            // Advance iterator
            sitable_iter_next(&iter);
        }
    }

    printf("\n");

    // Free sitable
    sitable_free(table);
}
