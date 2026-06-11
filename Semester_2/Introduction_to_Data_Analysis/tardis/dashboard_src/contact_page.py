#!/usr/bin/env python3
##
## EPITECH PROJECT, 2026
## G2 - Introduction to Data Analysis - Tardis - Alexis & Emilien
## File description:
## this file contains all function to render the contact page of the dashboard
##

import streamlit as st
import webbrowser
from dashboard_src.dashboard_global import EPITECH_SUCCESS


model_has_been_load = False


def render_contact(container, name:str, img:str, linkedin:str,
    github:str, contact_id:int=0) -> None :
    global nbr_contacts

    with container :
        st.subheader(name)
        st.image(
            img,
            width="stretch",
        )
        k1, k2 = (contact_id * 2) + 1, (contact_id * 2) + 2
        if st.button(label="Linkedin", help="Link to a linkedin page", key=k1):
            webbrowser.open(linkedin)
        if st.button(label="Github", help="Link to a linkedin page", key=k2):
            webbrowser.open(github)
    contact_id += 1



def contact_page() -> int:
    st.header("""Contact""")
    col1, col2 = st.columns([3, 3], border=True, gap="small")

    render_contact(
        col1,
        "Emilien Chinsy",
        "./to_show/emilien_photo.png",
        "https://www.linkedin.com/in/emilien-chinsy-5a794632b/",
        "https://github.com/EChinsy1",
        contact_id=0
    )
    render_contact(
        col2,
        "Alexis Guibert",
        "./to_show/photo_alexis.jpg",
        "https://www.linkedin.com/in/alexis-guibert-it/",
        "https://github.com/UntilVrac",
        contact_id=1
    )
    return EPITECH_SUCCESS
