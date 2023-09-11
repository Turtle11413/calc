CC = gcc
FLAGS = -Wall -Werror -Wextra
GCOV = -fprofile-arcs -ftest-coverage
SRC=$(wildcard ./backend/*.c)
OBJ=$(patsubst %.c,%.o,$(SRC))
OS:=$(shell uname)

clang:
	clang-format --style=Google -i */*.c */*/*.c */*.h */*/*.h */*.cpp

calc.a: ${OBJ}
	ar rcs calc.a $^

build_main: calc.a
	$(CC) $(FLAGS) -lm main.c -L. calc.a -o main.out

main: build_main
	./main.out

valgrind_main: build_main
	valgrind --tool=memcheck --leak-check=yes ./main.out

valgrind_test: build_test
	valgrind --tool=memcheck --leak-check=yes ./test.out

leaks_main: build_main
	leaks -atExit -- ./main.out

leaks_test: build_test
	leaks -atExit -- ./test.out

build_test:
	$(CC) $(FLAGS) -lm -lcheck test.c backend/*.c -o test.out

test: build_test
	./test.out

gcov_report:
	$(CC) $(GCOV) test.c backend/*.c -o test.out -lcheck
	./test.out
	lcov -t "test" -o test.info -c -d ./
	genhtml test.info -o report
	open report/index.html

clean:
	rm -rf *.o
	rm -rf backend/*.o
	rm -rf *.a
	rm -rf *.out
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.info
	rm -rf *.gch
	rm -rf test.dSYM 
	rm -rf report 
	rm -rf gcov_report 
	rm -rf build
	rm -rf logs

