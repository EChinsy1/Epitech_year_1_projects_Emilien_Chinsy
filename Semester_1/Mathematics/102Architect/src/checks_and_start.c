/*
** EPITECH PROJECT, 2025
** main
** File description:
** handles parsing and executes functions
*/

#include "my.h"
#include "struct.h"

int show_help(void)
{
    printf("USAGE\n");
    printf("\t./102architect x y ");
    printf("transfo1 arg11 [arg12] [transfo2 arg21 [arg22]] ...");
    printf("\n\n\nDESCRIPTION\n");
    printf("\tx\tabscissa of the original point\n");
    printf("\ty\tordinate of the original point\n");
    printf("\ttransfo arg1 [arg2]\n");
    printf("\t-t i j\ttranslation along vector (i, j)\n");
    printf("\t-z m n\tscaling by factors m (x-axis) and n (y-axis)\n");
    printf("\t-r d\trotation centered in 0 by a d degree angle\n");
    printf("\t-s d\treflection over the axis passing ");
    printf("though 0 with an inclination angle of d degrees\n");
    return (0);
}

static int isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if ((str[i] <= 57 && str[i] >= 48) || str[i] == 45
            || str[i] == 46){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}

static int flag_exists(char **argv, int i, int argc)
{
    int j = 0;

    if (argc - i == 1)
        return (84);
    while (ONE_ARG[j] != '\0'){
        if (ONE_ARG[j] == argv[i][1] && isnum(argv[i + 1]) == 1)
            return (1);
        ++j;
    }
    j = 0;
    if (argc - i == 2)
        return (84);
    while (EACH_MATH_FUNC[j].flag){
        if (EACH_MATH_FUNC[j].flag == argv[i][1]
            && isnum(argv[i + 1]) == 1
            && isnum(argv[i + 2]) == 1)
            return (2);
        ++j;
    }
    return (84);
}

int verify_args(int argc, char **argv)
{
    int increase = 0;

    if (argc < 5)
        return (84);
    if (isnum(argv[1]) != 1 || isnum(argv[2]) != 1)
        return (84);
    for (int i = 3; i < argc; ++i){
        if (argv[i][0] == '-') {
            increase = flag_exists(argv, i, argc);
        } else
            return (84);
        if (increase == 84)
            return (84);
        i += increase;
    }
    return (1);
}

float **free_matrix(float **matrix, int size)
{
    for (int i = 0; i < size; ++i)
        free(matrix[i]);
    free(matrix);
    matrix = NULL;
    return (matrix);
}

float **do_operation(float **matrix, int *i, char **av)
{
    int j = 0;

    while (ONE_ARG[j] != '\0'){
        if (ONE_ARG[j] == av[*i][1]) {
            matrix = EACH_MATH_FUNC[j].fptr(atof(av[*i + 1]), 0.00);
            *i = *i + 1;
            return (matrix);
        }
        ++j;
    }
    j = 0;
    while (EACH_MATH_FUNC[j].flag){
        if (EACH_MATH_FUNC[j].flag == av[*i][1]) {
            matrix = EACH_MATH_FUNC[j].fptr(atof(av[*i + 1]), atof(av[*i + 2]));
            *i = *i + 2;
            return (matrix);
        }
        ++j;
    }
    return (NULL);
}

static int final_print(float **final_matrix, float *vector, float *final_vector)
{
    for (int i = 0; i < 3; ++i)
        printf("%-8.2f%-8.2f%.2f\n",
            final_matrix[i][0],
            final_matrix[i][1],
            final_matrix[i][2]);
    printf("(%.2f, %.2f) => (%.2f, %.2f)\n",
        vector[0],
        vector[1],
        final_vector[0],
        final_vector[1]);
    free_matrix(final_matrix, 3);
    free(vector);
    free(final_vector);
    return (0);
}

static int matrix_operations(int argc, char **argv, float ***matrix,
    float ***final_matrix)
{
    for (int i = 3; i < argc; ++i){
        if (i == 3) {
            (*final_matrix) = do_operation((*final_matrix), &i, argv);
        } else {
            *matrix = do_operation(*matrix, &i, argv);
            *final_matrix = multiply_matrix_real(*matrix, *final_matrix);
            free_matrix(*matrix, 3);
        }
    }
    return (0);
}

int architect(int argc, char **argv)
{
    float *vector = NULL;
    float *final_vector = NULL;
    float **matrix = NULL;
    float **final_matrix = NULL;
    int args_valid = 0;

    if (argc == 2 && strcmp(argv[1], "-h") == 0)
        return (show_help());
    args_valid = verify_args(argc, argv);
    if (args_valid != 1)
        return (args_valid);
    vector = create_vector(atof(argv[1]), atof(argv[2]), 1);
    matrix_operations(argc, argv, &matrix, &final_matrix);
    final_vector = multiply_matrix_1(vector, final_matrix);
    return (final_print(final_matrix, vector, final_vector));
}
