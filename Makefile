CC=gcc

all: genetic
	$(CC) $(OPTIONS) -O3 ./obj/genetic.o ./src/main.c -o ./bin/genetic

genetic:
	mkdir -p obj
	$(CC) -O3 -c ./src/genetic.c -o ./obj/genetic.o

debug: OPTIONS += -DDEBUG
debug: all

trace: OPTIONS += -DTRACE
trace: all

clean:
	rm -f ./obj/* ./bin/*
doc:
	doxygen Doxyfile