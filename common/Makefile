# makefile for common purposes
# source files
CXX = g++
CXXFLAGS = -Wall -W -O2 -g -Wunused -I./inc `sdl-config --cflags` -std=c++0x 
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all : $(OBJS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) 

clean :
	rm -rf $(OBJS)
