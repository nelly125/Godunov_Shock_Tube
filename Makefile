CC = g++
FLAGS=-std=c++14 -g  -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -fsanitize=address -O3

all: a.out

a.out: main.o starpu.o sample.o
	g++ -o a.out main.o starpu.p sample.o

starpu.o: starpu.cpp starpu.h initial.h
	g++ - c starpu.cpp

sample.o: sample.cpp sample.h initial.h
	g++ -c sample.cpp	
	
main.o: main.cpp initial.h starpu.h sample.h
	g++ main.cpp
clean:
	rm *.o a.out
