/**
 * Hash Table
 *
 * @author Afaan Bilal
 * @link   https://afaan.dev
 * @link   https://github.com/AfaanBilal/hash-table
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "prime.h"
#include "hash_table.h"

#define HT_INITIAL_BASE_SIZE 50

static HashItem HashTable_DELETED_ITEM = {NULL, NULL};

static HashTable *HashTable_new_sized(const int base_size)
{
    HashTable *ht = malloc(sizeof(HashTable));

    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(HashItem *));

    return ht;
}

HashTable *HashTable_new()
{
    return HashTable_new_sized(HT_INITIAL_BASE_SIZE);
}

static HashItem *HashTable_new_item(const char *k, const char *v)
{
    HashItem *item = malloc(sizeof(HashItem));

    item->key = strdup(k);
    item->value = strdup(v);

    return item;
}

static void HashTable_delete_item(HashItem *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void HashTable_delete(HashTable *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        HashItem *item = ht->items[i];

        if (item != NULL)
            HashTable_delete_item(item);
    }

    free(ht->items);
    free(ht);
}

static int HashTable_hash(const char *s, const int a, const int m)
{
    long hash = 0;
    const int len_s = strlen(s);

    for (int i = 0; i < len_s; i++)
    {
        hash += (long)pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }

    return (int)hash;
}

static int HashTable_make_hash(const char *s, const int num_buckets, const int attempt)
{
    const int hash_a = HashTable_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = HashTable_hash(s, HT_PRIME_2, num_buckets);

    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

static void HashTable_resize(HashTable *ht, const int base_size)
{
    if (base_size < HT_INITIAL_BASE_SIZE)
        return;

    HashTable *new_ht = HashTable_new_sized(base_size);
    for (int i = 0; i < ht->size; i++)
    {
        HashItem *item = ht->items[i];

        if (item != NULL && item != &HashTable_DELETED_ITEM)
            HashTable_insert(new_ht, item->key, item->value);
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // Swap ht with new_ht
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    HashItem **tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    HashTable_delete(new_ht);
}

static void HashTable_resize_up(HashTable *ht)
{
    const int new_size = ht->base_size * 2;
    HashTable_resize(ht, new_size);
}

static void HashTable_resize_down(HashTable *ht)
{
    const int new_size = ht->base_size / 2;
    HashTable_resize(ht, new_size);
}

void HashTable_insert(HashTable *ht, const char *key, const char *value)
{
    const int load = ht->count * 100 / ht->size;
    if (load > 70)
        HashTable_resize_up(ht);

    HashItem *item = HashTable_new_item(key, value);

    int index = HashTable_make_hash(item->key, ht->size, 0);
    HashItem *cur_item = ht->items[index];

    int attempt = 1;
    while (cur_item != NULL)
    {
        // Overwrite if key exists
        if (cur_item != &HashTable_DELETED_ITEM && strcmp(cur_item->key, key) == 0)
        {

            HashTable_delete_item(cur_item);
            ht->items[index] = item;
            return;
        }

        index = HashTable_make_hash(item->key, ht->size, attempt);
        cur_item = ht->items[index];
        attempt++;
    }

    ht->items[index] = item;
    ht->count++;
}

char *HashTable_get(HashTable *ht, const char *key)
{
    int index = HashTable_make_hash(key, ht->size, 0);
    HashItem *item = ht->items[index];

    int attempt = 1;
    while (item != NULL)
    {
        if (item != &HashTable_DELETED_ITEM && strcmp(item->key, key) == 0)
            return item->value;

        index = HashTable_make_hash(key, ht->size, attempt);
        item = ht->items[index];
        attempt++;
    }

    return NULL;
}

char *HashTable_get_default(HashTable *ht, const char *key, char *default_value)
{
    char *value = HashTable_get(ht, key);

    return value == NULL ? default_value : value;
}

void HashTable_remove(HashTable *ht, const char *key)
{
    const int load = ht->count * 100 / ht->size;
    if (load < 10)
        HashTable_resize_down(ht);

    int index = HashTable_make_hash(key, ht->size, 0);

    HashItem *item = ht->items[index];
    int attempt = 1;
    while (item != NULL)
    {
        if (item != &HashTable_DELETED_ITEM && strcmp(item->key, key) == 0)
        {
            HashTable_delete_item(item);
            ht->items[index] = &HashTable_DELETED_ITEM;
        }

        index = HashTable_make_hash(key, ht->size, attempt);
        item = ht->items[index];
        attempt++;
    }

    ht->count--;
}
