##
## EPITECH PROJECT, 2026
## 105demography
## File description:
## file to math out the rms, a, and b
##

import math
from class_def import *
from get_sums import *

def get_sign(number):
    if number < 0:
        return("-")
    return("+")

def get_pop_in_2050(a, b, country, fit):
    final_value = 0

    if fit == 1:
        final_value += a * 2050 + b
    else:
        final_value += (2050 - b) / a
    return final_value

def get_number_values(country):
    n = 0

    for values in country.list.keys():
        n += 1
    return n

def make_predicted_values(country, a, b, fit):
    predicted_pop = []
    residual_pop = []

    if fit == 1:
        predicted_pop = [a * x + b for x in country.list.keys()]
        residual_pop = [real - pred for real, pred in zip(country.list.values(), predicted_pop)]
        residual_pop = [residual ** 2 for residual in residual_pop]
    else:
        predicted_pop = [((x - b) / a) for x in country.list.keys()]
        residual_pop = [real - pred for real, pred in zip(country.list.values(), predicted_pop)]
        residual_pop = [residual ** 2 for residual in residual_pop]
    return predicted_pop, residual_pop

def find_rms_fit_1(country):
    N = get_number_values(country)
    a = 0
    b = 0
    sum_x = sum_big_x(country)
    sum_y = sum_big_y(country)
    sum_x_sq = sum_big_x_squared(country)
    sum_x_y = sum_big_y_and_x(country)
    predicted_pop = []
    residual_pop = []
    rms = 0

    a = (((N * sum_x_y) - (sum_x * sum_y)) / ((N * sum_x_sq) - (sum_x ** 2)))
    b = ((sum_y * sum_x_sq - sum_x * sum_x_y) / (N * sum_x_sq - sum_x ** 2))
    predicted_pop, residual_pop = make_predicted_values(country, a, b, 1)
    rms = math.sqrt(sum(residual_pop) / N)
    print(f"\tY = {a:.2f} X {get_sign(b)} {abs(b):.2f}")
    print(f"\tRoot-mean-square deviation: {rms:.2f}")
    print(f"\tPopulation in 2050: {get_pop_in_2050(a, b, country, 1):.2f}")

def find_rms_fit_2(country):
    N = get_number_values(country)
    a = 0
    b = 0
    sum_x = sum_big_x(country)
    sum_y = sum_big_y(country)
    sum_y_sq = sum_big_y_squared(country)
    sum_x_y = sum_big_y_and_x(country)
    predicted_pop = []
    residual_pop = []
    rms = 0

    a = (((N * sum_x_y) - (sum_y * sum_x)) / ((N * sum_y_sq) - (sum_y ** 2)))
    b = ((sum_x * sum_y_sq - sum_y * sum_x_y) / (N * sum_y_sq - sum_y ** 2))
    predicted_pop, residual_pop = make_predicted_values(country, a, b, 2)
    rms = math.sqrt(sum(residual_pop) / N)
    print(f"\tX = {a:.2f} Y {get_sign(b)} {abs(b):.2f}")
    print(f"\tRoot-mean-square deviation: {rms:.2f}")
    print(f"\tPopulation in 2050: {get_pop_in_2050(a, b, country, 2):.2f}")