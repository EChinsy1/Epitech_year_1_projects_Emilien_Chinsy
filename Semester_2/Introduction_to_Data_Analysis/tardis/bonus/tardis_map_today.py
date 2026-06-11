#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all functions to create the today's predictions map
##

import pandas as pd
import folium as flm
from datetime import date, time
from tqdm import trange
from os import getcwd, chdir
from sys import path


def set_cwd() -> None :
    """
    no arguments

    set the current working directory to the repository root
    """
    cwd = getcwd()
    path.append(cwd + "/..")
    if cwd.endswith("/bonus") :
        chdir("../")


set_cwd()

from tardis_tools import get_field_value
from tardis_model import question_the_model, TRAIN_SERVICE, SEC_IN_MIN


EPITECH_SUCCESS = 0
EPITECH_FAILURE = 84

FILENAME = "maps/map_today.html"

GET_NBR_ROWS = lambda df: df.shape[0]
MONTH_IN_YEAR = 12
MIN_IN_H = 60
SEC_IN_MIN = 60
SEC_IN_H = MIN_IN_H * SEC_IN_MIN
H_IN_DAY = 24

FOREIGN_STATIONS = (
    "FRANCFORT",
    "STUTTGART",
    "ZURICH",
    "LAUSANNE",
    "ITALIE",
    "BARCELONA",
    "MADRID",
)

MAP_CENTER = (46.92475, 2.51240)
MAP_ZOOM = 6.2

COLOR_STEP = 5
STATION_ICON = "train"
LINE_WEIGHT = 2.5


def init_map() -> flm.Map :
    """
    no argument

    return the folium Map object centered on `MAP_CENTER` and zoom at `MAP_ZOOM`
    """
    map = flm.Map(location=MAP_CENTER, zoom_start=MAP_ZOOM, tiles="OpenStreetMap")
    tl = flm.TileLayer(tiles="https://tile.openstreetmap.org/{z}/{x}/{y}.png",
        attr="&copy; <a href='https://www.openstreetmap.org/copyright'>OpenStreetMap</a> contributors")
    tl.options["Referrer-Policy"] = "no-referrer-when-downgrade"
    tl.add_to(map)
    return map


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


def get_stations_data() -> dict[str:tuple[float, float]] :
    """
    no arguments

    return the list of stations names (list of str)\\
    return None in case of error
    """
    try :
        csv = pd.read_csv("bonus/stations_coords.csv", sep=",")
    except :
        return None
    for c in ("Latitude", "Longitude") :
        csv[c] = pd.to_numeric(csv[c], errors="coerce")
    data = {}
    for i in range(GET_NBR_ROWS(csv)):
        name = get_field_value(csv.iloc[[i]]["Name"], str)
        lat = get_field_value(csv.iloc[[i]]["Latitude"], float)
        long = get_field_value(csv.iloc[[i]]["Longitude"], float)
        if (type(name) == str and type(lat) in (int, float)
            and type(long) in (int, float)) :
            data[name.upper()] = (lat, long)
    return data


def get_color(delay:float) -> str:
    """
    color guide :
    - green = average delay <= 5 minutes
    - blue = 5 minutes < average delay <= 10 minutes
    - yellow = 10 minutes < average delay <= 15 minutes
    - orange = 15 minutes < average delay <= 20 minutes
    - red = 20 minutes < average delay <= 30 minutes
    - purple = average delay > 30 minutes
    - gray = no data
    """
    if delay < 0:
        return "gray"
    colors = ("green", "blue", "yellow", "orange", "red", "red", "purple")
    i = 0
    while delay >= COLOR_STEP and i < (len(colors) - 1):
        delay -= COLOR_STEP
        i += 1
    return colors[i]


def min_to_time(nbr:float) -> str :
    """
    argument :
    - nbr (float), the time value in minutes

    return the corresponding *[`J`j] `hh`:`mm`:`ss`* string
    """
    if nbr < 0 :
        return "-" + min_to_time(-nbr)
    n_sec = int(round(nbr * SEC_IN_MIN, 0))
    d = n_sec // (SEC_IN_H * H_IN_DAY)
    n_sec = n_sec % (SEC_IN_H * H_IN_DAY)
    h = n_sec // SEC_IN_H
    n_sec = n_sec % SEC_IN_H
    m = n_sec // SEC_IN_MIN
    sec = n_sec % SEC_IN_MIN
    text = f"{d}j" if d > 0 else ""
    return text + f"{h:02}:{m:02}:{sec:02}"


