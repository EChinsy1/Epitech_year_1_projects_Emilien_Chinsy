/*
** EPITECH PROJECT, 2025
** types_and_colors
** File description:
** a file that holds types and colors
*/

typedef struct types_n_colors {
    char *type;
    void (*fptr)(void *material);
} types_n_colors_t;

const struct types_n_colors TYPES_N_COLORS[] = {
    {"ACTUATOR", &print_actuators},
    {"DEVICE", &print_device},
    {"PROCESSOR", &print_processor},
    {"SENSOR", &print_sensor},
    {"WIRE", &print_wire}
};
