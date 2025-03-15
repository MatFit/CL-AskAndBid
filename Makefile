# Basic Make file with g++ compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wpedantic

all: main

clean:
	rm -f main *.o

main: main.cpp Driver.o Users.o Manager.o
	$(CXX) $(CXXFLAGS) main.cpp Driver.o Users.o Manager.o -o main

Driver.o: Driver.cpp Driver.h
	$(CXX) $(CXXFLAGS) -c Driver.cpp

Users.o: Users.cpp Users.h
	$(CXX) $(CXXFLAGS) -c Users.cpp

Manager.o: Manager.cpp Manager.h
	$(CXX) $(CXXFLAGS) -c Manager.cpp

test: test.cpp Driver.hpp Users.hpp
	$(CXX) $(CXXFLAGS) test.cpp -o test


