#!/bin/bash 

file="simpletest";

if [ -f "$file" ] ; then
    rm "$file"
fi

# Phase 1: Uncomment 1 of the following
# g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=std::string simpletest.cpp -o simpletest
# g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=std::string -DSIZE=13 simpletest.cpp -o simpletest
# g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=Person simpletest.cpp -o simpletest
# g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=Person -DSIZE=13 simpletest.cpp -o simpletest
# g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=unsigned simpletest.cpp -o simpletest
# g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH1 -DETYPE=unsigned -DSIZE=13 simpletest.cpp -o simpletest

# PHASE 2: Uncomment 1 of the following
#  g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=std::string simpletest.cpp -o simpletest
#  g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=std::string -DSIZE=13 simpletest.cpp -o simpletest
 g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=Person simpletest.cpp -o simpletest
 #g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=Person -DSIZE=13 simpletest.cpp -o simpletest
 #g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=unsigned simpletest.cpp -o simpletest
 #g++ -Wall -Wextra -O3 -std=c++17 -pedantic-errors -DPH2 -DETYPE=unsigned -DSIZE=13 simpletest.cpp -o simpletest

./simpletest 