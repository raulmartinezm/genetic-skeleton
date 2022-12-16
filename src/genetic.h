/** @file genetic.h
 *  @brief Header of genetic algorithm skeleton.
 *
 * A list of genetic algorithm applications
 * @see http://en.wikipedia.org/wiki/List_of_genetic_algorithm_applications
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define	EXIT_SUCCESS	0

 /** Initial fitness value, after being created and before evaluation all chromosomes are "bad". */
#define BAD_CHROM -999999
// Mutation types for the mutation function
#define BIT_STRING_MUTATION 1
#define FLIP_BITS 2

// Chromosome crossover methods.
#define ONE_POINT_CROSS 10
#define TWO_POINT_CROSS 11
// #define CUT_AND_SPLICE_CROSS 12
// #define UNIFORM_CROSSOVER 13
// #define HALF_UNIFORM_CROSSOVER 14

struct Chromosome_configuration {
	int total_chrom,   /**< Population. Total number of chromosomes */
		max_iter_best, /**< Max number of iterations of the best chromosome */
		max_iter,	   /**< Max number of iterations of the algorithm */
		chrom_length;  /**< Length of chromosome. Number of gens */
};

typedef int* BinaryGens;

/** @struct Chromosome
 *  @brief struct type of a chromosome with binary encoding.
 */
struct Chromosome {
	int id;		   		/**< Chromosome id or TAG. */
	BinaryGens gens;	/**< Chromosome's discrete encoding (values are 0 or 1). */
	double evaluation;  /**< Fitness value of the chromosome */
};


typedef struct Chromosome_configuration* Ptr_config;
typedef struct Chromosome* Ptr_Chromosome;
typedef struct Chromosome** ChromosomeList;

Ptr_Chromosome create_chromosome(int id, const int chrom_length);
void seed_with_random_values(Ptr_Chromosome chrom, int chrom_length);
void free_chromosome(Ptr_Chromosome chrom);
double evaluate_chromosome(Ptr_Chromosome chrom, const int chrom_length);
int good_chromosome(Ptr_Chromosome chrom, const int chrom_length);
void classify_chromosomes(ChromosomeList, const int total_chrom);
void mutate(Ptr_Chromosome chrom, const int chrom_length, int mutation_type);
void crossover(Ptr_Chromosome a, Ptr_Chromosome b, ChromosomeList c1, ChromosomeList c2, const int chrom_length, int cross_type);
int genetic_main(Ptr_config config);
void show_chromosome(Ptr_Chromosome chrom, const int chrom_length);
