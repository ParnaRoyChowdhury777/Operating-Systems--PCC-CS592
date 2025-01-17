#Selection Sort

#!/bin/bash

read -p "Enter the length: " len
if [ $len -lt 1 ]; then
	echo "Length should atleast be 1"
else
	declare -A arr
	for (( i=0; i<len; i++ ))
	do
		read arr[$i]
	done

	echo -n "Unsorted array: "
	for (( i=0; i<len; i++ ))
	do
		echo -n "${arr[$i]} "
	done
	echo ''

	for (( i=0; i<len-1; i++ ))
	do
		min=$i 
		for (( j=i+1; j<len; j++ ))
		do
			if [[ ${arr[$j]} -lt ${arr[$min]} ]]
			then
				min=$j
			fi
		done
		t=${arr[$i]}
		arr[$i]=${arr[$min]}
		arr[$min]=$t
	done

	echo -n "Sorted array: "
	for (( i=0; i<len; i++ ))
	do
		echo -n "${arr[$i]} "
	done
	echo ''
fi
