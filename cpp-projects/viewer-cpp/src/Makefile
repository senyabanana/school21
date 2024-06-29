CC = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -g
GOOGLE_TEST_FLAGS = -lgtest -lgtest_main -pthread
OS = $(shell uname -s)

ifeq ($(OS), Linux)
	CPPFLAGS += -D LINUX
else 
ifeq ($(OS), Darwin)
	CPPFLAGS += -D MAC
endif
endif

all: install open

open:
ifeq ($(OS), Linux)
	@chmod +x ./build/3dViewer
	@./build/3dViewer
else
ifeq ($(OS), Darwin)
	@open build/3dViewer.app/Contents/MacOS/3dViewer
endif
endif

install:
	@make clean
	@mkdir build
ifeq ($(OS), Linux)
	@cd view && qmake6 || qmake && make && make clean && rm Makefile && cd ../ && mv view/3dViewer build
else
ifeq ($(OS), Darwin)
	@cd view && qmake6 || qmake && make && make clean && rm Makefile && mv 3dViewer.app ../build
endif
endif

uninstall:
	@rm -rf build*
	@rm -rf view/.qmake.stash
	@rm -rf view/3dViewer.pro.user

dvi:
	@open viewer.pdf

dist:
	@rm -rf 3dViewer_v2.0_dist/
	@mkdir 3dViewer_v2.0_dist/
	@mkdir 3dViewer_v2.0_dist/src
ifeq ($(OS), Linux)
	@cp -r ./build/3dViewer 3dViewer_v2.0_dist/src/
else
ifeq ($(OS), Darwin)
	@cp -r ./build/3dViewer.app/Contents/MacOS/3dViewer 3dViewer_v2.0_dist/src/
endif
endif
	@tar cvzf 3dViewer_v2.0_dist.tgz 3dViewer_v2.0_dist/
	@rm -rf 3dViewer_v2.0_dist/

viewer.a: viewer.o
	@ar rcs viewer.a *.o
	@rm -f *.o

viewer.o:
	@$(CC) $(CPPFLAGS) -c ./model/*/*.cpp ./controller/controller.cpp

test: viewer.a unit_tests.o
	@$(CC) $(CPPFLAGS) tests/unit_tests.o viewer.a $(GOOGLE_TEST_FLAGS) -o unit_tests
	@make start_tests

unit_tests.o: tests/unit_tests.cpp
	@$(CC) $(CPPFLAGS) -c tests/unit_tests.cpp -o tests/unit_tests.o

start_tests:
	@./unit_tests

clang_check:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	@clang-format -style=Google -n ./model/*/*.cpp ./model/*/*.h ./controller/* ./view/*.cpp ./view/*.h ./tests/*.cpp
	@rm .clang-format

clang:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	@clang-format -style=Google -i ./model/*/*.cpp ./model/*/*.h ./controller/* ./view/*.cpp ./view/*.h ./tests/*.cpp
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

clean:
	@rm -rf *.o
	@rm -rf tests/*.o
	@rm -rf *.a
	@rm -rf ./unit_tests
	@rm -rf *.tgz
	@make uninstall
