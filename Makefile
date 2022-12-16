CC=gcc
FLAGS=-O3
BINARY_OUT=./bin/genetic

all: genetic
	$(CC) $(OPTIONS) $(FLAGS) ./obj/genetic.o ./src/main.c -o $(BINARY_OUT)

genetic:
	mkdir -p obj bin
	$(CC) $(FLAGS) -c ./src/genetic.c -o ./obj/genetic.o

debug: OPTIONS += -DDEBUG
debug: all

trace: OPTIONS += -DTRACE
trace: all

test: genetic
	$(CC) $(OPTIONS) $(FLAGS) ./obj/genetic.o ./src/tests/test.c -o ./bin/tests
	./bin/tests

clean:
	rm -frv ./obj/* ./bin/* 
doc:
	doxygen Doxyfile -f

run:
	$(BINARY_OUT)

