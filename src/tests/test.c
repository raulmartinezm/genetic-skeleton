#define CHROM_LENGTH 100

#include "minunit.h"
#include "../genetic.h"

int tests_run = 0;

static char* test_create_chromosome() {
	Ptr_Chromosome c = create_chromosome(1, CHROM_LENGTH);

	for (int i = 0; i < CHROM_LENGTH; i++) {
		mu_assert("ERROR: all gens should have value 0", c->gens[i] == 0);
	}
	free_chromosome(c);

	return 0;
}

static char* test_seed_chromosome_gens() {
	Ptr_Chromosome c = create_chromosome(1, CHROM_LENGTH);
	seed_with_random_values(c, CHROM_LENGTH);

	for (int i = 0; i < CHROM_LENGTH; i++) {
		mu_assert("ERROR: gens should have 0 or 1 value", (c->gens[i] == 0 || c->gens[i] == 1));
	}
	free_chromosome(c);

	return 0;
}


static char* test_classify_chromosomes() {
	Ptr_Chromosome c1 = create_chromosome(1, CHROM_LENGTH);
	c1->evaluation = 32.0;
	Ptr_Chromosome c2 = create_chromosome(2, CHROM_LENGTH);
	c2->evaluation = 500.0;
	Ptr_Chromosome c3 = create_chromosome(3, CHROM_LENGTH);
	c3->evaluation = 122.0;

	ChromosomeList chromosome_list = (ChromosomeList)malloc(3 * sizeof(Ptr_Chromosome));;
	chromosome_list[0] = c1;
	chromosome_list[1] = c2;
	chromosome_list[2] = c3;

	classify_chromosomes(chromosome_list, 3);

	mu_assert("bad chromosome classification", chromosome_list[0] == c2);
	mu_assert("bad chromosome classification", chromosome_list[1] == c3);
	mu_assert("bad chromosome classification", chromosome_list[2] == c1);

	free_chromosome(c1);
	free_chromosome(c2);
	free_chromosome(c3);
	free(chromosome_list);
	return 0;
}


static char* all_tests() {

	mu_run_test(test_create_chromosome);
	mu_run_test(test_classify_chromosomes);
	mu_run_test(test_seed_chromosome_gens);

	return 0;
}

int main() {
	char* result = all_tests();

	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TEST PASSED\n");
	}

	printf("Tests run %d\n", tests_run);

	return result != 0;
}
