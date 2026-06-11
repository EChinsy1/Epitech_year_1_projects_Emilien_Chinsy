#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all functions to create the today's predictions map
##

import fpdf
from datetime import time, date
from sys import path
from os import getcwd, chdir
from math import sin, acos, cos, pi


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


A4_PAGE = (210, 297)
A5_PAGE = (A4_PAGE[1] / 2, A4_PAGE[0])
MARGIN = 10

OUTPUT_PATH = "to_show/delay_sheet.pdf"

FAVICON_PATH = "to_show/favicon_dark.png"
FAVICON_SIZE = 40

STATION_POINT_RADIUS = 5
STATION_POINT_STYLE = "F"
STATIONS_SPACING = 75
DEPARTURE_POINT_POS = (MARGIN + STATION_POINT_RADIUS,
    2 * MARGIN + FAVICON_SIZE + STATION_POINT_RADIUS)
ARRIVAL_POINT_POS = (DEPARTURE_POINT_POS[0],
    DEPARTURE_POINT_POS[1] + STATIONS_SPACING)
LINE_WIDTH = 5
STATION_NAME_PADDING = 2.5

GREEN = (0x2f, 0xb1, 0x70)
RED = (0xe6, 0x69, 0x5b)
BLUE = (0x67, 0x91, 0xe0)
BLACK = (0, 0, 0)

FONT_NAME = "Arial"
FONT_SIZE_STATIONS = 24
FONT_SIZE_DELAY = 20
FONT_SIZE_COPYRIGHT = 8
FONT_SIZE_DATE = FONT_SIZE_STATIONS

DATA_SPACE = 2 + (FONT_SIZE_DELAY / FONT_SIZE_STATIONS) * \
    STATION_POINT_RADIUS * 2

WEEK_DAYS = ("Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
    "Saturnday", "Sunday")
GET_SUFFIX = lambda d : "st" if d % 10 == 1 and d // 10 != 1 else \
    "nd" if d % 10 == 2 and d // 10 != 1 else \
    "rd" if d % 10 == 3 and d // 10 != 1 else "th"

DEG_TO_RAD = lambda a : (a * pi) / 180


def draw_line(pdf:fpdf.FPDF, p1:tuple[float, float], p2:tuple[float, float],
    width:float, color:tuple[int, int, int]=None) -> None :
    """
    arguments:
    - pdf (fpdf FPDF), the pdf object
    - p1 (tuple of 2 floats), the first point
    - p2 (tuple of 2 floats), the second point
    - width (float), the line width
    - color (tuple of 3 int) (None by default), the line color

    draw a line between the both points
    """
    if not(color is None) :
        pdf.set_draw_color(color[0], color[1], color[2])
    pdf.set_line_width(width)
    pdf.line(p1[0], p1[1], p2[0], p2[1])


def draw_circle(pdf:fpdf.FPDF, pos:tuple[float, float], size:float,
    fill:tuple[int, int, int]=None,
    border_color:tuple[int, int, int]=None) -> None :
    """
    arguments :
    - pdf (fpdf FPDF), the pdf object
    - pos (tuple of 2 floats), the (x, y) tuple
    - size (float), the circle diameter
    - fill (tuple of 3 int) (None by default), the background color
    - border_color (tuple of 3 int) (None by default), the border color

    draw the circle with the pos as coordinate of the center
    """
    style = ""
    if not(border_color is None) :
        style += "D"
        pdf.set_draw_color(border_color[0], border_color[1], border_color[2])
    if not(fill is None) :
        style += "F"
        pdf.set_fill_color(fill[0], fill[1], fill[2])
    pdf.ellipse(pos[0] - size / 2, pos[1] - size / 2, size, size, style)


def compute_distance(p1:tuple[float, float], p2:tuple[float, float]) -> float :
    a = DEG_TO_RAD(p1[0])
    b = DEG_TO_RAD(p2[0])
    dl = DEG_TO_RAD(abs(p1[1] - p2[1]))
    sin_a = sin(a)
    sin_b = sin(b)
    cos_a = cos(a)
    cos_b = cos(b)
    cos_dl = cos(dl)
    s_ab = acos(sin_a * sin_b + cos_a * cos_b * cos_dl)
    radius = 40000 / (2 * pi)
    return s_ab * radius


