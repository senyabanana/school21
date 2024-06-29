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
	@chmod +x ./build/SmartCalc
	@./build/SmartCalc
else
ifeq ($(OS), Darwin)
	@open build/SmartCalc.app/Contents/MacOS/SmartCalc
endif
endif

install:
	@make clean
	@mkdir build
ifeq ($(OS), Linux)
	@cd view && qmake6 || qmake && make && make clean && rm Makefile && cd ../ && mv view/SmartCalc build
else
ifeq ($(OS), Darwin)
	@cd view && qmake6 || qmake && make && make clean && rm Makefile && mv SmartCalc.app ../build
endif
endif

uninstall:
	@rm -rf build*
	@rm -rf view/.qmake.stash
	@rm -rf view/SmartCalc.pro.user

dvi:
	@open calculator.pdf

dist:
	@rm -rf SmartCalcv2.0_dist/
	@mkdir SmartCalcv2.0_dist/
	@mkdir SmartCalcv2.0_dist/src
ifeq ($(OS), Linux)
	@cp -r ./build/SmartCalc SmartCalcv2.0_dist/src/
else
ifeq ($(OS), Darwin)
	@cp -r ./build/SmartCalc.app/Contents/MacOS/SmartCalc SmartCalcv2.0_dist/src/
endif
endif
	@tar cvzf SmartCalcv2.0_dist.tgz SmartCalcv2.0_dist/
	@rm -rf SmartCalcv2.0_dist/

calculator.a: calculator.o
	@ar rcs calculator.a *.o
	@rm -f *.o

calculator.o:
	@$(CC) $(CPPFLAGS) -c ./model/model.cpp ./controller/controller.cpp

test: calculator.a unit_tests.o
	@$(CC) $(CPPFLAGS) tests/unit_tests.o calculator.a $(GOOGLE_TEST_FLAGS) -o unit_tests
	@make start_tests

unit_tests.o: tests/unit_tests.cpp
	@$(CC) $(CPPFLAGS) -c tests/unit_tests.cpp -o tests/unit_tests.o

start_tests:
	@./unit_tests

clang_check:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	@clang-format -style=Google -n ./model/*.cpp ./controller/*.cpp ./model/*.h ./controller/*.h tests/*.cpp ./view/*.h ./view/*.cpp
	@rm .clang-format

clang:
	@cp ../materials/linters/.clang-format ../src/.clang-format
	@clang-format -style=Google -i ./model/*.cpp ./controller/*.cpp ./model/*.h ./controller/*.h tests/*.cpp ./view/*.h ./view/*.cpp
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
