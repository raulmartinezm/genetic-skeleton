/** @file genetic.h
 *  @brief Header of genetic algorithm skeleton.
 *
 * A list of genetic algorithm applications
 * @see http://en.wikipedia.org/wiki/List_of_genetic_algorithm_applications
 */

#include <stdio.h>
#include <stdlib.h>

//#define TRACE 1

/** Initial fitness value, after being created and before evaluation all chromosomes are "bad". */
#define BAD_CHROM  -999999
/** Chromosome size of number of gens */
#define CHROMOSOME_LENGTH 20
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
	    max_iter 		/**< Max number of iterations of the algorithm */
	    chrom_legth; 	/**< Length of chromosome. Number of gens */
}

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

Ptr_Chromosome create_chromosome(int id);
void free_chromosome(Ptr_Chromosome chrom);
double evaluate_chromosome(Ptr_Chromosome chrom);
int good_chromosome(Ptr_Chromosome chrom);
void classify_chromosome(Ptr_Chromosome*, int total_chrom);
void mutate(Ptr_Chromosome chrom, int mutation_type);
void crossover(Ptr_Chromosome a, Ptr_Chromosome b, Ptr_Chromosome *c1, Ptr_Chromosome *c2);
int genetic_main(Ptr_Chromosome_config config);

void show_chromosome(Ptr_Chromosome chrom);
