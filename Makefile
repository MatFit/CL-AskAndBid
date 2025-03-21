# Basic Make file with g++ compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wpedantic
SRC_DIR   = src

all: main

clean:
	rm -f main *.o

main: $(SRC_DIR)/main.cpp Driver.o Users.o Manager.o Factory.o Utils.o
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/main.cpp Driver.o Users.o Manager.o Factory.o Utils.o -o main

Driver.o: $(SRC_DIR)/Driver.cpp $(SRC_DIR)/Driver.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Driver.cpp

Users.o: $(SRC_DIR)/Users.cpp $(SRC_DIR)/Users.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Users.cpp

Manager.o: $(SRC_DIR)/Manager.cpp $(SRC_DIR)/Manager.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Manager.cpp

Factory.o: $(SRC_DIR)/Factory.cpp $(SRC_DIR)/Factory.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Factory.cpp

Utils.o: $(SRC_DIR)/Utils.cpp $(SRC_DIR)/Utils.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Utils.cpp


# test: test.cpp Driver.hpp Users.hpp
# 	$(CXX) $(CXXFLAGS) test.cpp -o test


