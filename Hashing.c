#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Entry
{
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct HashTable
{
    Entry *entries[TABLE_SIZE];
} HashTable;

unsigned int hash(const char *key)
{
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i)
    {
        value = value * 37 + key[i];
    }

    value = value % TABLE_SIZE;
    return value;
}

Entry *create_entry(const char *key, const char *value)
{
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->next = NULL;
    return entry;
}

HashTable *create_table()
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        table->entries[i] = NULL;
    }
    return table;
}

void free_entry(Entry *entry)
{
    free(entry->key);
    free(entry->value);
    free(entry);
}

void free_table(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        Entry *entry = table->entries[i];
        while (entry != NULL)
        {
            Entry *temp = entry;
            entry = entry->next;
            free_entry(temp);
        }
    }
    free(table);
}

void ht_insert(HashTable *table, const char *key, const char *value)
{
    unsigned int slot = hash(key);
    Entry *entry = table->entries[slot];

    if (entry == NULL)
    {
        table->entries[slot] = create_entry(key, value);
        return;
    }

    Entry *prev;
    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            free(entry->value);
            entry->value = strdup(value);
            return;
        }
        prev = entry;
        entry = entry->next;
    }

    prev->next = create_entry(key, value);
}

char *ht_search(HashTable *table, const char *key)
{
    unsigned int slot = hash(key);
    Entry *entry = table->entries[slot];

    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void ht_delete(HashTable *table, const char *key)
{
    unsigned int slot = hash(key);
    Entry *entry = table->entries[slot];
    Entry *prev = NULL;

    while (entry != NULL && strcmp(entry->key, key) != 0)
    {
        prev = entry;
        entry = entry->next;
    }

    if (entry == NULL)
    {
        return;
    }

    if (prev == NULL)
    {
        table->entries[slot] = entry->next;
    }
    else
    {
        prev->next = entry->next;
    }

    free_entry(entry);
}

int main()
{
    HashTable *ht = create_table();

    ht_insert(ht, "name", "Alice");
    ht_insert(ht, "age", "25");
    ht_insert(ht, "city", "New York");

    printf("name: %s\n", ht_search(ht, "name"));
    printf("age: %s\n", ht_search(ht, "age"));
    printf("city: %s\n", ht_search(ht, "city"));

    ht_delete(ht, "age");

    printf("age after deletion: %s\n", ht_search(ht, "age"));

    free_table(ht);
    return 0;
}