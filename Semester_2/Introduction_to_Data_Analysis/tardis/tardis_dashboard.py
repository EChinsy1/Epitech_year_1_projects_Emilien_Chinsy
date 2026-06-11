#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## main file of the dashboard
##

import streamlit as st
from dashboard_src.dashboard_global import EPITECH_SUCCESS
from dashboard_src.welcome_page import welcome_page
from dashboard_src.plot_page import plot_page
from dashboard_src.model_page import model_page
from dashboard_src.maps_page import maps_page
from dashboard_src.contact_page import contact_page


model_has_been_load = False


st.set_page_config(
    layout="wide", page_title="Tardis Dashboard", page_icon="./to_show/favicon_dark.svg"
)


def main_dashboard() -> int:
    demo_name = st.sidebar.selectbox("Choose a page", page_names_to_funcs.keys())
    page_names_to_funcs[demo_name]()
    return EPITECH_SUCCESS


page_names_to_funcs = {
    "Welcome": welcome_page,
    "Observations": plot_page,
    "Model": model_page,
    "Maps": maps_page,
    "Contact": contact_page,
}

if __name__ == "__main__":
    main_dashboard()
