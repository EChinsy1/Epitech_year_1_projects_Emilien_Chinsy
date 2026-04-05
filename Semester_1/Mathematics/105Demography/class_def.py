##
## EPITECH PROJECT, 2026
## demography
## File description:
## class definition
##

class Country:
    def __init__(self, name, small):
        self.name = name
        self.small = small
        self.list = {}
    
    def fill_list(self, list, empty):
        i = 0
        year = 1960
        for item in list:
            if (i > 1 and empty == 0):
                if (item != ".." and item != ""):
                    self.list[year] = int(item) * 10**-6
                year = year + 1
            if (i > 1 and empty > 0):
                if (item != ".." and item != ""):
                    self.list[year] += int(item) * 10**-6
                year = year + 1
            i += 1