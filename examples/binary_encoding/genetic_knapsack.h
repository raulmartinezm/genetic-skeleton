/** @file genetic_knapsack.h
 *  @brief Header of genetic algorithm implementation for knapsack problem.
 *
 * @see http://en.wikipedia.org/wiki/Knapsack_problem
 */

#include <stdio.h>
#include <stdlib.h>

/** Initial fitness value, after being created and before evaluation all chromosomes are "bad". */
#define BAD_CHROM  -999999
// Mutation types for the mutation function 
#define BIT_STRING_MUTATION	1
#define FLIP_BITS	2

// Chromosome crossover methods.
#define ONE_POINT_CROSS 1
#define TWO_POINT_CROSS 2
#define CUT_AND_SPLICE_CROSS 3
#define UNIFORM_CROSSOVER 4
#define HALF_UNIFORM_CROSSOVER 5


struct Chromosome_configuration {
	int total_chrom, 	/**< Population. Total number of chromosomes */
	    max_iter_best,  /**< Max number of iterations of the best chromosome */
	    max_iter,		/**< Max number of iterations of the algorithm */
	    chrom_length; 	/**< Length of chromosome. Number of gens */
};

/** @struct Chromosome
 *  @brief struct type of a chromosome.
 * This defines a chromosome with a binary enconding
 */
struct Chromosome
{
	int id,     		/**< Chromosome id or TAG. */
	    *gens;			/**< Chromosome's discrete encoding (0 or 1). */
	double  evaluation; /**< Fitness value of the chromosome */
};


typedef struct Chromosome_configuration * Ptr_config;
typedef struct Chromosome * Ptr_Chromosome;

Ptr_Chromosome create_chromosome(int id, const int chrom_length);
void free_chromosome(Ptr_Chromosome chrom);
double evaluate_chromosome(Ptr_Chromosome chrom, const int chrom_length);
int good_chromosome(Ptr_Chromosome chrom, const int chrom_length);
void classify_chromosome(Ptr_Chromosome*,const int total_chrom);
void mutate(Ptr_Chromosome chrom, const int chrom_length, int mutation_type);
void crossover(Ptr_Chromosome a, Ptr_Chromosome b, Ptr_Chromosome *c1, Ptr_Chromosome *c2, const int chrom_length, int cross_type);
int genetic_main(Ptr_config config);
void show_chromosome(Ptr_Chromosome chrom, const int chrom_length);
