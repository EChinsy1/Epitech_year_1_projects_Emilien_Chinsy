/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** main header file of the project
*/

#ifndef DATAFRAME_
    #define DATAFRAME_

    #include <stdbool.h>

    #define EPITECH_SUCCESS 0
    #define EPITECH_FAILURE 1

typedef enum {
    BOOL,
    UINT,
    INT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

    #define _UINT "unsigned int"
    #define _UDF "undefined"
    #define _STR "string"
    #define TYPES_NAMES ((char *[6]){"bool", _UINT, "int", "float", _STR, _UDF})
    #define TYPES_FLAGS ((char *[6]){"", "%u", "%i", "%f", "%s", "%p"})
    #define _SBOOL sizeof(bool)
    #define _SUINT sizeof(unsigned int)
    #define _SINT sizeof(int)
    #define _SFLOAT sizeof(double)
    #define _SSTR sizeof(char *)
    #define _SUDF sizeof(void *)
    #define TYPES_SIZE ((int[6]){_SBOOL, _SUINT, _SINT, _SFLOAT, _SSTR, _SUDF})

    #define STRUE "true"
    #define SFALSE "false"
    #define BOOL_TO_STR(b) ((b) ? (STRUE) : (SFALSE))
    #define BOOL_TO_NBR(b) ((b) ? (1) : (0))

typedef struct {
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_types;
    void ***data;
    char *separator;
} dataframe_t;

typedef struct {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

// standard functions
dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *dataframe, const char *filename);

// basic tools functions
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *dataframe);
dataframe_shape_t df_shape(dataframe_t *dataframe);
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);
// dataframe_t *bigger_df_tail_n_head(dataframe_t *dataframe,
//     dataframe_t *df, int nb_rows, int size);

dataframe_t *set_head_values(dataframe_t *dataframe, dataframe_t *head,
    int nb_rows);

// advanced tools functions
dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *));
dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *, void *));
dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **, int));
dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *));
dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast);

// utilitiy functions
void *df_get_value(dataframe_t *dataframe, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);
void **df_get_unique_values(dataframe_t *dataframe, const char *column);

// destroy and free functions
void *free_two_ptrs(void *ptr1, void *ptr2);
void free_and_reset(void **ptr);
void free_array(void **arr);
void df_free(dataframe_t *df);

// tools functions
int index_of_str_arr(char **arr, char *str);
void *cpy_data(void *data, column_type_t type);
int data_dup(dataframe_t *df, dataframe_t *df_new, int row_init, int row_new);
dataframe_t *init_new_df(dataframe_t *dataframe);
int arr_len(void **arr);
void *cast_the_right_type(char *fake_value, column_type_t type);
int arr_len(void **arr);
bool is_in_arr(void *item, void **arr, column_type_t type);
bool are_values_eq(void *value1, void *value2, column_type_t type);
bool is_a_bool(char *str);
void remove_trailing_newline(char *str);

// convertion tools functions
char *to_lower(char *str);
int get_int_part(double nbr);
int iround(double nbr);
void *convert_nbr_from_str(char *str, column_type_t type);
int get_nbr_digits(int nbr);

// compare
int my_strcmp(char *str1, char *str2);

#endif /* DATAFRAME_ */
