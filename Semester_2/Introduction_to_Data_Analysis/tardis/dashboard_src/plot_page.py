#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all function to render the plot page of the dashboard
##

import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import base64
from os import remove
from dashboard_src.dashboard_global import EPITECH_SUCCESS, EPITECH_FAILURE


PLOT_FILENAME = "plot_save.png"
NAME_COMMENT_N_IMAGE = [
    [
        "Correlation",
        "Visual representation of relationships between delay factors",
        "./to_show/Correlation.png",
    ],
    [
        "Average Yearly Delay",
        "Here we can see that Delays were getting better leading up to covid, during which it was at it's lowest, since then it has started to rise, leading us to believe that only two minutes of about seven on average are due to large masses of people.",
        "./to_show/Average_yearly_delay.png",
    ],
    [
        "Top 10 Worst Departure Stations",
        "Here are the top 10 worst departure stations, we can see that Montpellier is absolutely awful",
        "./to_show/Top_10_worst_depature_stations.png",
    ],
    [
        "Top 10 Worst Arrival Stations",
        "Here are the top 10 worst arrival stations",
        "./to_show/Top_10_worst_arrival_stations.png",
    ],
]


def render_avg_delay_station(csv: pd.DataFrame) -> None:
    cell1, cell2 = st.columns([2, 4], border=True, gap="small")
    with cell1:
        st.subheader("Average arrival delay for chosen stations")
        options = st.multiselect(
            label="Choose the stations to analyse",
            options=csv["Departure station"].unique(),
        )
    with cell2:
        list = csv[csv["Departure station"].isin(options)]
        fig = plt.subplots()[0]
        sns.histplot(list["Average delay of all trains at arrival"], bins=40)
        plt.title("Average delay lengths for chosen stations")
        plt.xlabel("Average arrival delay (minutes)")
        plt.ylabel("Number of records")
        if len(list) > 0:
            st.pyplot(fig)
            plt.savefig(PLOT_FILENAME)
            file = open(PLOT_FILENAME, "rb")
            if not(file is None) :
                png = base64.b64encode(file.read())
                file.close()
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
                    href="data:application/octet-stream;base64,{png.decode()}"
                    download="{PLOT_FILENAME}">
                    Download Chart</a>"""
                st.markdown(html, unsafe_allow_html=True)
            remove(PLOT_FILENAME)
        else:
            st.write("Please input at least one station")
        plt.close()


def render_cell_pair(title: str, msg: str, img: str) -> None:
    cell1, cell2 = st.columns([2, 4], border=True, gap="small")

    with cell1:
        st.subheader(title)
        st.write(msg)

    with cell2:
        st.image(img, width="stretch")


def plot_page() -> int:
    load_csv = EPITECH_SUCCESS
    try:
        csv = pd.read_csv("filtered_dataset.csv")
    except:
        load_csv = EPITECH_FAILURE
    if load_csv != EPITECH_FAILURE:
        render_avg_delay_station(csv)
    for value in NAME_COMMENT_N_IMAGE:
        render_cell_pair(value[0], value[1], value[2])
    return EPITECH_SUCCESS
