#include "cmap.h"
#include <stdio.h>

int main(void) {

    int res;
    struct hash_map hmap;

    res = cmap_hash_map_init(&hmap, 16, NULL, NULL);

    if (res < 0) {
        return res;
    }

    cmap_hash_set(&hmap, "hey", (void*)"hi");
    cmap_hash_set(&hmap, "hey", (void*)"hey");
    cmap_hash_set(&hmap, "lol", (void*)"lol");
    printf("Value is %s\n", (char *)cmap_hash_get(&hmap, "hey"));
    cmap_hash_remove(&hmap, "hey");
    printf("Value is %s\n", (char *)cmap_hash_get(&hmap, "lol"));
    cmap_hash_map_free(&hmap);

    return 0;
}
