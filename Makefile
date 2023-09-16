CC = gcc
FLAGS = -Wall -Werror -Wextra
GCOV = -fprofile-arcs -ftest-coverage
SRC=$(wildcard ./backend/*.c)
SRC_TEST=test.c
OBJ=$(patsubst %.c,%.o,$(SRC))
INSTALL_DIR=/usr/local/bin
TARGET=calc
OS:=$(shell uname)
ifeq ($(OS),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif

ifeq ($(OS),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lcheck -lm
endif

all: clean uninstall install

calc.a: ${OBJ}
	@ar rcs calc.a $^
	@ranlib calc.a

install: clean uninstall
	@mkdir build/
	@mkdir calculator/
	@cd build/ && qmake ../frontend/calc.pro && make
	@cp -rf build/calc.app calculator
	@make clean

run_app: install
ifeq ($(OS), Darwin)
	cd calculator/$(TARGET).app/Contents/MacOS && ./$(TARGET)
else
	cd build/ && ./$(TARGET)
endif

uninstall:
	rm -rf calculator

dvi:
	@$(OPEN_CMD) dvi.md

dist:
	@mkdir dist
	@cp -R frontend/ backend/ dvi.md Makefile dist
	@cd dist && tar cvzf smartCalc_v1.0.tgz *
	@cd dist && rm -rf *.c *.cpp *.h *.ui calc* dvi.md Makefile
	@rm -rf calculator

test:
	@$(CC) $(FLAGS) $(SRC) $(SRC_TEST) -o test.out $(ADD_LIB)
	@./test.out

gcov_report:
	@$(CC) $(GCOV) $(SRC) $(SRC_TEST) -o test.out $(ADD_LIB)
	@./test.out
	@lcov -t "test" -o test.info -c -d ./
	@genhtml test.info -o report
	@$(OPEN_CMD) report/index.html

clean:
	@rm -rf *.o backend/*.o *.a *.out *.gcno *.gcda *.info *.gch test.dSYM report gcov_report build* logs

clang:
	@clang-format --style=Google -i */*.c */*.h */*.cpp

check_style:
	@clang-format --style=Google -n */*.c */*.h */*.cpp