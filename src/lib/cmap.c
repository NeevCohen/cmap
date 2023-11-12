#include "cmap.h"
#include <stdio.h>
#include <string.h>

size_t __default_hash_function(char *key) {
    return strlen(key);
}

bool __default_cmp_function(char *key, char *other_key) {
    return strcmp(key, other_key) == 0 ? true : false;
}

/// @brief Initialize a hashmap
/// @param hmap Pointer to the hashmap to initialize
/// @param size The size of the hashmap, length of it's `entries` array
/// @param hfunc The hashing function to use on the keys of the hashmap
/// @param cfunc The compare function to use when comparing keys of the hashmap
/// @return 0 if succeeded in allocating all of the resources needed for the hashmap, else negative return value
int hash_map_init(struct hash_map* hmap, size_t size, hash_function hfunc, cmp_function cfunc) {
    if (!hmap) {
        printf("[hash_map_init] Error: received null hash map\n");
        return -1;
    }

    if (!hfunc) {
        hfunc = __default_hash_function;
    }

    if (!cfunc) {
        cfunc = __default_cmp_function;
    }

    if (!size) {
        size = DEFAULT_HASHMAP_SIZE;
    }

    hmap->entries = malloc(sizeof(struct hash_entry) * size);
    if (!hmap->entries) {
        printf("[hash_map_init] Error: could not allocated memory for hash map\n");
        return -1;
    }
    
    hmap->hash_func = hfunc;
    hmap->cmp_func = cfunc;
    hmap->size = size;

    return 0;
}

/// @brief Free resources acquired by the hash map
/// @param hmap Pointer to the hashmap to free
void hash_map_free(struct hash_map* hmap) {
    struct hash_entry *hentry, *next;

    if (!hmap) {
        printf("[hash_map_free] Warning: received null hash map\n");
        return;
    }

    for (int i = 0; i < hmap->size; ++i) {
        if (!hmap->entries[i]) {
            continue;
        }

        hentry = hmap->entries[i];
        while (hentry) {
            next = hentry->next;
            hentry->next = NULL;
            free(hentry);
            hentry = next;
        }
    }

    free(hmap->entries);
    hmap->entries = NULL;
}


/// @brief Set key to given value in the hashmap
/// @param hmap Pointer to the hashmap
/// @param key The key to set
/// @param value The value to assign to the key
void hash_set(struct hash_map* hmap, char* key, void* value) {
    /*
    Algorithm - 
    Calculate the hash of the given key, and convert it into an index. Use the index to 
    index into the `enteries` array of the hash_map and check if a value exists for that key. If no entry is set, then set
    the given value to the `data` member of the entry. If there is already an entry for the given key, 
    then create a new `struct hash_entry` and set the existing entry's `next` member to point to the new entry,
    creating a linked list.
    */
    struct hash_entry *hentry, *cursor;

    if (!hmap) {
        printf("[hash_set] Error: received null hash map\n");
        return;
    }

    if (!key) {
        printf("[hash_set] Error: received null key\n");
        return;
    }

    hentry = malloc(sizeof(struct hash_entry));
    
    if (!hentry) {
        printf("[hash_set] Error: cannot allocate new hash entry\n");
        return;
    }

    hentry->key = key;
    hentry->data = value;
    hentry->next = NULL;

    size_t index = hmap->hash_func(key) % hmap->size;  // Since the hash function is user supplied, we can't be sure
    // that the value it returns would be in the range of the entries array, so we modulo it to make sure we don't 
    // access the array out of it's range
    if (!hmap->entries[index]) { // No entry for hash
        hmap->entries[index] = hentry;
    } else { // Entry exists - hash colision
        cursor = hmap->entries[index];
        while(cursor) {
            if (hmap->cmp_func(cursor->key, key)) {
                cursor->data = value;
                return;
            }
            if (!cursor->next) {
                break;
            }
            cursor = cursor->next;
        }
        // here cursor points to the last element in the linked list, and we know it doesn't include the given key
        cursor->next = hentry;
    }
}


void *hash_get(struct hash_map *hmap, char *key)
{
    size_t index;
    struct hash_entry *cursor;

    if (!hmap) {
        printf("[hash_get] Error: received null hash map\n");
    }

    if (!key) {
        printf("[hash_get] Error: received null key\n");
    }

    index = hmap->hash_func(key) % hmap->size;

    if (!hmap->entries[index]) { // No entry for hash
        return NULL;
    } else { // Entry exists - hash colision
        cursor = hmap->entries[index];
        while (cursor) {
            if (hmap->cmp_func(cursor->key, key)) {
                return cursor->data;
            }
            cursor = cursor->next;
        }
        return NULL;
    }
}

void hash_remove(struct hash_map *hmap, char *key)
{
    size_t index;
    struct hash_entry *cursor, *prev = NULL;

    if (!hmap) {
        printf("[hash_get] Error: received null hash map\n");
    }

    if (!key) {
        printf("[hash_get] Error: received null key\n");
    }

    index = hmap->hash_func(key) % hmap->size;

    if (!hmap->entries[index]) { // No entry for hash
        return;
    } else { // Entry exists - hash colision
        cursor = hmap->entries[index];
        while (cursor) {
            if (hmap->cmp_func(cursor->key, key)) {
                if (!prev) { // cursor is the first element in the bucket
                    hmap->entries[index] = cursor->next;
                } else {
                    prev->next = cursor->next;
                }
                free(cursor);
                return;
            }
            prev = cursor;
            cursor = cursor->next;
        }
    }
}