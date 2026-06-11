#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all function to render the maps page of the dashboard
##

import streamlit as st
import streamlit.components.v1 as components
from datetime import date
from tardis_model import *
from bonus.tardis_map_mean import create_mean_map, DEFAULT_MAX_DATA_AGE
from bonus.tardis_map_today import create_today_map


MAP_HEIGHT = 600
DATA_AGE_MAX_VALUE = (date.today().year * MONTH_IN_YEAR + date.today().month) \
    - (2017 * MONTH_IN_YEAR + 12)
SLIDER_WIDTH = 200
MAPS_LOADED = False


def render_map_from_file(filepath: str) -> None:
    html_file = open(filepath, "r", encoding="utf-8")
    source_code = html_file.read()
    html_file.close()
    components.html(source_code, height=MAP_HEIGHT)


def render_map(html:str) -> None :
    if type(html) != str :
        st.error("Sorry, this map is currently unavailable.")
    else :
        components.html(html, height=MAP_HEIGHT)


def color_label(color: str) -> None:
    return f'<span style="color: {color};">{color}</span>'


def maps_page() -> int:
    global MAPS_LOADED
    if not MAPS_LOADED :
        create_today_map()
        MAPS_LOADED = True
    st.header("""
             Statistics in a few Maps
             """)
    st.markdown(
        """#### Average trains delay for the last *n* months

The following map presents the average trains delay for the last *n* months (you can set the *n* value below). You can click on the stations to see their name and the average delay of all trains at departure from them. You can see the average trains delay on a route by passing the mouse on the line.\\
*(See the colors guide below)*
        """
    )
    mda = DEFAULT_MAX_DATA_AGE
    max_data_age = st.slider("Maximal data age (in months)", min_value=0,
        max_value=DATA_AGE_MAX_VALUE, value=(DEFAULT_MAX_DATA_AGE,),
        width=SLIDER_WIDTH)
    if max_data_age != []:
        mda = max_data_age[0]
    render_map(create_mean_map(max_data_age=mda))
    st.markdown(
        f"""#### Trains delay predicted for today

The following map presents the trains delay predictions for today ({date.today()}). You can click on the stations to see their name and the average delay predicted for all trains arriving to them. You can see the predicted trains delay on a route (the average of the predictions for the outbound and return journeys) by passing the mouse on the line.\\
*(See the colors guide below)*
        """
    )
    render_map_from_file("./maps/map_today.html")
    st.markdown(
        f"""#### Colors Guide

- {color_label("green")} : average delay <= 5 minutes
- {color_label("blue")} : 5 minutes < average delay <= 10 minutes
- {color_label("yellow")} (or {color_label("beige")}) : 10 minutes < average delay <= 15 minutes
- {color_label("orange")} : 15 minutes < average delay <= 20 minutes
- {color_label("red")} : 20 minutes < average delay <= 30 minutes
- {color_label("purple")} : average delay > 30 minutes
- {color_label("gray")} : no data
        """,
        unsafe_allow_html=True,
    )
    return EPITECH_SUCCESS
