#!/bin/bash

sum=0
for i in $*
do
	if [[ $i -lt 1 ]]; then
		echo "Natural Numbers are only allowed"
		exit 1
	fi
	sum=`expr $sum + $i`
done
echo "Sum is: $sum"
