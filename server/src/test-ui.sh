#!/bin/bash
mkdir -p ../bin
echo "Compilation..."
g++ -o ../bin/server-ui main.cpp -Wall -lncurses
echo "ENTER to continue ..."
read
../bin/server-ui
