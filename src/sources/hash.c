#include "headers/lib.h"
#include <sys/time.h>



void dict_create(dict_t *d, int cap){
    d->bucket = (pair_t **) malloc((cap+1) * sizeof(pair_t*));
    if(d->bucket == NULL){
        fprintf(stderr,"ERrrore");
        exit(1);
    }
    d->cap = cap+1;
    for(int i = 0; i < cap+1; i++){
        d->bucket[i] = NULL;
    }
}

unsigned int hash(unsigned int n) {
    unsigned int hash = 2166136261u;
    hash ^= n;
    hash *= 16777619u;
    return hash;
}
/*
unsigned int hash(int key){
    
    return (unsigned int) key;
}*/

void *dict_get(dict_t *d, type_t key){
    int h = hash(key) % d->cap;
    pair_t *e;
    while(true){
        e = d->bucket[h];

        if(e == NULL){
            return NULL;
        } else if(e->key == key) {
            return e->value;
        }

        h = (h + 1) % d->cap;
    }
    

}

void dict_put(dict_t *d, type_t key, void* value){
    
    pair_t *entry = (pair_t *) malloc(sizeof(pair_t));
    if(entry == NULL){
        fprintf(stderr, "AA");
        exit(1);
    }
    entry->key = key;
    entry->value = value;

    int h = hash(key) % d->cap;
    pair_t *e;
    while(true){    
        
        e = d->bucket[h];
        
        if(e == NULL){
            d->bucket[h] = entry;
            
            return;
        }

        h = (h + 1) % d->cap;
        
    }
}

void dict_destroy(dict_t *d){
    free(d->bucket);
}


/*
int main(){

    
    
    dict_t d;
    dict_create(&d, N);    

    for (int i = 0; i < N; i++)
    {
        int j = (int)random() % (N/2);
        dict_put(&d, j, NULL);
    }
    
    printf("DONE\n");
}*/