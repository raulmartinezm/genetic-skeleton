CC=gcc
FLAGS=-O3

all: binary_encoding

.PHONY: binary_encoding
binary_encoding: DIR += binary_encoding
binary_encoding: MAIN += knapsack.c
binary_encoding: GENETIC += genetic_knapsack.c
binary_encoding:
	echo $(DIR)
	mkdir -p ./$(DIR)/obj ./$(DIR)/bin
	$(CC) $(FLAGS) -c ./$(DIR)/$(GENETIC) -o ./$(DIR)/obj/genetic.o
	$(CC) $(OPTIONS) $(FLAGS) ./$(DIR)/obj/genetic.o ./$(DIR)/$(MAIN) -o ./$(DIR)/bin/genetic_knapsack

debug: OPTIONS += -DDEBUG
debug: all

trace: OPTIONS += -DTRACE
trace: all

clean: DIR += binary_encoding
clean:
	rm -fv ./$(DIR)/obj/* ./$(DIR)/bin/* 
