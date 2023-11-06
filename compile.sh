#!/bin/bash

# Check if .o files exist, if not, compile the corresponding .cpp files
# g++ -c sourceFile.cpp -o sourceFile.o
g++ -c huff.cpp -o main.o

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Link object files and create the executable
    g++ -o myprogram main.o
    if [ $? -eq 0 ]; then
        echo "COMPILATION SUCCESSFUL."
        echo "***********************"
        echo ""
        ./myprogram
    else
        echo "ERROR IN LINKING"
    fi
else
    echo "ERROR IN COMPILING"
fi