#!/bin/bash

choice=1
while [ $choice -eq 1 ]
do
	read -p "Enter the four details (separated by spaces) " name roll phone address
	details="$name|$roll|$phone|$address"
	echo "$details" >> Students.dat
	echo "Your details have been updated."
	read -p "Press 1 to continue 0 to exit: " choice
done
while [ 1 ] 
	echo "MENU"
	echo "1. Sort the records in reverse order"
	echo "2. REplace lower case letters with upper case letters"
	echo "3. Records with unique names"
	echo "4. Display 2nd and 3rd lines"
	echo ""
do
	read -p "Enter your choice: " ch
	case $ch in
	1)
		sort -t '|' -k 2 -r Students.dat >> sorted.dat
		echo "File after sorting:"
		cat sorted.dat
		;;
	2)
		tr [:lower:] [:upper:] < sorted.dat
		echo "File updated"
		;;
	3)
		list=`cat sorted.dat | sort -t'|' -k1 | cut -d'|' -f1 | uniq -c | tr -s " " | cut -d' ' -f3`
		for i in $list; do
			found=`cat sorted.dat | grep -w "^$i" | head -1`
			echo $found
		done
		;;
	4)
		cat Students.dat | head -n 3 | tail -n 2
		;;
	5)
		exit;;
	*) 
		echo "\n Invalid key "
		;;

esac	
done

