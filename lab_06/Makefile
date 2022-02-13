.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic

all: lab_06

bin:
	mkdir -p bin

lab_06: src/main.cpp bin/my_vector.o include/*.h bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

bin/%.o: src/%.cpp include/*.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<

clean:
	rm -rf bin main