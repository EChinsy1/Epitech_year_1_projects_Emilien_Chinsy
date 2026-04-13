#!/usr/bin/env python3
###
## EPITECH PROJECT, 2026
## 109titration
## File description:
## 109titration
##

import unittest
from temp import *

class TestTitration(unittest.TestCase):
    def test_biggest_values(self):
        my_list = [1,2,8,1273,92,-4]
        self.assertEqual(find_max_value(my_list), 4)

    def test_titration_fake_value(self):
        argv = ["109titration", "fake.csv"]
        self.assertEqual(titration(argv), 84)
    
    def test_titration_normal_value(self):
        argv = ["109titration", "values.csv"]
        self.assertEqual(titration(argv), 0)
    
    def test_rate_of_change_error(self):
        self.assertEqual(rate_of_change(1, 1, 1, 1), 0)
    
    def test_rate_of_change(self):
        self.assertEqual(rate_of_change(1, 2, 2, 3), 1)

if __name__ == '__main__':
    unittest.main()