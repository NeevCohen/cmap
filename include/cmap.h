#ifndef CMAP_H
#define CMAP_H

#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_HASHMAP_SIZE 16

typedef size_t (*hash_function)(char*);
typedef bool (*cmp_function)(char*, char*);

struct hash_entry {
    char* key;
    void* data;
    struct hash_entry* next;
};

struct hash_map {
    struct hash_entry** entries;
    size_t size;
    hash_function hash_func;
    cmp_function cmp_func;
};

void *cmap_hash_get(struct hash_map*, char*);
void cmap_hash_set(struct hash_map*, char*, void*);
void cmap_hash_remove(struct hash_map*, char*);
int cmap_hash_map_init(struct hash_map*, size_t, hash_function, cmp_function);
void cmap_hash_map_free(struct hash_map*);


#endif // CMAP_H
