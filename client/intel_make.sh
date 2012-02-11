#!/bin/bash
icpc -o pray_client_intel -O3 -march=native `sdl-config --cflags` -I./inc -I../common/inc ./src/*.cpp ../common/src/*.cpp -lm -lrt `sdl-config --libs` -lpthread -ltinyxml
