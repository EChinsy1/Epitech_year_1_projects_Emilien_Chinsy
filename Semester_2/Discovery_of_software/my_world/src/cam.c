/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** cam
*/

#include <stdlib.h>
#include <unistd.h>
#include "camera.h"

cam_t *create_cam(void)
{
    cam_t *cam = malloc(sizeof(cam_t));

    if (cam == NULL)
        return NULL;
    cam->pan_x = INIT_PANX;
    cam->pan_y = INIT_PANY;
    cam->cam_x = INIT_CAMX;
    cam->cam_y = INIT_CAMY;
    cam->zoom = 1;
    return cam;
}
