.PHONY: all build run clean

all: lab5

clean: 
	del lab5 *.o *.exe

build: lab5

lab5: lab5.o
	gcc -o lab5 lab5.o

lab5.o: lab5.c
	gcc -c lab5.c

run: 
	lab5 

 