#!/usr/bin/awk -f

BEGIN {FS="~"; sum=0; printf("Enter the sub no."); getline n < "-"}

NR>1 {sum=sum+$(n+2)}

END {avg=sum/(NR-1); print "Average: "avg}
