#define CHROM_LENGTH 100

#include "minunit.h"
#include "../genetic.h"

int tests_run = 0;

static char * test_seed_chromosome() {
	int i = 0,
		count = 0;

	Ptr_Chromosome c = create_chromosome(1,CHROM_LENGTH);
	seed_with_random_values(c, CHROM_LENGTH);

	for ( i = 0 ; i < CHROM_LENGTH ; i++) {
		if ( c->gens[i] == 1 ) { count++; }
	}
	// free before assert or won't be freed	
	free_chromosome(c);

	mu_assert("ERROR, NO GEN DISTINCT OF 0 FOUND AFTER SEEDING", (count != 0));

	return 0;
}

static char * all_tests(){

	mu_run_test(test_seed_chromosome);


	return 0;
}

int main() {
	char *result = all_tests();

	if (result != 0){
		printf("%s\n",result);
	}
	else {
		printf("ALL TEST PASSED\n");
	}

	printf("Tests run %d\n", tests_run);

	return result != 0;
}