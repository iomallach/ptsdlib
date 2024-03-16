all: main
	./main

main: clean
	clang -I./include --debug -pedantic -o main main.c vector.c

clean:
	rm -f ./main
