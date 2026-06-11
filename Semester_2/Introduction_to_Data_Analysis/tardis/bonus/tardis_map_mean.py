#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all functions to create the map showing the mean delays
##

import pandas as pd
import folium as flm
from datetime import date
from tqdm import trange
from os import getcwd, chdir
from tardis_tools import get_field_value
from bonus.tardis_map_today import set_cwd, EPITECH_SUCCESS, EPITECH_FAILURE, \
    GET_NBR_ROWS, MONTH_IN_YEAR, STATION_ICON, LINE_WEIGHT, init_map, \
    get_stations_data, get_color, min_to_time
from tardis_model import load_pkl_file

set_cwd()

DEFAULT_MAX_DATA_AGE = 36
FILENAME = "maps/map_mean.html"


def get_station_dep_delay(csv:pd.DataFrame, station:str, max_data_age:float) -> float :
    """
    arguments :
    - csv (panda DataFrame), the dataset
    - station (str), the station name
    - max_data_age (float)

    return the average delay of all trains at departure of this station regardless of there destination
    """
    mean = 0
    n = 0
    today = date.today().year * MONTH_IN_YEAR + date.today().month
    rows = csv.query(f"`Year` * {MONTH_IN_YEAR} + `Month` <= { \
        today - max_data_age} & `Departure station` == '{station.upper()}'")

    for i in range(GET_NBR_ROWS(rows)) :
        tmp = get_field_value(rows.iloc[[i]]["Average delay of all trains at departure"], float)
        if type(tmp) not in (int, float) :
            continue
        n += 1
        mean += tmp
    if n <= 0 :
        return -1
    return mean / n


def check_route(row:pd.Series, stations:tuple[str, str]) -> bool :
    """
    arguments :
        - row (panda Series), the row content
        - stations ((departure, arrival) tuple)

    return True if
    """
    s1, s2 = stations
    s1, s2 = s1.upper(), s2.upper()
    dep = get_field_value(row["Departure station"], str)
    arr = get_field_value(row["Arrival station"], str)
    if type(dep) != str or type(arr) != str:
        return False
    return (dep.upper(), arr.upper()) == (s1, s2) or (dep.upper(), arr.upper()) == (s2, s1)


def get_route_mean_delay(csv:pd.DataFrame, stations:tuple[str, str], max_data_age:float) -> float :
    mean = 0
    n = 0
    s1, s2 = stations[0].upper(), stations[1].upper()
    today = date.today().year * MONTH_IN_YEAR + date.today().month
    rows = csv.query(f"`Year` * {MONTH_IN_YEAR} + `Month` <= { \
        today - max_data_age} & (`Departure station` == '{s1 \
        }' & `Arrival station` == '{s2}') | (`Departure station` == '{s2 \
        }' & `Arrival station` == '{s1}')")

    if s1 == s2 :
        return -1
    for i in range(GET_NBR_ROWS(rows)) :
        tmp = get_field_value(rows.iloc[[i]]["Average delay of all trains at arrival"], float)
        if type(tmp) not in (int, float) :
            continue
        n += 1
        mean += tmp
    if n <= 0 :
        return -1
    return mean / n


def draw_stations(map:flm.Map, csv:pd.DataFrame, \
    stations:dict[str:tuple[float, float]], max_data_age:float) -> None :
    """
    arguments :
    - map (folium Map), the map object
    - csv (panda DataFrame), the dataframe
    - stations ({str : (float, float)} dict), the stations data
    - max_data_age (float)

    draw the stations markers on the map\\
    doesn't return anything
    """
    print("Draw stations")
    names = list(stations.keys())
    for i in trange(0, len(names), 1) :
        k = names[i]
        delay = get_station_dep_delay(csv, k, max_data_age)
        c = get_color(delay)
        if c == "yellow":
            c = "beige"
        if delay < 0 :
            popup = f"{k} : NaN"
        else :
            popup = f"{k} : {min_to_time(delay)}"
        flm.Marker(location=list(stations[k]),
            icon=flm.Icon(color=c, prefix="fa", icon=STATION_ICON),
            popup=flm.Popup(popup, max_width=None)).add_to(map)


def draw_routes(map:flm.Map, csv:pd.DataFrame, \
    stations:dict[str : tuple[float, float]], max_data_age:float) -> None:
    """
    arguments :
    - map (folium Map), the map object
    - csv (panda DataFrame), the dataframe
    - stations ({str : (float, float)} dict), the stations data
    - max_data_age (float)

    draw the route polylines on the map\\
    doesn't return anything
    """
    print("Draw lines :")
    names = list(stations.keys())
    l = len(names)
    for i in trange(l - 1):
        k1 = names[i]
        for j in range(i + 1, l):
            k2 = names[j]
            if k2 == k1:
                continue
            delay = get_route_mean_delay(csv, (k1, k2), max_data_age)
            if delay < 0:
                continue
            c = get_color(delay)
            popup = f"{k1} ↔ {k2} : {min_to_time(delay)}"
            flm.PolyLine(
                [list(stations[k1]), list(stations[k2])],
                color=c,
                weight=LINE_WEIGHT,
                tooltip=popup,
            ).add_to(map)
    print()


def draw_map(max_data_age:float, stations:bool=True, routes:bool=False) -> flm.Map :
    """
    arguments :
    - max_data_age (float)
    - stations (bool) (True by default), the boolean indicating if the stations must be drown
    - routes (bool) (False by default), the boolean indicating if the routes must be drown

    create and return the map
    """
    if stations or routes :
        csv = load_pkl_file("cleaned_dataset.pkl")
        if csv is None :
            return None
        data = get_stations_data()
        if data is None or csv is None:
            return None
    map = init_map()
    if stations :
        draw_stations(map, csv, data, max_data_age)
    if routes :
        draw_routes(map, csv, data, max_data_age)
    return map


def create_mean_map(max_data_age:float=DEFAULT_MAX_DATA_AGE) -> str :
    """
    argument :
    - max_data_age (float) (`DEFAULT_MAX_DATA_AGE` by default)

    creates and saves the map into the `FILENAME` file and return its html code
    """
    map = draw_map(max_data_age, stations=True, routes=True)
    if map is None:
        return None
    print("Finished !")
    map.save(FILENAME)
    file = open(FILENAME, "r")
    if file is None:
        return None
    html = file.read()
    file.close()
    return html


if __name__ == "__main__":
    html = create_mean_map()
    if html is None :
        exit(EPITECH_FAILURE)
    exit(EPITECH_SUCCESS)
