CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBS = -lcheck -lsubunit -lm -lgcov
FUNC_FILES_C = *.c
FUNC_FILES_O = *.o
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBNAME = s21_math.a
GLFLAGS = --coverage

all: s21_math.a

peer: gcov_report gcov_html

build_object_files:
	$(CC) $(FLAGS) $(GCOVFLAGS) $(GLFLAGS) -c $(FUNC_FILES_C)

build_library:
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

s21_math.a:
	$(CC) $(FLAGS) -c $(FUNC_FILES_C)
	make build_library
	rm -rf *.o

test: s21_math.a
	$(CC) tests/s21_abs_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_abs_test
	$(CC) tests/s21_acos_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_acos_test
	$(CC) tests/s21_asin_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_asin_test
	$(CC) tests/s21_atan_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_atan_test
	$(CC) tests/s21_ceil_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_ceil_test
	$(CC) tests/s21_cos_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_cos_test
	$(CC) tests/s21_exp_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_exp_test
	$(CC) tests/s21_fabs_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_fabs_test
	$(CC) tests/s21_floor_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_floor_test
	$(CC) tests/s21_fmod_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_fmod_test
	$(CC) tests/s21_log_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_log_test
	$(CC) tests/s21_pow_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_pow_test
	$(CC) tests/s21_sin_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_sin_test
	$(CC) tests/s21_sqrt_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_sqrt_test
	$(CC) tests/s21_tan_test.c -L. s21_math.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_tan_test
	make start_tests

start_tests:
	./s21_abs_test
	./s21_acos_test
	./s21_asin_test
	./s21_atan_test
	./s21_ceil_test
	./s21_cos_test
	./s21_exp_test
	./s21_fabs_test
	./s21_floor_test
	./s21_fmod_test
	./s21_log_test
	./s21_pow_test
	./s21_sin_test
	./s21_sqrt_test
	./s21_tan_test

gcov_report: clean build_object_files build_library test
	gcov $(FUNC_FILES_C)
	~/.local/bin/gcovr -r . --html --html-details -o s21_math.html

gcov_html: start_tests gcov_report
	xdg-open s21_math.html

clean:
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.gcda
	rm -rf *.a
	rm -rf *.info
	rm -rf *.html
	rm -rf *.css
	rm -rf s21_*_test

rebuild:
	make clean
	make