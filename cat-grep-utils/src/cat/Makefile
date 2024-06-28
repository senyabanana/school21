CC = gcc
FLAGS = -Wall -Werror -Wextra --std=c11 -pedantic

all: s21_cat

s21_cat: s21_cat.c s21_cat.h
	$(CC) $(FLAGS) s21_cat.c -o s21_cat

clean:
	clear
	rm -rf s21_cat

test:
	chmod u=rwx test_cat.sh
	bash test_cat.sh