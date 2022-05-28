CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++2a -g -fstandalone-debug

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/cord-utilities.cc ./src/cord.cc ./includes/cord-utilities.hpp ./includes/cord.hpp ./includes/cs128referencelist.hpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) ./src/driver.cc ./src/cord-utilities.cc ./src/cord.cc -o $@

bin/tests: ./tests/tests.cc obj/catch.o ./src/cord-utilities.cc ./src/cord.cc ./includes/cord-utilities.hpp ./includes/cord.hpp ./includes/cs128referencelist.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) ./tests/tests.cc obj/catch.o ./src/cord-utilities.cc ./src/cord.cc -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
