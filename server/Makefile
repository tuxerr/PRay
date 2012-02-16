# output executable name
EXEC = pray_server
# source files
CXX = g++
CXXFLAGS = -g -Wall -W -O3 -march=native -Wunused -I./inc `sdl-config --cflags` -I../common/inc -std=c++0x 
LDFLAGS = -lm -lrt -lcurses -lpthread `sdl-config --libs` -ltinyxml
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
COMMONSRCS = $(wildcard ../common/src/*.cpp)
COMMONOBJS = $(COMMONSRCS:.cpp=.o)

all: $(EXEC)

$(EXEC) : common $(OBJS)
	$(CXX) -o $@ $(OBJS) $(COMMONOBJS) $(LDFLAGS)

common : 
	cd ../common; make

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	cd ../common; make clean
	rm -rf $(OBJS)
