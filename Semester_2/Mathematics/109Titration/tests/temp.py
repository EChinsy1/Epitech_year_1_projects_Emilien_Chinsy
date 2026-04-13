#!/usr/bin/env python3
###
## EPITECH PROJECT, 2026
## 109titration
## File description:
## 109titration
##

import csv
import sys
import os

def find_max_value(list):
    index_max = 0
    curr_max = float('-inf')
    i = 0

    for value in list:
        if value > curr_max:
            curr_max = value
            index_max = i
        i = i + 1
    return (index_max + 1)


def rate_of_change(x0, fx0, x1, fx1):
    if ((x1 - x0) == 0):
        return 0
    return (fx1 - fx0) / (x1 - x0)

def derivative_estimation(x0, fx0, x1, fx1, x2, fx2):
    weight_a = x2 - x1
    weight_b = x1 - x0
    rate_1 = rate_of_change(x0, fx0, x1, fx1)
    rate_2 = rate_of_change(x1, fx1, x2, fx2)
    result = (weight_a * rate_1 + weight_b * rate_2) / (weight_a + weight_b)

    return result

def linear_approximation(x0, fx0, x1, fx1, x):
    if x1 == x0:
        return fx0
    if fx1 == fx0:
        return fx0
    return fx0 + (x - x0) / (x1 - x0) * (fx1 - fx0)

def estimate_second_derivative(vol, derive_2, index_max):
    print("\nSecond derivative estimated:")
    vol_d2 = [vol[i + 2] for i in range(len(derive_2))]
    if index_max <= 0 or index_max >= len(vol) - 1:
        return
    start = vol[index_max - 1]
    end = vol[index_max + 1]
    x_values = []
    y_values = []
    x = start
    while x <= end:
        for i in range(len(vol_d2) - 1):
            if vol_d2[i] <= x <= vol_d2[i + 1]:
                y = linear_approximation(vol_d2[i], derive_2[i], vol_d2[i + 1], derive_2[i + 1], x)
                x_values.append(x)
                y_values.append(y)
                print(f"{x:.1f} ml -> {y:.2f}")
                break
        x += 0.1
    eq_point = None
    for i in range(len(y_values) - 1):
        y0 = y_values[i]
        y1 = y_values[i + 1]
        x0 = x_values[i]
        x1 = x_values[i + 1]
        if y0 == 0:
            eq_point = x0
            break
        elif y0 * y1 < 0:
            eq_point = x0 - y0 * (x1 - x0) / (y1 - y0)
            break
    if eq_point is not None:
        print(f"\nEquivalence point at {eq_point:.1f} ml")

def titration(argv):
    i = 0
    if (len(argv) != 2 or not os.path.exists(argv[1])):
        return (84)
    with open(argv[1], newline='') as csvfile:
        vol = []
        ph = []
        derive_1 = []
        derive_2 = []
        index_max = 0
        csvfile = csv.reader(csvfile, delimiter=';', quotechar='|')
        try:
            for value in csvfile:
                if len(value) != 2:
                    return 84
                vol.append(float(value[0]))
                ph.append(float(value[1]))
        except:
            return 84
        if len(vol) <= 0 or len(ph) <= 0:
            return 84
        for i in range (0, len(vol), 1):
            if vol[i] < 0:
                return 84
        for i in range (1, len(vol), 1):
            if vol[i] <= vol[i - 1]:
                return 84
        for i in range (0, len(ph), 1):
            if ph[i] < 0 or ph[i] > 14:
                return 84
        print("Derivative:")
        for i in range (1, len(vol) - 1, 1):
            derive_1.append(derivative_estimation(vol[i - 1], ph[i - 1], vol[i], ph[i], vol[i + 1], ph[i + 1]))
            print(f"{vol[i]} ml -> {derive_1[i - 1]:.2f}")
        index_max = find_max_value(derive_1)
        print()
        print("Equivalence point at", vol[index_max], "ml")
        print()
        print("Second derivative:")
        for i in range(1, len(derive_1) - 1):
            d2 = derivative_estimation(vol[i], derive_1[i - 1], vol[i + 1], derive_1[i], vol[i + 2], derive_1[i + 1])
            derive_2.append(d2)
            print(f"{vol[i + 1]:.1f} ml -> {d2:.2f}")
        estimate_second_derivative(vol, derive_2, index_max)
    return (0)
