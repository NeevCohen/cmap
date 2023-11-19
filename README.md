# CMAP

A minimal hashmap implimintation written in C.

Cmap includes all of the basic features of a hashmap - 
* Initializing
* Setting values
* Getting values
* Removing values

## How to use it

The most basic usage -

```c
#include <cmap.h>

int main() {
    struct cmap_hash_map *hmap = cmap_hash_map_new(16, NULL, NULL);
    cmap_hash_set(hmap, "foo", "foo");
    char *foo = hash_map_get("foo");
    printf("The value is %s\n", foo);

    return 0;
}
```

This program will produce the following output - 

```
The value is foo
```

## Restrictions

Currently, cmap only supports key type of string, though in the future I do intend to implement a generic version for any type of key.

## Tests

The test in this project are written with the help of the [Mintest library](https://github.com/NeevCohen/mintest)
