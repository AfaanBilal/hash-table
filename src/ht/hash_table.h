/**
 * Hash Table
 *
 * @author Afaan Bilal
 * @link   https://afaan.dev
 * @link   https://github.com/AfaanBilal/hash-table
 */

typedef struct
{
    char *key;
    char *value;
} HashItem;

typedef struct
{
    int base_size;
    int size;
    int count;
    HashItem **items;
} HashTable;

HashTable *HashTable_new();
static HashTable *HashTable_new_sized(const int base_size);
static void HashTable_resize_up(HashTable *ht);
static void HashTable_resize_down(HashTable *ht);
void HashTable_delete(HashTable *ht);

void HashTable_insert(HashTable *ht, const char *key, const char *value);
char *HashTable_get(HashTable *ht, const char *key);
char *HashTable_get_default(HashTable *ht, const char *key, char *default_value);
void HashTable_remove(HashTable *h, const char *key);
