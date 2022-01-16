#!/bin/bash

SHEET=$(ls | grep "^[0-9][0-9][0-9][0-9]$")

if [ -n "${SHEET}" ] && git status | grep "modified:" | grep "${SHEET}" ; then

	git add ${SHEET}
	git commit -m "$(date +%d-%m-%Y_%H:%M:%S)"
	git push -u origin main

fi

