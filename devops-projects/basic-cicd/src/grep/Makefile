CC = gcc
FLAGS = -Wall -Werror -Wextra --std=c11 -pedantic

s21_grep: s21_grep.c s21_grep.h
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

clean:
	clear
	rm -rf s21_grep

test:
	chmod u=rwx tests.sh
	bash tests.sh