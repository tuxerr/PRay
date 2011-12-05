#!/bin/bash
mkdir -p ../bin
g++ -o ../bin/server-ui main.cpp -lncurses
../bin/server-ui
