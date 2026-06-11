#!/usr/bin/env bash
##
## EPITECH PROJECT, 2025
## build.sh
## File description:
## a shell file to create my own library
## using any functions I put in the same folder
##

epiclang -c *.c -Wno-implicit-function-declaration
ar rc libmy.a *.o
