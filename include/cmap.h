#ifndef CMAP_H
#define CMAP_H

#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_HASHMAP_SIZE 16

typedef size_t (*cmap_hash_function)(char *);
typedef bool (*cmap_cmp_function)(char *, char *);

struct cmap_hash_entry
{
    char *key;
    void *data;
    struct cmap_hash_entry *next;
};

struct cmap_hash_map
{
    struct cmap_hash_entry **entries;
    size_t size;
    cmap_hash_function hash_func;
    cmap_cmp_function cmp_func;
};

void *cmap_hash_get(struct cmap_hash_map *, char *);
void cmap_hash_set(struct cmap_hash_map *, char *, void *);
void cmap_hash_remove(struct cmap_hash_map *, char *);
struct cmap_hash_map *cmap_hash_map_new(size_t, cmap_hash_function, cmap_cmp_function);
int cmap_hash_map_init(struct cmap_hash_map *, size_t, cmap_hash_function, cmap_cmp_function);
void cmap_hash_map_free(struct cmap_hash_map *);

#endif // CMAP_H
