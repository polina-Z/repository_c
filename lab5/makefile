LAB = lab5
.PHONY: all build run clean valgrind

all: $(LAB)

clean: 
	@rm -rf $(LAB) *.o *.exe

build: $(Lab)

$(LAB): $(LAB).o
	gcc -o $(LAB) $(LAB).o

$(LAB).o: $(LAB).c
	gcc -c $(LAB).c

run: 
	$(LAB) 

valgrind:
	valgrind --leak-check=full -v $(LAB) 

 
