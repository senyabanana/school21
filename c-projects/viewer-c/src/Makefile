CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
TEST_FLAGS = -lcheck -lpthread -lm
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GCOVDIR = gcov
OS = $(shell uname -s)

ifeq ($(OS), Linux)
 CFLAGS += -D LINUX
 TEST_FLAGS += -lsubunit
else 
ifeq ($(OS), Darwin)
 CFLAGS += -D MAC -I/opt/homebrew/opt/check/include
 TEST_FLAGS +=  -L/opt/homebrew/opt/check/lib
endif
endif

all: install test gcov_report dvi

open:
ifeq ($(OS), Linux)
	chmod +x ./build/3dViewer
	./build/3dViewer
else
ifeq ($(OS), Darwin)
	open build/3dViewer.app/Contents/MacOS/3dViewer
endif
endif

install:
	make clean
	mkdir build
ifeq ($(OS), Linux)
	cd 3dViewer && qmake6 || qmake && make && make clean && rm Makefile && cd ../ && mv 3dViewer/3dViewer build
else
ifeq ($(OS), Darwin)
	cd 3dViewer && qmake6 || qmake && make && make clean && rm Makefile && mv 3dViewer.app ../build
endif
endif

uninstall:
	rm -rf build*
	rm -rf 3dViewer/.qmake.stash

dvi:
	open viewer.pdf

dist:
	rm -rf Viewerv_dist/
	mkdir Viewerv_dist/
	mkdir Viewerv_dist/src
	cp -r ./build/3dViewer Viewerv_dist/src/
	# cp ./viewer.pdf Viewerv_dist/
	tar cvzf Viewerv_dist.tgz Viewerv_dist/
	rm -rf Viewerv_dist/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.a: %.o
	ar rcs $@ $^

test: viewer.a matrix.a affine.a unit_tests.o
	$(CC) $(CFLAGS) tests/unit_tests.o viewer.a matrix.a affine.a $(TEST_FLAGS) -o unit_tests
	make start_tests
	rm -rf tests/*.o
	rm -rf *.a

unit_tests.o: tests/unit_tests.c
	$(CC) $(CFLAGS) -c tests/unit_tests.c -o tests/unit_tests.o

start_tests:
	./unit_tests

gcov_report: $(GCOVDIR)/gcov_test.info
ifeq ($(OS), Linux)
	xdg-open $(GCOVDIR)/viewer.html
else 
ifeq ($(OS), Darwin)
	open $(GCOVDIR)/viewer.html
endif
endif

$(GCOVDIR)/gcov_test.info: $(GCOVDIR)/gcov_test $(GCOVDIR)/gcov_test.gcda
ifeq ($(OS), Linux)
	~/.local/bin/gcovr -r . --html --html-details -o $(GCOVDIR)/viewer.html --exclude tests/unit_tests.c
else 
ifeq ($(OS), Darwin)
	/opt/homebrew/bin/gcovr -r . --html --html-details -o $(GCOVDIR)/viewer.html --exclude tests/unit_tests.c	
endif
endif

$(GCOVDIR)/gcov_test.gcda: $(GCOVDIR)/gcov_test
	chmod +x *
	./$(GCOVDIR)/gcov_test
ifeq ($(OS), Darwin)
	mv ./*.gcno $(GCOVDIR)/
	mv ./*.gcda $(GCOVDIR)/
endif

$(GCOVDIR)/gcov_test: tests/unit_tests.c viewer.c matrix.c affine.c
	mkdir $(GCOVDIR)
	$(CC) $(CFLAGS) --coverage tests/unit_tests.c viewer.c matrix.c affine.c $(TEST_FLAGS) -o $(GCOVDIR)/gcov_test

clang_check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i *.c *.h
	rm .clang-format

val:
	make test
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
