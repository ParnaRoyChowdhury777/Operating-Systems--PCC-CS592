#!/bin/bash

read -p "Enter a year of your choice: " year
if [ $year -lt 1 ]; then
	echo "Year must be a positive integer"
else
	if { [ $((year % 4)) -eq 0 ] && [ $((year % 100)) -ne 0 ]; } || [ $((year % 400)) -eq 0 ]; then
		echo "$year is a leap year."
	else
		echo "$year is not a leap year."
	fi
fi

