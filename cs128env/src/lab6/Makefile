CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec

bin/exec: ./src/driver.cc ./src/solution.cc $(CXX) $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: exec