#include "cmap.h"
#include <mintest.h>
#include <stdio.h>

struct cmap_hash_map *hmap;

void setup_hash_map()
{
    hmap = cmap_hash_map_new(16,    /* size */
                             NULL,  /* hash function*/
                             NULL); /* compare function */
};

void teardown_hash_map()
{
    cmap_hash_map_free(hmap);
};

MINTEST_CASE(test_hash_set_string)
{
    cmap_hash_set(hmap, "foo", (void *)"foo");
    int idx = hmap->hash_func("foo") % hmap->size;
    char *value = hmap->entries[idx]->data;
    mintest_assert_string_eq(value, "foo");
}

MINTEST_CASE(test_hash_set_overwrite_string)
{
    cmap_hash_set(hmap, "foo", (void *)"foo");
    cmap_hash_set(hmap, "foo", (void *)"bar");
    int idx = hmap->hash_func("foo") % hmap->size;
    char *value = hmap->entries[idx]->data;
    mintest_assert_string_eq(value, "bar");
}

MINTEST_CASE(test_hash_get_string)
{
    char *foo = "foo";
    cmap_hash_set(hmap, "foo", foo);
    char *value = cmap_hash_get(hmap, "foo");
    mintest_assert_string_eq(value, foo);
}

MINTEST_CASE(test_hash_remove_string)
{
    cmap_hash_set(hmap, "foo", "foo");
    cmap_hash_remove(hmap, "foo");
    void *value = cmap_hash_get(hmap, "foo");
    mintest_assert(value == NULL);
    for (int i = 0; i < hmap->size; ++i)
    {
        mintest_assert(hmap->entries[i] == NULL);
    }
}

MINTEST_SUITE(test_suite)
{
    MINTEST_SETUP_TEST_SUITE(setup_hash_map, teardown_hash_map);
    MINTEST_RUN_TEST_CASE(test_hash_set_string);
    MINTEST_RUN_TEST_CASE(test_hash_set_overwrite_string);
    MINTEST_RUN_TEST_CASE(test_hash_get_string);
    MINTEST_RUN_TEST_CASE(test_hash_remove_string);
};

int main(void)
{
    MINTEST_SETUP();
    MINTEST_RUN_TEST_SUITE(test_suite);
    MINTEST_REPORT();
    MINTEST_CLEANUP();
    return 0;
}
