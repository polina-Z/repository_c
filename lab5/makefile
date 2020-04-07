TARGET = lab5
.PHONY: all build run clean

all: $(TARGET)

clean: 
	@del $(TARGET) *.o *.exe

build: $(TARGET)

$(TARGET): $(TARGET).o
	gcc -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).c
	gcc -c $(TARGET).c

run: 
	$(TARGET) 

 