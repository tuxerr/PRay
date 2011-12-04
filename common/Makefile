# makefile for common purposes
# source files
CXX = g++
CXXFLAGS = -Wall -W -O2 -g -Wunused -I./inc
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all : $(OBJS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) 

clean :
	rm -rf $(OBJS)
