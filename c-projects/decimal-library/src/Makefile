CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBS = -lcheck -lsubunit -lm -lgcov
FUNC_FILES_C = *.c
FUNC_FILES_O = *.o
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage -fprofile-exclude-files=unit_tests.c
LIBNAME = s21_decimal.a
GLFLAGS = --coverage

all: s21_decimal.a

peer: gcov_report gcov_html

build_object_files:
	$(CC) $(FLAGS) $(GCOVFLAGS) $(GLFLAGS) -c $(FUNC_FILES_C)

build_library:
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

s21_decimal.a:
	$(CC) $(FLAGS) -c $(FUNC_FILES_C)
	make build_library
	rm -rf *.o

test: s21_decimal.a
	$(CC) tests/unit_tests.c -L. s21_decimal.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o unit_tests
	make start_tests

start_tests:
	./unit_tests

gcov_report: clean build_object_files build_library test
	gcov $(FUNC_FILES_C)
	~/.local/bin/gcovr -r . --html --html-details -o s21_decimal.html

gcov_html: gcov_report
	xdg-open s21_decimal.html

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format

clean:
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.gcda
	rm -rf *.a
	rm -rf *.html
	rm -rf *.css
	rm -rf ./unit_tests

rebuild:
	make clean
	make