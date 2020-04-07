Lab = lab5
.PHONY: all build run clean valgrind

all: $(Lab)

clean: 
	@rm -rf $(Lab) *.o *.exe

build: $(Lab)

$(Lab): $(Lab).o
	gcc -o $(Lab) $(Lab).o

$(Lab).o: $(Lab).c
	gcc -c $(Lab).c

run: 
	$(Lab) 

valgrind:
	valgring --leak-check=full -v $(Lab)


 