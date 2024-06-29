CC = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17
TEST_FLAGS = -lgtest -pthread
OS = $(shell uname -s)

all: clean test

clean:
	@rm -rf containers_tests

test: clean
	@$(CC) $(CXXFLAGS) tests/*.cpp $(TEST_FLAGS) -o containers_tests
	@./containers_tests

clang_check:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	@clang-format -style=Google -n *.h ./*/*.hpp ./*/*.tpp tests/*.cpp tests/*.hpp
	@rm .clang-format

clang:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	@clang-format -style=Google -i *.h ./*/*.hpp ./*/*.tpp tests/*.cpp tests/*.hpp
	@rm .clang-format

val:
	@make test
ifeq ($(OS), Linux)
	@valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./containers_tests
else 
ifeq ($(OS), Darwin)
	@leaks -atExit -- ./containers_tests
endif
endif