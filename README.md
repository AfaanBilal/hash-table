Hash Table
==========

A Hash Table implementation in C.

---

### **Author**: [Afaan Bilal](https://afaan.dev)

---

## Compile &amp; Run

```bash
gcc src/ht/*.c src/main.c -o main && ./main
```

Output:
```
A Hash Table implementation in C

k1: value 1
k2: value 2
k3: value 3

Not present key: (null)
Not present key with default: default

Removed key: (null)
Removed key with default: default
```
---

## Usage

Include the header:
```c
#include "ht/hash_table.h"
```

Create a hash table:
```c
HashTable *ht = HashTable_new();
```

Remember to delete the hash table to free the memory:
```c
HashTable_delete(ht);
```

Insert an item:
```c
HashTable_insert(ht, "key", "value");
```

Get the value:
```c
char *v = HashTable_get(ht, "key"); // returns NULL if key not present
```

Get the value with default:
```c
char *v = HashTable_get_default(ht, "key", "default"); // returns "default" if key not present
```

Remove an item:
```c
HashTable_remove(ht, "key");
```

HashTable will automatically resize based upon load (`<0.1` to resize down with a minimum size of `50`, `>0.7` to resize up).

However, you may create a sized table directly if you know how many items you'll be storing beforehand with:
```c
// Creates a hash table with base size 100 (actual size will be a prime number >= 100)
HashTable *ht = HashTable_new_sized(100);
```

You may also manually resize the table up / down by:
```c
// Resize to roughly double the current size
HashTable_resize_up(ht);

// Resize to roughly half the current size (unless size is already minimum)
HashTable_resize_down(ht);
```

---

## Contributing
All contributions are welcome. Please create an issue first for any feature request
or bug. Then fork the repository, create a branch and make any changes to fix the bug
or add the feature and create a pull request. That's it!
Thanks!

---

## License
**Hash Table** is released under the MIT License.
Check out the full license [here](LICENSE).
