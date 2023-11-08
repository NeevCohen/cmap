#include "cmap.h"
#include <stdio.h>

int main(void) {

    int res;
    struct hash_map hmap;

    res = hash_map_init(&hmap, 16, NULL, NULL);

    if (res < 0) {
        return res;
    }

    hash_set(&hmap, "hey", (void*)"hello");
    hash_set(&hmap, "jjj", (void*)"there");
    printf("[main] hmap value is %s\n", (char*)hmap.entries[3]->next->data);
    hash_map_free(&hmap);
    printf("[main] hmap entries is %p\n", hmap.entries);

    return 0;
}
