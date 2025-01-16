#!/bin/bash

read -p "Enter the no. : " num
if [[ $num -lt 0 ]]
then
	echo "Please enter a positive integer"
else
	fact=1
	for (( i=2;i<=num;i++ ))
	do
		fact=$(( $fact*$i ))
	done
fi
echo "The factorial is $fact"
