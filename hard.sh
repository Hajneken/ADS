#!/bin/bash 

file="btest";

if [ -f "$file" ] ; then
    rm "$file"
fi

# PH1
# \g++ -Wall -Wextra -Og -g -std=c++17 -pedantic-errors -pthread -DPH1 btest.cpp -o btest;
# PH2
\g++ -Wall -Wextra -Og -g -std=c++17 -pedantic-errors -pthread -DPH2 -DSIZE=1 btest.cpp -o btest

./btest 2> log.txt;

code log.txt;