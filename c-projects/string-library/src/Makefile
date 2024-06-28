CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBS = -lcheck -lsubunit -lm -lgcov
FUNC_FILES_C = *.c
FUNC_FILES_O = *.o
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBNAME = s21_string.a
GLFLAGS = --coverage

all: s21_string.a

peer: gcov_report gcov_html

build_object_files:
	$(CC) $(FLAGS) $(GCOVFLAGS) $(GLFLAGS) -c $(FUNC_FILES_C)

build_library:
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

s21_string.a:
	$(CC) $(FLAGS) -c $(FUNC_FILES_C)
	make build_library
	rm -rf *.o

test: s21_string.a
	$(CC) tests/s21_memchr_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_memchr_test
	$(CC) tests/s21_memcmp_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_memcmp_test
	$(CC) tests/s21_memcpy_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_memcpy_test
	$(CC) tests/s21_memset_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_memset_test
	$(CC) tests/s21_strncat_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strncat_test
	$(CC) tests/s21_strchr_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strchr_test
	$(CC) tests/s21_strncmp_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strncmp_test
	$(CC) tests/s21_strncpy_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strncpy_test
	$(CC) tests/s21_strcspn_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strcspn_test
	$(CC) tests/s21_strerror_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strerror_test
	$(CC) tests/s21_strlen_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strlen_test
	$(CC) tests/s21_strpbrk_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strpbrk_test
	$(CC) tests/s21_strrchr_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strrchr_test
	$(CC) tests/s21_strstr_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strstr_test
	$(CC) tests/s21_strtok_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_strtok_test
	$(CC) tests/s21_sprintf_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_sprintf_test
	$(CC) tests/s21_sscanf_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_sscanf_test
	$(CC) tests/s21_to_upper_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_to_upper_test
	$(CC) tests/s21_to_lower_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_to_lower_test
	$(CC) tests/s21_insert_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_insert_test
	$(CC) tests/s21_trim_test.c -L. s21_string.a $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) -o s21_trim_test
	make start_tests

start_tests:
	./s21_memchr_test
	./s21_memcmp_test
	./s21_memcpy_test
	./s21_memset_test
	./s21_strncat_test
	./s21_strchr_test
	./s21_strncmp_test
	./s21_strncpy_test
	./s21_strcspn_test
	./s21_strerror_test
	./s21_strlen_test
	./s21_strpbrk_test
	./s21_strrchr_test
	./s21_strstr_test
	./s21_strtok_test
	./s21_sprintf_test
	./s21_sscanf_test
	./s21_to_upper_test
	./s21_to_lower_test
	./s21_insert_test
	./s21_trim_test

val:
	valgrind --tool=memcheck --leak-check=yes ./s21_memchr_test
	valgrind --tool=memcheck --leak-check=yes ./s21_memcmp_test
	valgrind --tool=memcheck --leak-check=yes ./s21_memcpy_test
	valgrind --tool=memcheck --leak-check=yes ./s21_memset_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strncat_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strchr_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strncmp_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strncpy_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strcspn_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strerror_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strlen_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strpbrk_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strrchr_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strstr_test
	valgrind --tool=memcheck --leak-check=yes ./s21_strtok_test
	valgrind --tool=memcheck --leak-check=yes ./s21_sprintf_test
	valgrind --tool=memcheck --leak-check=yes ./s21_to_upper_test
	valgrind --tool=memcheck --leak-check=yes ./s21_to_lower_test
	valgrind --tool=memcheck --leak-check=yes ./s21_insert_test
	valgrind --tool=memcheck --leak-check=yes ./s21_trim_test

gcov_report: clean build_object_files build_library test
	gcov $(FUNC_FILES_C)
	~/.local/bin/gcovr -r . --html --html-details -o s21_string.html

gcov_html: gcov_report
	xdg-open s21_string.html

clean:
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.gcda
	rm -rf *.a
	rm -rf *.html
	rm -rf *.css
	rm -rf s21_*_test

rebuild:
	make clean
	make