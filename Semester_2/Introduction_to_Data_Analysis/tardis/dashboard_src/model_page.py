#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all function to render the model page of the dashboard
##

import streamlit as st
import pandas as pd
from datetime import date, time
from tardis_model import *
from dashboard_src.dashboard_global import EPITECH_SUCCESS, EPITECH_FAILURE
from os import getcwd, chdir
from sys import path
import webbrowser
import base64


def set_cwd() -> None :
    """
    no arguments

    set the current working directory to the repository root
    """
    cwd = getcwd()
    path.append(cwd + "/..")
    if cwd.endswith("/dashboard_src") :
        chdir("../")


set_cwd()

from bonus.tardis_delay_pdf import generate_pdf_delay_sheet
from bonus.tardis_map_today import get_stations_data

try :
    STATIONS_COORDS = get_stations_data()
except :
    STATIONS_COORDS = None
button_pressed = False
value, pdf = None, None


st.set_page_config(layout="wide", page_title="Tardis Dashboard")


def model_explainations() -> None:
    mae = compute_model_confidence()
    if mae is None:
        mae_str = "<NaN>"
    else:
        mae_str = f"{(mae.hour * MIN_IN_H + mae.minute):02}:{mae.second:02}"
    st.write(
        f"""The model results can not be exactly the truth. They are approximated to within `{mae_str}`."""
    )
    st.write("All asked values are important :")
    st.write(
        "- the `Departure Station` and `Arrival Station` are absolutely necessary because the delay on one route can not be compared with the delay on another one"
    )
    st.write("""- the `Date` are used to make a prediction from data of the same month and year
    - the results will not be equals during the dead season than during a peak holiday travel period
    - the trains delays vary from one year to the next so years too far away can not be compared""")


def get_service_enum_item(service_str: str) -> TRAIN_SERVICE:
    for e in TRAIN_SERVICE:
        if service_str == e.name:
            return e
    return None


def render_selection_cell(filtered_clean: pd.DataFrame) -> tuple[time, str] :
    st.subheader("Input your values")
    value, pdf = None, None
    departure = st.selectbox(
        label="Departure Station",
        options=filtered_clean["Departure station"].unique(),
    )
    filtered_clean = filtered_clean[filtered_clean["Departure station"] == departure]
    arrival = st.selectbox(
        label="Arrival Station",
        options=filtered_clean["Arrival station"].unique(),
    )
    filtered_clean = filtered_clean[filtered_clean["Arrival station"] == arrival]
    input_date = st.date_input("Date", date.today())
    service = st.selectbox(
        label="Service Type",
        options=[e.name for e in TRAIN_SERVICE],
    )
    if st.button(label="predict", help="predict", key=6):
        global button_pressed
        button_pressed = True
        value = question_the_model(
            departure, arrival, input_date, get_service_enum_item(service)
        )
        try :
            pdf = generate_pdf_delay_sheet(departure, arrival, input_date,
                service, STATIONS_COORDS, value)
        except :
            pdf = None
    return (value, pdf)


def render_model() -> int:
    global value, pdf
    global button_pressed
    load_cleaned = EPITECH_SUCCESS
    try:
        cleaned = pd.read_csv("filtered_dataset.csv")
    except:
        load_cleaned = EPITECH_FAILURE
    filtered_clean = cleaned
    st.write(
        "Here you can use our model to predict tardiness, simply imput the Departure station, Arrival Station, date and Service you want to use to depart"
    )
    cell1, cell2 = st.columns([2, 4], border=True, gap="small")
    if load_cleaned == EPITECH_FAILURE:
        st.write("Failed to load dataset")
    else:
        with cell1:
            tmp = render_selection_cell(filtered_clean)
            if not(tmp[0] is None) :
                value, pdf = tmp
        with cell2:
            if value is None and button_pressed :
                st.error("No prediction available for this route.")
                button_pressed = False
            elif button_pressed :
                st.write(value)
                if pdf is not None :
                    base64_pdf = base64.b64encode(pdf)
                    html = """<style type="text/css">
                        a.button:hover {
                            background-color: rgba(172, 177, 195, 0.15);
                        }

                        a.button {
                            cursor: pointer;
                            display: inline-block;
                            font-weight: 400;
                            padding: 0.25rem 0.75rem;
                            border-radius: 0.5rem;
                            margin: 0;
                            line-height: 1.6;
                            text-decoration: none;
                            font-size: 16px;
                            font-family: inherit;
                            color: inherit;
                            border: 1px solid rgba(250, 250, 250, 0.2);
                            appearance: button;
                        }
                    </style>\n""" + f"""<a class="button"
                        href="data:application/octet-stream;base64,{ \
                        base64_pdf.decode()}" download="delay_sheet.pdf">
                        Export</a>"""
                    st.markdown(html, unsafe_allow_html=True)
    model_explainations()


def model_unavailable() -> None:
    st.error("Sorry, the Tardis Model is currently unavailable !")


def model_page() -> int:
    st.header("Query Tardiness")
    if MODEL_AVAILABLE:
        return render_model()
    return model_unavailable()
