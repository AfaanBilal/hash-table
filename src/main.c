/**
 * Hash Table
 *
 * @author Afaan Bilal
 * @link   https://afaan.dev
 * @link   https://github.com/AfaanBilal/hash-table
 */

#include <stdio.h>

#include "ht/hash_table.h"

int main()
{
    printf("A Hash Table implementation in C\n\n");

    HashTable *ht = HashTable_new();

    HashTable_insert(ht, "k1", "value 1");
    HashTable_insert(ht, "k2", "value 2");
    HashTable_insert(ht, "k3", "value 3");

    printf("k1: %s\n", HashTable_get(ht, "k1"));
    printf("k2: %s\n", HashTable_get(ht, "k2"));
    printf("k3: %s\n", HashTable_get(ht, "k3"));

    printf("\n");

    printf("Key not present: %s\n", HashTable_get(ht, "not present"));
    printf("Key not present with default: %s\n", HashTable_get_default(ht, "not present", "default"));

    printf("\n");
    HashTable_remove(ht, "k1");

    printf("Key removed: %s\n", HashTable_get(ht, "k1"));
    printf("Key removed with default: %s\n", HashTable_get_default(ht, "k1", "default"));

    HashTable_delete(ht);

    return 0;
}
