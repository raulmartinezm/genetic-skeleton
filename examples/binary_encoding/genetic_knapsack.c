
#define KNAPSACK_SIZE 10000
/** Max value that could have an element when randomly generated */
#define MAX_VALUE 100
/** Max weigth that could have an element when randomly generated */
#define MAX_WEIGHT 100


struct elements {
	int *element;
	int *value;
}





knapsack = (int*) malloc(KNAPSACK_SIZE*sizeof(int));

/**
 * A chromosome is valid if its total weight is little than the knapsack's total weight.
 * @param chrom chromosome
 */
int good_chromosome (Ptr_Chromosome chrom) {
	int i = 0,
	    accum = 0;

	for (i = 0 ; i < CHROMOSOME_LENGTH ; i++) {
		if ( chrom->gens[i] == 1) {
			accum += elements->value[i];
		}
	}

	return (accum > KNAPSACK_SIZE ? 0 : 1);
}