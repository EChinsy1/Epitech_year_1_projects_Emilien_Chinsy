/*
** EPITECH PROJECT, 2025
** entity creation
** File description:
** a file that holds the functions to create entities
*/

#include "my.h"
#include "macros.h"
#include "struct_levels.h"

static void spawn_birds_on_endless(birds_t **birds, int level)
{
    for (int i = 0; i < level; ++i){
        if (i % 9 == 0 && i != 0)
            birds[i] = create_bird(level, "supersonic");
        if (i % 4 == 0 && i != 0)
            birds[i] = create_bird(level, "evil");
        if ((i % 4 != 0 && i % 9 != 0) || i == 0)
            birds[i] = create_bird(level, "normal");
    }
    birds[level] = NULL;
}

static void spawn_birds_on_normal(birds_t **birds, int level)
{
    int j = 0;

    for (int i = 0; i < EACH_LEVEL[level - 1].num_of_supersonics; ++i) {
        birds[j] = create_bird(EACH_LEVEL[level - 1].level_speed, "supersonic");
        ++j;
    }
    for (int i = 0; i < EACH_LEVEL[level - 1].num_of_evils; ++i) {
        birds[j] = create_bird(EACH_LEVEL[level - 1].level_speed, "evil");
        ++j;
    }
    for (int i = 0; i < EACH_LEVEL[level - 1].num_of_normals; ++i) {
        birds[j] = create_bird(EACH_LEVEL[level - 1].level_speed, "normal");
        ++j;
    }
    birds[EACH_LEVEL[level - 1].total_size] = NULL;
}

birds_t **create_birds(int level, int type)
{
    birds_t **birds;

    if (type == INF){
        birds = malloc(sizeof(birds_t *) * (level + 1));
        spawn_birds_on_endless(birds, level);
    } else {
        birds = malloc(sizeof(birds_t *) *
            (EACH_LEVEL[level - 1].total_size + 1));
        spawn_birds_on_normal(birds, level);
    }
    return (birds);
}

void destroy_elements(element_t **elements)
{
    int i = 0;

    while (elements[i]){
        sfTexture_destroy(elements[i]->texture);
        sfSprite_destroy(elements[i]->sprite);
        sfMusic_destroy(elements[i]->sound);
        free(elements[i]);
        ++i;
    }
}

int num_birds(int level, int type)
{
    int num_of_birds = 0;

    if (type == INF)
        num_of_birds = level;
    else
        num_of_birds = EACH_LEVEL[level - 1].total_size;
    return (num_of_birds);
}

void destroy_birds(birds_t **birds, int level, int type)
{
    int num_of_birds = num_birds(level, type);

    if (level == MAX_LEVEL && type == LV)
        return;
    for (int i = 0; i < num_of_birds; ++i){
        if (birds[i] != NULL){
            sfClock_destroy(birds[i]->clock);
            sfTexture_destroy(birds[i]->texture);
            sfSprite_destroy(birds[i]->sprite);
            sfMusic_destroy(birds[i]->sound);
            free(birds[i]);
            birds[i] = NULL;
        }
    }
    free(birds);
}