def generate_pdf_delay_sheet(departure:str, arrival:str, travel_date:date,
    service:str, stations_coords:dict[str:tuple[float, float]],
    delay:time) -> str :
    """
    arguments :
    - departure (str), the departure station
    - arrival (str), the arrival station
    - travel_date (date), the date of the prediction
    - service (str), the train service
    - stations_coords ({str : (float, float)} dict), the stations coords dict
    - delay (time), the predicted delay

    return the filepath to the created pdf file
    return None in case of error
    """
    try :
        pdf = fpdf.FPDF(format=A5_PAGE)
        dep_pos, arr_pos = stations_coords[departure], stations_coords[arrival]
    except :
        return None
    if pdf is None :
        return None
    pdf.add_page()
    pdf.image(FAVICON_PATH, MARGIN, MARGIN, FAVICON_SIZE, FAVICON_SIZE)
    draw_line(pdf, DEPARTURE_POINT_POS, ARRIVAL_POINT_POS, LINE_WIDTH, BLUE)
    draw_circle(pdf, DEPARTURE_POINT_POS, STATION_POINT_RADIUS * 2, fill=GREEN)
    draw_circle(pdf, ARRIVAL_POINT_POS, STATION_POINT_RADIUS * 2, fill=RED)
    pdf.set_fill_color(BLACK[0], BLACK[0], BLACK[0])
    pdf.set_draw_color(BLACK[0], BLACK[0], BLACK[0])
    pdf.set_font(FONT_NAME, size=FONT_SIZE_STATIONS)
    pdf.text(MARGIN * 2 + FAVICON_SIZE, MARGIN * 1.75, f"{ \
        WEEK_DAYS[travel_date.weekday()]} {travel_date.day}{ \
        GET_SUFFIX(travel_date.day)}, {travel_date.year}")
    pdf.text(MARGIN * 2 + FAVICON_SIZE, MARGIN * 1.75 + FONT_SIZE_DATE * 0.4,
        f"{service.capitalize()} train")
    pdf.text(DEPARTURE_POINT_POS[0] + STATION_POINT_RADIUS +
            STATION_NAME_PADDING,
        DEPARTURE_POINT_POS[1] + STATION_POINT_RADIUS * 0.5, departure)
    pdf.text(ARRIVAL_POINT_POS[0] + STATION_POINT_RADIUS + \
            STATION_NAME_PADDING,
        ARRIVAL_POINT_POS[1] + STATION_POINT_RADIUS * 0.5, arrival)
    pdf.set_font(FONT_NAME, size=FONT_SIZE_DELAY)
    data_pos = (((DEPARTURE_POINT_POS[0] + ARRIVAL_POINT_POS[0]) / 2) + \
            STATION_POINT_RADIUS + STATION_NAME_PADDING,
        (DEPARTURE_POINT_POS[1] + ARRIVAL_POINT_POS[1]) / 2)
    dist_pos = (data_pos[0], data_pos[1] - DATA_SPACE / 2)
    delay_pos = (data_pos[0], data_pos[1] + DATA_SPACE / 2)
    distance = compute_distance(dep_pos, arr_pos)
    pdf.text(dist_pos[0], dist_pos[1], f"Distance: {distance:.2f} km")
    pdf.text(delay_pos[0], delay_pos[1], f"Estimated Delay: {delay.hour:02}:{ \
        delay.minute:02}:{delay.second:02}")
    pdf.set_font(FONT_NAME, size=FONT_SIZE_COPYRIGHT)
    today = date.today()
    pdf.text(MARGIN, A5_PAGE[1] - MARGIN,
        f"© tardis alexis&emilien - made with tardis on {today.month:02}/{ \
            today.day:02}/{today.year:04}")
    if __name__ == "__main__" :
        pdf.output(OUTPUT_PATH)
    return pdf.output(dest="S").encode("latin-1")
    

if __name__ == "__main__" :
    filepath = generate_pdf_delay_sheet("PARIS MONTPARNASSE",
        "POITIERS", date(day=5, month=6, year=2026), "National",
            {"PARIS MONTPARNASSE" : (48.83888, 2.31753),
            "POITIERS" : (46.58266, 0.33299)}, time(0, 6, 32))
