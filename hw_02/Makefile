
CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++2a

all: hw_02

obj/huffman.o: src/huffman.cpp include/huffman.h include/huffman_util.h
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c src/huffman.cpp -o obj/huffman.o -I include

obj/main.o: src/main.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o -I include

hw_02: obj/huffman.o obj/main.o
	$(CXX) $(CXXFLAGS) obj/huffman.o obj/main.o -o hw_02 -I include

obj/doctest.o: test/doctest.cpp include/doctest.h include/doctest_fwd.h
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c test/doctest.cpp -o obj/doctest.o -I include

obj/autotest.o: test/autotest.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c test/autotest.cpp -o obj/autotest.o -I include

test: obj/autotest.o obj/doctest.o obj/huffman.o
	$(CXX) $(CXXFLAGS) obj/autotest.o obj/doctest.o obj/huffman.o -o hw_02_test -I include

clean:
	rm -R obj

.PHONY: clean all test