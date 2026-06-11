#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all function to render the weclome page of the dashboard
##

import streamlit as st
import pandas as pd
from datetime import date
from dashboard_src.dashboard_global import EPITECH_SUCCESS, EPITECH_FAILURE


def show_data_stats(dataset: pd.DataFrame) -> int:
    st.header("Data Statistics")
    st.write(
        "The **average delay** across every path is :",
        round(dataset["Average delay of all trains at arrival"].mean(), 2),
        " minutes",
    )
    st.write(
        "The **number of trips** across all tracks is :",
        int(
            dataset["Number of scheduled trains"].sum()
            - dataset["Number of cancelled trains"].sum()
        ),
    )
    delay_rate = (
        (
            dataset["Number of cancelled trains"].sum()
            + dataset["Number of trains delayed at arrival"].sum()
        )
        / dataset["Number of scheduled trains"].sum()
        * 100
    )
    st.write(
        "The **punctuality rate** across all tracks is :",
        round((delay_rate - 100) * -1, 2),
        " %",
    )
    st.write("The **delay rate** across all tracks is :", round(delay_rate, 2), " %")
    return EPITECH_SUCCESS


def show_data_integrity(cleaned: pd.DataFrame, dataset: pd.DataFrame) -> None:
    st.header("Data Integrity")

    missing_percent = (cleaned.isnull().mean() * 100).sort_values(ascending=False)
    st.subheader("Missing Data Overview")
    st.write(
        "This corresponds to the percentage of NULL values for each column of the dataset:"
    )
    st.dataframe(
        missing_percent.reset_index().rename(
            columns={"index": "Column", 0: "Missing %"}
        )
    )
    st.subheader("Completeness of Data")
    # Not using len because len is the size, not the number of values and .shape gives (num_of_val, num_rows)
    st.write(
        "This corresponds to the percentage of NULL values compared to the total number of values: ",
        round(
            (1 - (cleaned.isnull().sum().sum() / (cleaned.shape[0] * cleaned.shape[1])))
            * 100,
            1,
        ),
        " %",
    )
    st.subheader("Number of duplicated rows")
    st.write(
        "This corresponds to the number of duplicated rows: ",
        cleaned.duplicated().sum(),
    )
    st.subheader("Number of entry per departure station")
    st.write(
        "This chart corresponds to the number of entry per departure station, to know which station will yield more reliable results:"
    )
    st.bar_chart(
        (cleaned["Departure station"].value_counts().sort_values(ascending=False))
    )


def create_filter_station(
    label: str, col_name: str, filtered_clean: pd.DataFrame
) -> pd.DataFrame:
    select = st.multiselect(
        label=label,
        options=filtered_clean[col_name].unique(),
    )
    if select != []:
        filtered_clean = filtered_clean[filtered_clean[col_name].isin(select)]
    return filtered_clean


def show_data_and_filters(
    cleaned: pd.DataFrame, dataset: pd.DataFrame, load_dataset: int, load_cleaned: int
) -> None:
    if load_dataset == EPITECH_SUCCESS:
        st.dataframe(dataset)
    else:
        st.write("""
        Could not load the csv file.
        """)
    st.write("""
        Which we cleaned for it to look like this to allow us to keep only the useful data for training the model.
    """)
    filtered_clean = cleaned
    with st.popover("Filters"):
        filtered_clean = create_filter_station("Departure Station",
            "Departure station", filtered_clean)
        filtered_clean = create_filter_station("Arrival Station",
            "Arrival station", filtered_clean)
        start_time = st.slider(
            "time range",
            value=(date(2017, 12, 31), date(2025, 12, 2)),
            format="YYYY-MM",
        )
        if start_time != []:
            start = str(start_time[0])
            end = str(start_time[1])
            filtered_clean = filtered_clean.query("`Date` >= @start & `Date` <= @end")
    if load_cleaned == EPITECH_SUCCESS:
        st.dataframe(filtered_clean)
    else:
        st.write("""
        Could not load the csv file.
        """)


def welcome_page() -> int:
    load_dataset = EPITECH_SUCCESS
    load_cleaned = EPITECH_SUCCESS
    try:
        dataset = pd.read_csv("cleaned_dataset.csv")
        if dataset is None :
            load_dataset = EPITECH_FAILURE
    except:
        load_dataset = EPITECH_FAILURE
    try:
        cleaned = pd.read_csv("filtered_dataset.csv")
        if cleaned is None :
            load_cleaned = EPITECH_FAILURE
    except:
        load_cleaned = EPITECH_FAILURE
    st.write("""
    # Tardis Dashboard
    Welcome to the dashboard for our tardis project!
    """)
    st.markdown("""
        This is a dashboard built for the tardis epitech project.

        **👈 Select a page from the dropdown on the left** to access different features of our Dashboard.
        Stay on this page if you want more details on the project.

        For this project, we have a made an AI model that predicts how late trains will be using this data from the sncf:
    """)
    show_data_and_filters(cleaned, dataset, load_dataset, load_cleaned)
    st.markdown("""
        ### Please note that our data is only from 2018 to 2025 so this is what we based our training on, all our observations are based on this time period.
        You will find more detailed statistics on the data hereunder""")
    if load_dataset == EPITECH_SUCCESS:
        show_data_stats(dataset)
        show_data_integrity(dataset, dataset)
    return EPITECH_SUCCESS
