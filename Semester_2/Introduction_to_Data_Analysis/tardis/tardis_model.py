#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all function to use the tardis model
##

from pickle import load
from datetime import date, time
from sklearn.ensemble import ExtraTreesRegressor
from enum import Enum
from sys import exit


EPITECH_SUCCESS = 0
EPITECH_FAILURE = 84
MONTH_IN_YEAR = 12
MIN_IN_H = 60
SEC_IN_MIN = 60
SEC_IN_H = MIN_IN_H * SEC_IN_MIN
H_IN_DAY = 24

MODEL = None

TRAIN_SERVICE = Enum("TRAIN_SERVICE", [("National", 1), ("International", 2)])
MODEL_AVAILABLE = True


def minutes_to_time_obj(t_init: float) -> time:
    t_sec = int(round(t_init * SEC_IN_MIN, 0))
    h = t_sec // SEC_IN_H
    t_sec %= SEC_IN_H
    m = t_sec // SEC_IN_MIN
    s = t_sec % SEC_IN_MIN
    if h >= H_IN_DAY:
        return None
    return time(hour=h, minute=m, second=s)


def load_pkl_file(filename: str) -> any:
    try:
        file = open(filename, "r+b")
    except:
        return None
    if file is None:
        return None
    var = load(file=file)
    file.close()
    return var


ROUTE_MEANS = load_pkl_file("route_means.pkl")
DEP_MEANS = load_pkl_file("dep_means.pkl")
ARR_MEANS = load_pkl_file("arr_means.pkl")
GLOBAL_MEAN = load_pkl_file("global_mean.pkl")
DEFAULT_MEAN = -1
MODEL = load_pkl_file("model.pkl")
if None in (ROUTE_MEANS, DEP_MEANS, ARR_MEANS, GLOBAL_MEAN):
    exit(EPITECH_FAILURE)
if type(MODEL) != ExtraTreesRegressor:
    MODEL_AVAILABLE = False


def check_journey_validity(departure: str, arrival: str) -> bool:
    return (departure, arrival) in ROUTE_MEANS


def get_encoded_features(departure: str, arrival: str) -> tuple:
    if (departure, arrival) not in ROUTE_MEANS :
        return None
    route_mean = ROUTE_MEANS[(departure, arrival)]
    if departure not in DEP_MEANS :
        return None
    dep_mean = DEP_MEANS[departure]
    if arrival not in ARR_MEANS :
        return None
    arr_mean = DEP_MEANS[arrival]

    if route_mean is None:
        if dep_mean is not None and arr_mean is not None:
            route_mean = (dep_mean + arr_mean) / 2
        else:
            route_mean = DEFAULT_MEAN
    if dep_mean is None :
        dep_mean = DEFAULT_MEAN
    if arr_mean is None :
        arr_mean = DEFAULT_MEAN
    return route_mean, dep_mean, arr_mean


def question_the_model(
    departure: str, arrival: str, day: date, service: TRAIN_SERVICE
) -> time | None:
    if None in (departure, arrival, day, service):
        return None
    departure = departure.upper()
    arrival = arrival.upper()
    encoded_features = get_encoded_features(departure, arrival)
    if encoded_features is None :
        return None
    if None in encoded_features :
        return None
    route_mean, dep_mean, arr_mean = encoded_features
    raw = MODEL.predict(
        [
            [
                day.month,
                day.year,
                service.value,
                route_mean,
                dep_mean,
                arr_mean,
            ]
        ]
    )[0]

    total_seconds = max(0, int(round(raw * SEC_IN_MIN, 0)))
    h = total_seconds // SEC_IN_H
    m = (total_seconds % SEC_IN_H) // SEC_IN_MIN
    s = total_seconds % SEC_IN_MIN

    if h > 23:
        return None

    return time(hour=h, minute=m, second=s)


def compute_model_confidence() -> time:
    try:
        file = open(".model_error", "r")
    except:
        return None
    mae_str = file.read()
    file.close()
    try:
        mae = float(mae_str)
    except:
        return None
    return minutes_to_time_obj(mae)


if __name__ == "__main__":
    print(
        question_the_model(
            "Paris Montparnasse", "Poitiers", date(2026, 5, 21), TRAIN_SERVICE.National
        )
    )
