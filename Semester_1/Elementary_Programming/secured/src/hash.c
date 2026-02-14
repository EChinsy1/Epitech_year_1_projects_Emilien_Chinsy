/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** Hash fonctiun for Secured
*/

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "hashtable.h"
#include "macro.h"
#include "my.h"

int hash(char *str, int len)
{
    int p = PRIME_NUMBER;
    int m = __INT_MAX__;
    long long int hash = 0;
    int power = 1;
    int bit_shift = 1;

    if (str == NULL)
        return (84);
    for (int i = 0; i < my_strlen(str); ++i) {
        hash = (((hash + (str[i] * (str[i] - len))) * power));
        hash = hash * i - (power * power);
        hash = hash % m;
        power = (power * p);
    }
    if (hash < 0){
        hash = hash * (-1);
    }
    return (hash);
}

int ht_delete(hashtable_t *ht, char *key)
{
    int hash = 0;

    if (ht == NULL || ht->len == 0 || key == NULL)
        return (84);
    hash = ht->hash(key, ht->len);
    return (list_delete(&ht->elements[hash % ht->len], hash));
}

char *ht_search(hashtable_t *ht, char *key)
{
    size_t hash = 0;
    list_t *current = NULL;

    if (ht == NULL || ht->len == 0 || key == NULL)
        return (NULL);
    hash = ht->hash(key, ht->len);
    current = ht->elements[hash % ht->len];
    for (; current; current = current->next) {
        if (current->hash == hash)
            return (current->value);
    }
    return (NULL);
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int hash = 0;

    if (ht == NULL || ht->len == 0 || key == NULL || value == NULL)
        return (84);
    hash = ht->hash(key, ht->len);
    return (list_add(&ht->elements[hash % ht->len], value, hash));
}

void ht_dump(hashtable_t *ht)
{
    if (ht == NULL)
        return;
    for (int i = 0; i < ht->len; ++i) {
        write(1, "[", 1);
        my_put_nbr(i);
        write(1, "]:\n", 3);
        print_list(ht->elements[i]);
    }
}
