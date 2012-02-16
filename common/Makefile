# makefile for common purposes
# source files
CXX = g++
#CXX = icpc
CXXFLAGS = -Wall -W -O3 -march=native -I./inc `sdl-config --cflags` -std=c++0x
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all : $(OBJS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) 

clean :
	rm -rf $(OBJS)
