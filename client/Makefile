# output executable name
EXEC = pray_client
# source files
CXX = g++
CXXFLAGS = `sdl-config --cflags` -Wall -W -O2 -g -Wunused -I./inc -I../common/inc
LDFLAGS = -lm -lrt `sdl-config --libs`
SRCS = $(wildcard src/*.cpp)
INCS = $(wildcard inc/*.h)
OBJS = $(SRCS:.cpp=.o)
COMMONOBJS = $(wildcard ../common/src/*.o)

all: $(EXEC)

$(EXEC) : $(OBJS) 
	cd ../common; make
	$(CXX) -o $@ $^ $(COMMONOBJS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	cd ../common; make clean
	rm -rf $(OBJS)
