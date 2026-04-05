/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** the structure for the function pointers
*/

#ifndef STRUCTS_
    #define STRUCTS_

typedef struct flag_holder {
    char flag;
} flag_holder_t;

const struct flag_holder EACH_FLAG[] = {
    {'a'},
    {'l'},
    {'R'},
    {'d'},
    {'t'},
    {'1'}};  

#endif
