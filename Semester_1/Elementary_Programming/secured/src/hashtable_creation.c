/*
** EPITECH PROJECT, 2026
** hashtab
** File description:
** Hash fonctiun for Secured
*/

#include "hashtable.h"
#include "my.h"
#include <stdlib.h>

hashtable_t *new_hashtable(int (*hash)(char *, int), int len)
{
    hashtable_t *hashtable = my_calloc(sizeof(hashtable_t), 1);
    list_t **elements = my_calloc(sizeof(list_t *), len + 1);

    if (!hashtable || !elements || !hash || len <= 0)
        return (NULL);
    hashtable->elements = elements;
    hashtable->hash = hash;
    hashtable->len = len;
    return (hashtable);
}

void delete_hashtable(hashtable_t *ht)
{
    if (!ht)
        return;
    for (int i = 0; i < ht->len; ++i) {
        free_list(ht->elements[i]);
    }
    free(ht->elements);
    free(ht);
}
