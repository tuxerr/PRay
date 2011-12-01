# output executable name
EXEC = pray_client
# source files
CXX = g++
CXXFLAGS = `sdl-config --cflags` -Wall -W -O2 -g -Wunused -I./inc
LDFLAGS = -lm -lrt `sdl-config --libs`
SRCS = $(wildcard src/*.cpp)
INCS = $(wildcard inc/*.h)
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC) : $(OBJS)
$(CXX) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
rm -rf $(OBJS)
