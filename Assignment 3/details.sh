#!/bin/bash

while [ 1 ]
	echo "Menu:"
	echo "1. enter personal details:"
	echo "2. display personal details:"
	echo "3. exit the program"
	echo ""
do
	read -p "Enter your choice: " choice
	case $choice in
	1)
		read -p "Enter your name, roll, dept-sec, dob separated by spaces " name roll dept dob
		read -sp "Enter your password " password
		details="$name|$roll|$dept|$dob|$password"
		echo "$details" >> personal.dat
		echo "Your details have been updated."
		;;
	2)
		read -sp "Enter your passowrd:" password
		echo
		details=$(grep "$password" personal.dat)
		if [ -z "$details" ]; then
			echo "Password doesnot match, invalid, try again."
		else
			echo "Valid password"
			name=$(echo "$details" | cut -d"|" -f1)
			roll=$(echo "$details" | cut -d"|" -f2)
			dept=$(echo "$details" | cut -d"|" -f3)
			dob=$(echo "$details" | cut -d"|" -f4)
			password=$(echo "$details" | cut -d"|" -f5)
			echo -e "Name: $name \nRoll: $roll \nDepartment: $dept\nDOB: $dob"
		fi
		;;
	3)
		echo "Exit the program"
		exit
		;;
	*)
		echo "INvalid choice"
		;;
	esac
done


