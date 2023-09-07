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
    if((key1 == NULL) || (key2 == NULL)) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap *map, char * key, void * value){
  
  if ((map == NULL) || (key == NULL) || (value == NULL)) return; 

  long index = hash(key, map->capacity);

  while ((map -> buckets[index] != NULL) && (map -> buckets[index]->key != NULL) && (strcmp(map->buckets[index]->key, key) != 0)) index = (index + 1) % map -> capacity;

  if (map -> buckets[index] == NULL || map->buckets[index]->key == NULL){
    Pair* pair = (Pair*)malloc(sizeof(Pair));
    if (pair == NULL) return; 
    
        pair -> key = strdup(key);
        pair -> value = value;
        map -> buckets[index] = pair;
        map -> size++;
  }
  map -> current = index;
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)

  if(map == NULL) return;
  Pair** old_buckets = map -> buckets;
  long old_capacity = map -> capacity;

  map -> capacity *= 2;
  map -> buckets = (Pair**)malloc(sizeof(Pair*) * map -> capacity);
  
  if (map -> buckets == NULL){
    map -> capacity = old_capacity;
    return;
  }
  map -> size = 0;
  for (long i = 0; i < old_capacity; i++){
    if ((old_buckets[i] != NULL) && (old_buckets[i] -> key != NULL))
      insertMap(map, old_buckets[i] -> key, old_buckets[i] -> value);      
  }

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

void eraseMap(HashMap * map,  char * key){    
  
  if((map == NULL) || (key == NULL)) return;
  long index = hash(key, map -> capacity);

  while ((map -> buckets[index] != NULL) && ((map -> buckets[index] -> key == NULL) || (strcmp(map -> buckets[index] -> key, key) != 0))) 
    index = (index + 1) % map -> capacity;

  if ((map -> buckets[index] != NULL) && (map -> buckets[index] -> key != NULL) && (strcmp(map -> buckets[index] -> key, key) == 0)){
        map -> buckets[index] -> key = NULL;
        map -> size--;
  }
}

Pair * searchMap(HashMap * map,  char * key) {   

  if((map == NULL) || (key == NULL)) return NULL;
  long index = hash(key, map -> capacity);

  while ((map -> buckets[index] != NULL) && ((map -> buckets[index] -> key == NULL) || (strcmp(map -> buckets[index] -> key, key) != 0))) index = (index + 1) % map -> capacity;
    
   if ((map -> buckets[index] != NULL) && (map -> buckets[index]->key != NULL) && (strcmp(map -> buckets[index] -> key, key) == 0)){
        map -> current = index;
        return map -> buckets[index];
    } else return NULL;
}

Pair * firstMap(HashMap * map){

  if((map == NULL) || (map -> size == 0)) return NULL;
  long index = 0;

  while ((index < map -> capacity) && ((map -> buckets[index] == NULL) || (map -> buckets[index] -> key == NULL))) index++;
  if (index < map -> capacity){
    map -> current = index;
    return map -> buckets[index];
    } 
  else return NULL;
}

Pair * nextMap(HashMap * map) {

  if ((map == NULL) || (map -> size == 0)) return NULL;
  long index = map -> current + 1;

  while ((index < map -> capacity) && ((map -> buckets[index] == NULL) || (map -> buckets[index] -> key == NULL))) index++;

  if (index < map->capacity){
    map -> current = index;
    return map -> buckets[index];
    } 
  else return NULL;
}
