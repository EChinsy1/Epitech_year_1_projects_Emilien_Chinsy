/*
** EPITECH PROJECT, 2025
** 101pong
** File description:
** math module exercise 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "struct.h"
#include "my.h"

void make_vector(double x, double y, double z, vector_t *vector)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void make_velocity(vector_t *coords,
    vector_t *coords2,
    vector_t *velocity)
{
    velocity->x = coords2->x - coords->x;
    velocity->y = coords2->y - coords->y;
    velocity->z = coords2->z - coords->z;
}

static void coords_t_plus_n(vector_t *coords_init,
    vector_t *velocity,
    int n,
    vector_t *coords_end)
{
    coords_end->x = (coords_init->x + (velocity->x * n));
    coords_end->y = (coords_init->y + (velocity->y * n));
    coords_end->z = (coords_init->z + (velocity->z * n));
}

double calc_norm(vector_t *vector)
{
    return (sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2)));
}

double calc_angle(vector_t *vector)
{
    return (asin(fabs(vector->z) / calc_norm(vector)) * (180 / M_PI));
}

static int touches_paddle(vector_t *coords, vector_t *coords_plus_n)
{
    if (coords->z > 0 && coords_plus_n->z < 0)
        return (1);
    if (coords->z < 0 && coords_plus_n->z > 0)
        return (1);
    if (coords->z == 0 || coords_plus_n->z == 0)
        return (1);
    return (0);
}

static int show_help(void)
{
    printf("USAGE\n    ./101pong x0 y0 z0 x1 y1 z1 n");
    printf("\n\n\nDESCRIPTION\n    x0  ball abscissa at time t - 1");
    printf("\n    y0  ball ordinate at time t - 1");
    printf("\n    z0  ball altitude at time t - 1");
    printf("\n    x1  ball abscissa at time t");
    printf("\n    y1  ball ordinate at time t");
    printf("\n    z1  ball altitude at time t\n    ");
    printf("n   time shift (greater than or equal to zero, integer)\n");
    return 0;
}

static void show_result(vector_t *velocity,
    vector_t *coords_n,
    vector_t *coords_1,
    char *n)
{
    printf("The velocity vector of the ball is:\n");
    printf("(%.2f, %.2f, %.2f)\n", velocity->x, velocity->y, velocity->z);
    printf("At time t + %d, ball coordinates will be:\n", atoi(n));
    printf("(%.2f, %.2f, %.2f)\n", coords_n->x, coords_n->y, coords_n->z);
    if (touches_paddle(coords_1, coords_n) &&
        (coords_n->z == 0 && coords_1->z == 0)){
        printf("The incidence angle is:\n0.00 degrees\n");
    } else if (touches_paddle(coords_1, coords_n)){
        printf("The incidence angle is:\n%.2f degrees\n", calc_angle(velocity));
    } else {
        printf("The ball won't reach the paddle.\n");
    }
}

int pong(int argc, char **argv)
{
    vector_t coords_0;
    vector_t coords_1;
    vector_t velocity;
    vector_t coords_n;

    if (argc == 2 && strcmp(argv[1], "-h") == 0){
        return (show_help());
    }
    if (argc != 8 || my_argv_is_valid(argc, &argv[1]) == 0){
        return (84);
    }
    make_vector(atof(argv[4]), atof(argv[5]), atof(argv[6]), &coords_1);
    make_vector(atof(argv[1]), atof(argv[2]), atof(argv[3]), &coords_0);
    make_velocity(&coords_0, &coords_1, &velocity);
    coords_t_plus_n(&coords_1, &velocity, atoi(argv[7]), &coords_n);
    show_result(&velocity, &coords_n, &coords_1, argv[7]);
    return (0);
}
