/*
** EPITECH PROJECT, 2025
** sprites
** File description:
** a file that handles sprites
*/

#include "my.h"
#include "macros.h"
#include "struct_each_type.h"

static void set_wind_up(birds_t *bird, int i)
{
    if (my_strcmp(bird->type, SUPERSONIC) == 0)
        bird->wind_up_time = EACH_TYPE[i].wind_up;
    else
        bird->wind_up_time = rand() % EACH_TYPE[i].wind_up;
}

static void set_with_struct(birds_t *bird, sfVector2f *pos, int speed)
{
    int i = 0;

    while (EACH_TYPE[i].mov_n_animate != NULL) {
        if (my_strcmp(bird->type, EACH_TYPE[i].type) == 0) {
            bird->height = EACH_TYPE[i].vertical_speed;
            bird->speed = EACH_TYPE[i].base_speed * speed;
            bird->hp = EACH_TYPE[i].hp;
            set_wind_up(bird, i);
            bird->texture = sfTexture_createFromFile(EACH_TYPE[i].sprite, NULL);
        }
        ++i;
    }
    sfSprite_setTexture(bird->sprite, bird->texture, sfTrue);
    sfSprite_setTextureRect(bird->sprite, (sfIntRect)AREA_OF_BIRD);
    sfSprite_setScale(bird->sprite, (sfVector2f)SCALE_OF_BIRD);
    sfSprite_setPosition(bird->sprite, *pos);
}

birds_t *create_bird(int speed, char *type)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f pos = {0, rand() % 800};
    sfClock *clock = sfClock_create();
    sfMusic *music = sfMusic_createFromFile(DEATH_BIRD_SOUND);
    birds_t *bird = malloc(sizeof(birds_t) * 1);

    bird->sprite = sprite;
    bird->size = (sfVector2i)SIZE_OF_BIRD;
    bird->scale = (sfVector2f)SCALE_OF_BIRD;
    bird->sound = music;
    bird->clock = clock;
    bird->spawned = 0;
    bird->type = type;
    set_with_struct(bird, &pos, speed);
    return bird;
}

element_t *create_button(char const *filepath, sfVector2f *pos, int type,
    int (*fptr)(sfRenderWindow *window, sfSprite *cursor, int type))
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);
    sfIntRect area = {0, 0, 25, 10};
    sfMusic *music = sfMusic_createFromFile(BTN_CLICK_SOUND);
    element_t *button = malloc(sizeof(element_t) * 1);

    button->texture = texture;
    button->sprite = sprite;
    button->size = (sfVector2i)SIZE_OF_BUTTON;
    button->scale = (sfVector2f)SCALE_OF_BUTTON;
    button->sound = music;
    button->fptr = fptr;
    button->type = type;
    sfSprite_setTexture(button->sprite, button->texture, sfTrue);
    sfSprite_setTextureRect(button->sprite, area);
    sfSprite_setScale(button->sprite, (sfVector2f)SCALE_OF_BUTTON);
    sfSprite_setPosition(button->sprite, *pos);
    return button;
}

sprite_t *create_sprite(const char *filepath, sfVector2f *scale)
{
    sprite_t *cursor = malloc(sizeof(sprite_t) * 1);
    sfSprite *cursor_sprite = sfSprite_create();
    sfTexture *cursor_texture = sfTexture_createFromFile(filepath, NULL);

    cursor->texture = cursor_texture;
    cursor->sprite = cursor_sprite;
    sfSprite_setTexture(cursor->sprite, cursor->texture, sfTrue);
    sfSprite_setScale(cursor->sprite, *scale);
    return (cursor);
}

void free_sprite(sprite_t *element)
{
    sfSprite_destroy(element->sprite);
    sfTexture_destroy(element->texture);
    free(element);
}
