##
## EPITECH PROJECT, 2026
## demography
## File description:
## get sums
##

def sum_big_y(country):
    return sum(country.list.values())

def sum_big_x(country):
    return sum(country.list.keys())

def sum_big_y_squared(country):
    return sum(pop ** 2 for pop in country.list.values())

def sum_big_x_squared(country):
    return sum(year ** 2 for year in country.list.keys()) 

def sum_big_y_and_x(country):
    return sum(year * pop for pop, year in zip(country.list.keys(), country.list.values())) 