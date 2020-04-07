LAB = lab5
.PHONY: all build run clean

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

 
