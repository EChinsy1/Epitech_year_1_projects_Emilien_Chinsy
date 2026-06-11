#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all tardis tool functions
##

import pandas as pd
from datetime import date


def get_field_value(ser:pd.Series, wanted_type:any) -> any :
    """
    arguments :
    - ser (panda Series), the serie corresponding to the field,
    - wanted_type (type), the type expected for the return value

    if the type of the first value of the serie is the wanted_type, return this value\\
    else return `None`
    """
    val = 0
    for e in ser :
        val = e
        break
    if wanted_type == date and type(val) == pd.Timestamp :
        val = val.date()
    pd_type = wanted_type
    if wanted_type == int :
        pd_type = float
    if type(val) == pd_type :
        if wanted_type == int :
            return int(val)
        return val
    if wanted_type == str :
        return ""
    return None

