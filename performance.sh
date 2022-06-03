#!/bin/bash 

file="btest";

if [ -f "$file" ] ; then
    rm "$file"
fi

# Run with Valgrind
\g++ -Wall -Wextra -Og -g -std=c++17 -pedantic-errors -pthread btest.cpp -o btest

valgrind ./btest