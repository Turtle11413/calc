CC = gcc
FLAGS = -Wall -Werror -Wextra
OS:=$(shell uname)

clang:
	clang-format --style=Google -i */*.c */*/*.c */*.h */*/*.h */*.cpp

build_main:
	$(CC) $(FLAGS) -lm main.c backend/*.c -o main.out

main: build_main
	./main.out

build_test: 
	$(CC) $(FLAGS) -lm -lcheck test.c backend/*.c -o test.out

test: build_test
	./test.out

valgrind: build_main
	valgrind --tool=memcheck --leak-check=yes  ./main.out
clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.out
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.info
	rm -rf *.gch
	rm -rf test 
	rm -rf test.dSYM 
	rm -rf report 
	rm -rf gcov_report 
	rm -rf build
	rm -rf logs

