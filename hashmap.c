#include "hashmap.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMap HashMap;
int enlarge_called = 0;

struct HashMap {
  Pair **buckets;
  long size;     // cantidad de datos/pairs en la tabla
  long capacity; // capacidad de la tabla
  long current;  // indice del ultimo dato accedido
};

Pair *createPair(char *key, void *value) {
  Pair *new = (Pair *)malloc(sizeof(Pair));
  new->key = key;
  new->value = value;
  return new;
}

long hash(char *key, long capacity) {
  unsigned long hash = 0;
  char *ptr;
  for (ptr = key; *ptr != '\0'; ptr++) {
    hash += hash * 32 + tolower(*ptr);
  }
  return hash % capacity;
}

int is_equal(void *key1, void *key2) {
  if (key1 == NULL || key2 == NULL)
    return 0;
  if (strcmp((char *)key1, (char *)key2) == 0)
    return 1;
  return 0;
}

void insertMap(HashMap *map, char *key, void *value) {
  Pair *newPair = malloc(sizeof(Pair));
  newPair->key = key;
  newPair->value = value;

  long position = hash(key, map->capacity);
  while (map->buckets[position] != NULL) {
    if (position == map->capacity - 1) {
      position = 0;
    } else {
      position = position + 1;
    }
  }
  map->buckets[position] = newPair;
  map->size++;
}

void enlarge(HashMap *map) {
  enlarge_called = 1; // no borrar (testing purposes)
}

HashMap *createMap(long capacity) {
  HashMap *mapa = malloc(sizeof(HashMap));
  mapa->capacity = capacity;
  mapa->buckets = (struct Pair **)malloc(sizeof(struct Pair *) * capacity);
  for (long i = 0; i < capacity; i++) {
    mapa->buckets[i] = NULL;
  }

  mapa->size = 0;
  mapa->current = -1;
  return mapa;
}

void eraseMap(HashMap *map, char *key) {}

Pair *searchMap(HashMap *map, char *key) {
  // Pair *foundPair = malloc(sizeof(Pair));
  long origPosition = hash(key, map->capacity);
  long position = hash(key, map->capacity);
  while (strcmp(key, map->buckets[position]->key) != 0) {
    if (position == origPosition - 1) {
      break;
    } else if (map->buckets[position] != NULL) {
      if (position == map->capacity - 1) {
        position = 0;
      } else {
        position++;
      }
    } else {
      break;
    }
  }

  if (map->buckets[position] != NULL) {
    map->current = position;
  }

  return map->buckets[position];
}

Pair *firstMap(HashMap *map) { return NULL; }

Pair *nextMap(HashMap *map) { return NULL; }
