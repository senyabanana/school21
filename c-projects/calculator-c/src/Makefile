CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
TEST_FLAGS = -lcheck -lpthread -lm
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GCOVDIR = gcov
OS = $(shell uname -s)

ifeq ($(OS), Linux)
	CFLAGS += -D LINUX -lsubunit
else 
ifeq ($(OS), Darwin)
	CFLAGS += -D MAC
endif
endif

all: install test gcov_report dvi

open:
ifeq ($(OS), Linux)
	chmod +x ./build/SmartCalc
	./build/SmartCalc
else
ifeq ($(OS), Darwin)
	open build/SmartCalc.app/Contents/MacOS/SmartCalc
endif
endif

install:
	make clean
	mkdir build
ifeq ($(OS), Linux)
	cd SmartCalc && qmake6 || qmake && make && make clean && rm Makefile && cd ../ && mv SmartCalc/SmartCalc build
else
ifeq ($(OS), Darwin)
	cd SmartCalc && qmake6 || qmake && make && make clean && rm Makefile && mv SmartCalc.app ../build
endif
endif

uninstall:
	rm -rf build*
	rm -rf SmartCalc/.qmake.stash

dvi:
	open calculator.pdf

dist:
	rm -rf SmartCalcv1.0_dist/
	mkdir SmartCalcv1.0_dist/
	mkdir SmartCalcv1.0_dist/src
	cp -r ./build/SmartCalc SmartCalcv1.0_dist/src/
	cp ./calculator.pdf SmartCalcv1.0_dist/
	tar cvzf SmartCalcv1.0_dist.tgz SmartCalcv1.0_dist/
	rm -rf SmartCalcv1.0_dist/

calculator.a: calculator.o
	ar rcs calculator.a calculator.o

calculator.o: calculator.c
	$(CC) $(CFLAGS) -c calculator.c -o calculator.o

test: calculator.a unit_tests.o
	$(CC) $(CFLAGS) tests/unit_tests.o calculator.a $(TEST_FLAGS) -o unit_tests
	make start_tests

unit_tests.o: tests/unit_tests.c
	$(CC) $(CFLAGS) -c tests/unit_tests.c -o tests/unit_tests.o

start_tests:
	./unit_tests

gcov_report: $(GCOVDIR)/gcov_test.info
	xdg-open $(GCOVDIR)/calculator.html

$(GCOVDIR)/gcov_test.info: $(GCOVDIR)/gcov_test $(GCOVDIR)/gcov_test.gcda
	~/.local/bin/gcovr -r . --html --html-details -o $(GCOVDIR)/calculator.html --exclude tests/unit_tests.c

$(GCOVDIR)/gcov_test.gcda: $(GCOVDIR)/gcov_test
	chmod +x *
	./$(GCOVDIR)/gcov_test

$(GCOVDIR)/gcov_test: tests/unit_tests.c calculator.c
	mkdir $(GCOVDIR)
	$(CC) $(CFLAGS) --coverage tests/unit_tests.c calculator.c $(TEST_FLAGS) -o $(GCOVDIR)/gcov_test

clang_check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i *.c *.h
	rm .clang-format

val:
	valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./unit_tests

cpp:
	cppcheck *.c *.h

clean:
	rm -rf *.o
	rm -rf tests/*.o
	rm -rf gcov/
	rm -rf *.a
	rm -rf ./unit_tests
	rm -rf *.tgz
	make uninstall