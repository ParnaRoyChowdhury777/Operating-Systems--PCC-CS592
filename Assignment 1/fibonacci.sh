#!/bin/bash

read -p "Enter the number of terms: " n
if [[ $n -le 0 ]]; then
	echo "Invalid input, enter a positive integer "
else
	a=0
	b=1
	echo "Fibonacci series upto $n terms "
	echo "$a"
	for ((i=2; i<=$n; i++)); do
		echo "$b"
		temp=$((a+b))
		a=$b
		b=$temp
	done
fi
