CXX = g++
CXXFLAGS = -std=c++17 -O2

all: main test

main: main.cpp graph.cpp
	$(CXX) $(CXXFLAGS) main.cpp graph.cpp -o main

test: test.cpp graph.cpp
	$(CXX) $(CXXFLAGS) test.cpp graph.cpp \
	/usr/src/gtest/libgtest.a \
	/usr/src/gtest/libgtest_main.a \
	-pthread -o test

clean:
	rm -f main test
