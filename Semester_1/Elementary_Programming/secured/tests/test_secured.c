/*
** EPITECH PROJECT, 2026
** Secured
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "my.h"
#include "hashtable.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(new_hashtable, basic_creation)
{
    hashtable_t *ht = new_hashtable(&hash, 10);

    cr_assert(ht != NULL && ht->len == 10 && ht->elements[3] == NULL);
}

Test(new_hashtable, basic_fake_creation)
{
    hashtable_t *ht = new_hashtable(NULL, 10);

    cr_assert(ht == NULL);
}

Test(new_hashtable, basic_no_len_creation)
{
    hashtable_t *ht = new_hashtable(&hash, 0);

    cr_assert(ht == NULL);
}

Test(delete_hashtable, basic_hashtable_delete)
{
    hashtable_t *ht = new_hashtable(&hash, 10);

    delete_hashtable(ht);
    cr_assert(1 == 1);
}

Test(delete_hashtable, fake_hashtable_delete)
{
    delete_hashtable(NULL);
    cr_assert(1 == 1);
}

Test(ht_delete, basic_delete)
{
    hashtable_t *ht = new_hashtable(&hash, 10);

    ht_insert(ht, "patestnonplus", "patestnonplus");
    ht_insert(ht, "test", "test");
    ht_insert(ht, "patest", "patest");
    cr_assert_eq(ht_delete(ht, "test"), 0);
}

Test(ht_delete, delete_nothing)
{
    hashtable_t *ht = new_hashtable(&hash, 10);

    cr_assert_eq(ht_delete(ht, "test"), 84);
}

Test(list_add, basic_add_list_null)
{
    list_t **list = NULL;

    cr_assert_eq(list_add(list, "test", 20), -1);
}

Test(print_list, no_list, .init = redirect_all_std)
{
    print_list(NULL);
    cr_assert(1 == 1);
}

Test(list_add, basic_add_chepa)
{
    list_t **list = malloc(sizeof(list_t *) * 1);

    list_add(list, "test", 20);
    cr_assert_eq(list_add(list, "test", 20), 0);
}

Test(list_delete, basic_list_delete)
{
    list_t **list = NULL;

    cr_assert_eq(list_delete(list, 20), 84);
}

Test(ht_dump, basic_ht_dump, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&hash, 1);
    char *return_string = malloc(sizeof(char) * 100);
    sprintf(return_string, "[0]:\n> %d - test\n", hash("key", 1));

    ht_insert(ht, "key", "test");
    ht_dump(ht);
    delete_hashtable(ht);
    cr_assert_stdout_eq_str(return_string);
    free(return_string);
}

Test(ht_dump, no_table)
{
    ht_dump(NULL);
    cr_assert(1 == 1);
}

Test(caca, caca2, .init = redirect_all_std)
{
    write(1, "caca", 4);
    cr_assert_stdout_eq_str("caca");
}

Test(ht_search, basic_search)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    ht_insert(ht, "key", "test");
    cr_assert_str_eq(ht_search(ht, "key"), "test");
}

Test(ht_search, basic_search_help)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    ht_insert(ht, "keyeuh", "testeuh");
    ht_insert(ht, "key", "test");
    ht_insert(ht, "imtuyung", "helfmir");
    cr_assert_str_eq(ht_search(ht, "key"), "test");
}

Test(ht_search, fake_search)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    ht_insert(ht, "key", "test");
    cr_assert(!ht_search(ht, "not_key"));
}

Test(ht_insert, ht_is_NULL)
{
    cr_assert(ht_insert(NULL, "key", "value") == 84);
}

Test(ht_insert, ht_len_is_0)
{
    hashtable_t *ht = new_hashtable(&hash, 0);

    cr_assert(ht_insert(ht, "key", "value") == 84);
}

Test(ht_insert, ht_key_is_NULL)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    cr_assert(ht_insert(ht, NULL, "value") == 84);
}

Test(ht_insert, ht_value_is_NULL)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    cr_assert(ht_insert(ht, "key", NULL) == 84);
}

Test(hash, str_is_null)
{
    cr_assert(hash(NULL, 1) == 84);
}

Test(ht_search, ht_is_null_search)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    cr_assert(!ht_search(NULL, "key"));
}

Test(ht_search, key_is_null_search)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    cr_assert(!ht_search(ht, NULL));
}

Test(ht_search, ht_len_is_0_search)
{
    hashtable_t *ht = new_hashtable(&hash, 0);

    cr_assert(!ht_search(ht, "key"));
}

Test(ht_search, ht_is_null_delete)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    cr_assert(ht_delete(NULL, "key") == 84);
}

Test(ht_search, key_is_null_delete)
{
    hashtable_t *ht = new_hashtable(&hash, 1);

    cr_assert(ht_delete(ht, NULL) == 84);
}

Test(ht_search, ht_len_is_0_delete)
{
    hashtable_t *ht = new_hashtable(&hash, 0);

    cr_assert(ht_delete(ht, "key") == 84);
}

Test(my_strlen, str_is_null)
{
    cr_assert_eq(my_strlen(NULL), 0);
}
