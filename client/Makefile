# output executable name
EXEC = pray_client
# source files
CXX = g++
CXXFLAGS = -Wall -W -O3 -march=native -Wunused `sdl-config --cflags` -I./inc -I../common/inc
LDFLAGS = -lm -lrt `sdl-config --libs`
SRCS = $(wildcard src/*.cpp)
INCS = $(wildcard inc/*.h)
OBJS = $(SRCS:.cpp=.o)
COMMONSRCS = $(wildcard ../common/src/*.cpp)
COMMONOBJS = $(COMMONSRCS:.cpp=.o)

all: $(EXEC)

$(EXEC) : $(OBJS)
	cd ../common; make
	$(CXX) -o $@ $^ $(COMMONOBJS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	cd ../common; make clean
	rm -rf $(OBJS)
