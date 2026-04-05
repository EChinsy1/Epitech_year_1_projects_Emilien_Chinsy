/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** camera
*/

#ifndef CAMERA_H_
    #define CAMERA_H_
    #define CAM_X 0
    #define CAM_Y 1
    #define X 0
    #define Y 1
    #define INIT_PANX 0.0
    #define INIT_PANY 35.0
    #define INIT_CAMX 35
    #define INIT_CAMY 35

typedef struct camera_s
{
    float pan_x;
    float pan_y;
    float cam_x;
    float cam_y;
    int zoom;
}cam_t;

cam_t *create_cam(void);
#endif /* CAMERA_H_ */
