/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** transformation
*/

#ifndef TRANSFORMATION_H_
    #define TRANSFORMATION_H_
    #define C_SIZE 10
    #include <SFML/Graphics/RenderWindow.h>
typedef struct trans_s
{
    int coord_x;
    int coord_y;
    int *point;
}trans_t;

trans_t *create_trans(void);
#endif /* !TRANSFORMATION_H_ */
