#!/bin/bash

num=$1
hex=`echo "obase=16;ibase=10;$num" | bc -l`
echo $hex