def time_obj_to_minutes(t:time) -> float :
    """
    argument :
    - t (time), the time obj

    return the time value in minutes (float)
    """
    return t.hour + t.minute + (t.second / SEC_IN_MIN)


def get_train_service(s1:str, s2:str) -> TRAIN_SERVICE :
    """
    arguments :
    - s1 (str), the first station
    - s2 (str), the second station

    return the TRAIN_SERVICE enum value corresponding to a train traveling between s1 and s2 : (if the at least one of these stations are out of France, return `TRAIN_SERVICE.International`, else return `TRAIN_SERVICE.National`)
    """
    if s1.upper() in FOREIGN_STATIONS or s2.upper() in FOREIGN_STATIONS :
        return TRAIN_SERVICE.International
    return TRAIN_SERVICE.National


def get_station_weight(name:str, stations:dict[str:tuple[float, float]]) -> float :
    """
    arguments :
    - name (str), the station name
    - stations ({name (str) : (pos_x (float), pos_y (float))} dict), the dict containing stations coordinates

    return the average delay predicted by the model of all trains going to this station (float)
    """
    today = date.today()
    s, n = 0, 0
    for dep in stations :
        tmp = question_the_model(dep, name, today, get_train_service(dep, name))
        if not (tmp is None) :
            s += time_obj_to_minutes(tmp)
            n += 1
    if n <= 0 :
        return -1
    return s / n


def draw_stations(map:flm.Map, stations:dict[str:tuple[float, float]]) -> None :
    """
    arguments :
    - map (folium Map), the map object
    - stations ({str : (float, float)} dict), the stations data

    draw the stations markers on the map\\
    doesn't return anything
    """
    print("Draw stations")
    names = list(stations.keys())
    for i in trange(0, len(names), 1) :
        k = names[i]
        delay = get_station_weight(k, stations)
        c = get_color(delay)
        if c == "yellow" :
            c = "beige"
        if delay < 0 :
            popup = f"{k} : NaN"
        else :
            popup = f"{k} : {min_to_time(delay)}"
        flm.Marker(
            location=list(stations[k]),
            icon=flm.Icon(color=c, prefix="fa", icon=STATION_ICON),
            popup=flm.Popup(popup, max_width=None),
        ).add_to(map)


def draw_routes(map:flm.Map, stations:dict[str:tuple[float, float]]) -> None :
    """
    arguments :
    - map (folium Map), the map object
    - stations ({str : (float, float)} dict), the stations data

    draw the route polylines on the map\\
    doesn't return anything
    """
    print("Draw routes :")
    names = list(stations.keys())
    l = len(names)
    for i in trange(l - 1) :
        k1 = names[i]
        for j in range(i + 1, l) :
            k2 = names[j]
            if k2 == k1:
                continue
            delay1 = question_the_model(k1, k2, date.today(), get_train_service(k1, k2))
            delay2 = question_the_model(k2, k1, date.today(), get_train_service(k1, k2))
            if delay1 is None or delay2 is None :
                delay = -1
            else :
                delay = (time_obj_to_minutes(delay1) + time_obj_to_minutes(delay2)) / 2
            if delay < 0 :
                continue
            c = get_color(delay)
            popup = f"{k1} ↔ {k2} : {min_to_time(delay)}"
            flm.PolyLine([list(stations[k1]), list(stations[k2])], color=c,
                weight=LINE_WEIGHT, tooltip=popup).add_to(map)
    print()


def draw_map(stations:bool=True, routes:bool=False) -> flm.Map :
    """
    arguments :
    - stations (bool) (True by default), the boolean indicating if the stations must be drown
    - routes (bool) (False by default), the boolean indicating if the routes must be drown

    create and return the map
    """
    if stations or routes :
        data = get_stations_data()
        if data is None:
            return None
    map = init_map()
    if stations :
        draw_stations(map, data)
    if routes :
        draw_routes(map, data)
    return map


def create_today_map() -> str :
    """
    no arguments

    creates and saves the map into the `FILENAME` file and return its html code
    """
    map = draw_map(stations=True, routes=True)
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


if __name__ == "__main__" :
    html = create_today_map()
    if html is None :
        exit(EPITECH_FAILURE)
    exit(EPITECH_SUCCESS)
