# output executable name
EXEC = pray_server
# source files
CXX = g++
CXXFLAGS = -g -Wall -W -O3 -march=native -Wunused -I./inc `sdl-config --cflags` -I../common/inc -std=c++0x 
LDFLAGS = -lm -lrt -lcurses -lpthread `sdl-config --libs`
SRCS = $(wildcard src/*.cpp)
INCS = $(wildcard inc/*.h)
OBJS = $(SRCS:.cpp=.o)
COMMONSRCS = $(wildcard ../common/src/*.cpp)
COMMONOBJS = $(COMMONSRCS:.cpp=.o)

all: $(EXEC)
	cd ../common; make

$(EXEC) : $(OBJS)
	$(CXX) -o $@ $^ $(COMMONOBJS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	cd ../common; make clean
	rm -rf $(OBJS)
