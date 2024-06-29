CC = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -g -fprofile-arcs -ftest-coverage
GOOGLE_TEST_FLAGS = -lgtest -lgtest_main -pthread
GCOV_FLAGS = -fprofile-exclude-files=tests/unit_tests.cpp -fprofile-arcs -ftest-coverage
GCOVR = $(shell which gcovr || echo "~/.local/bin/gcovr")
OS = $(shell uname -s)

all: s21_matrix_oop.a

s21_matrix_oop.a: s21_matrix_oop.o
	@ar rcs s21_matrix_oop.a *.o
	@rm -f *.o

s21_matrix_oop.o:
	@$(CC) $(CPPFLAGS) -c s21_matrix_oop.cpp s21_matrix_helpers.cpp s21_overload_operators.cpp

test: s21_matrix_oop.a unit_tests.o
	@$(CC) $(CPPFLAGS) tests/unit_tests.o s21_matrix_oop.a $(GOOGLE_TEST_FLAGS) -o unit_tests
	@make start_tests

unit_tests.o: tests/unit_tests.cpp
	@$(CC) $(CPPFLAGS) -c tests/unit_tests.cpp -o tests/unit_tests.o

start_tests:
	@./unit_tests

gcov_report: test
	@gcov s21_matrix_oop.cpp
	@$(GCOVR) -r . --exclude-throw-branches --html --html-details -o s21_matrix_oop.html --exclude 'main\.cpp' --exclude 'tests/.*'

	@make open

open:
	@echo "OPEN REPORT..."
ifeq ($(OS), Linux)
	@xdg-open s21_matrix_oop.html
else 
ifeq ($(OS), Darwin)
	@open s21_matrix_oop.html
endif
endif

clang_check:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	@clang-format -style=Google -n *.cpp *.hpp tests/*.cpp
	@rm .clang-format

clang:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	@clang-format -style=Google -i *.cpp *.hpp tests/*.cpp
	@rm .clang-format

val:
	@make test
ifeq ($(OS), Linux)
	@valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./unit_tests
else 
ifeq ($(OS), Darwin)
	@leaks -atExit -- ./unit_tests
endif
endif

cpp:
	@cppcheck *.cpp *.hpp tests/*.cpp

clean:
	@rm -f mem
	@rm -f *.o
	@rm -f s21_matrix_oop.a
	@rm -f tests/*.o
	@rm -f unit_tests
	@rm -f ./*.gcda
	@rm -f ./*.gcno
	@rm -f ./*.gcov
	@rm -f tests/*.gcda
	@rm -f tests/*.gcno
	@rm -f ./*.css
	@rm -f ./*.html
