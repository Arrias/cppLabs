.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++14 -Wall -pedantic

all: lab_07

bin:
	mkdir -p bin

lab_07: src/main.cpp bin/matrix.o include/*.h bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

bin/%.o: src/%.cpp include/*.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<

clean:
	rm -rf bin main
