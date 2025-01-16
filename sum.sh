#!/bin/bash

read -p "Enter a number: " num
if [[ $num -lt 0 ]]; then
	echo "Ivalid input, please enter a positive number"
else
	sum=0
	while [ $num -gt 0 ]; do
		digit=$((num % 10))
		sum=$((sum + digit))
		num=$((num / 10))
	done
	echo "The sum of digits is : $sum"
fi
