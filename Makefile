CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -pedantic -g  -std=gnu11
CXXFLAGS = -Wall -Wextra -pedantic -g  -std=gnu++11
BINS =  cbuild  #cppbuild

all: $(BINS)


cbuild: build.c deps/file_handle.o deps/LibStr.o 
	$(CC) $(CFLAGS) -o $@ $^

cppbuild: build.cpp depcpp/file_handle.o  depcpp/LibStr.o
	$(CXX) $(CXXFLAGS) -o $@ $^



clean:
	rm $(BINS)
