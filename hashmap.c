#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap *map, char * key, void * value){
  
  if (map == NULL || key == NULL || value == NULL) return; 

  for (long i = 0; i < map -> capacity; i++){
        long index = (hash(*map, *key) + i) % map -> capacity;
        Pair *currentPair = map -> buckets[index];
        if (currentPair == NULL){
            Pair *newPair = (Pair *)malloc(sizeof(Pair));
            
          if (newPair == NULL) return;
            newPair -> key = strdup(key);
            newPair -> value = value;
            map -> buckets[index] = newPair;
            map -> size++;
            map -> current = index;
            return;
        } else if (strcmp(currentPair->key, key) == 0) return;
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity){

  HashMap* map = (HashMap *) malloc(sizeof(HashMap));
  if(map == NULL) return NULL;

  map -> size = 0;
  map -> capacity = capacity;
  map -> current = -1;

  map -> buckets = (Pair **) malloc(sizeof(Pair* ) *capacity);
  if(map -> buckets == NULL){
    free(map);
    return NULL;
  }

  for(long i = 0; i < capacity; i++){
    map -> buckets[i] = NULL;
  }
  return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
