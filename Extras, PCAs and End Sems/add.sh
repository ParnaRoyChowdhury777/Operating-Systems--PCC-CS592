#!/bin/bash

read -p "Enter the 1st no. " n1
if [[ -z "$n1" ]]; then
	echo "blank"
	exit 1
fi
read -p "Enter the second no. " n2

if [[ $n1 =~ ^-?[0-9]+(\.[0-9]+)?$ && $n2 =~  ^-?[0-9]+(\.[0-9]+)? ]]
then
	sum=$(echo "$n1+$n2" | bc -l)
	echo $sum
else
	echo "Invalid input"
fi
