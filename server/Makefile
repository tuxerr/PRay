# output executable name
EXEC = pray_server
# source files
CXX = g++
CXXFLAGS = -Wall -W -O2 -g -Wunused -I./inc
LDFLAGS = -lm -lrt 
SRCS = $(wildcard src/*.cpp)
INCS = $(wildcard inc/*.h)
OBJS = $(SRCS:.cpp=.o)
COMMONOBJS = $(wildcard ../common/*.o)

all: $(EXEC)

$(EXEC) : $(OBJS)
	cd ../common; make
	$(CXX) -o $@ $^ $(COMMONOBJS) $(LDFLAGS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	cd ../common; make clean
	rm -rf $(OBJS)
