#!/usr/bin/awk -f

BEGIN {FS="~"; h1=0; h2=0; h3=0}

NR==1 {sub1=$3; sub2=$4; sub3=$5}

NR>1 {if($3>h1) {h1=$3; name1=$1}; if($4>h2) {h2=$4; name2=$1}; if($5>h3) {h3=$5; name3=$1}}

END {printf("Top Scorers\n\t%s -> %s(%d)",sub1,name1,h1)}
