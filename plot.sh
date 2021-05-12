#!/bin/bash
if [ -z "$1" ] ; then
	echo "usage: plot.sh <datafile>"
	exit -1;
fi;
gnuplot -p << EOF
plot "$1" using 3:1 with lines title "current temperature", \
	"$1" using 3:2 with lines title "goal temperature"
EOF
