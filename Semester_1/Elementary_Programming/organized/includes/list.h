/*
** EPITECH PROJECT, 2025
** G-CPE-110 : Shell Boostrap
** File description:
** bootstrap.h
*/

#ifndef LIST_H_
    #define LIST_H_

typedef struct linked_list_s {
    void *data;
    struct linked_list_s *next;
} linked_list_t;

typedef struct main_struct {
    struct linked_list_s *list;
    int biggest;
} main_t;

#endif
