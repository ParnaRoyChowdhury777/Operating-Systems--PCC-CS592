#!/usr/bin/awk -f

BEGIN {FS="~"; highest=0}

NR>1 {total=$3+$4+$5; if(total>highest) {highest=total; rec=$0}}

END {print rec" Highest marks= "highest}
