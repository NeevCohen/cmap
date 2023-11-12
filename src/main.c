#include "cmap.h"
#include <stdio.h>

int main(void) {

    int res;
    struct hash_map hmap;

    res = hash_map_init(&hmap, 16, NULL, NULL);

    if (res < 0) {
        return res;
    }

    hash_set(&hmap, "hey", (void*)"hi");
    hash_set(&hmap, "hey", (void*)"hey");
    hash_set(&hmap, "lol", (void*)"lol");
    printf("Value is %s\n", (char *)hash_get(&hmap, "hey"));
    hash_remove(&hmap, "hey");
    printf("Value is %s\n", (char *)hash_get(&hmap, "lol"));
    hash_map_free(&hmap);

    return 0;
}
