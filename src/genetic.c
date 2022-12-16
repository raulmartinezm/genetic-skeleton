/** @file genetic.c
 *  @brief Partial implementation of genetic algorithm.
 *  Skeleton of genetic algorithm using binary encoding for chromosome.
 */

#include "genetic.h"

 /**
  * Creates a new chromosome with a binary encoding.
  * @param id Chromosome label.
  * @return new Chromosome with random gens initialized to 0.
  */
Ptr_Chromosome create_chromosome(int id, const int chrom_length) {
#ifdef TRACE
    printf("---> create_chromosome. Chromosome: %d\n", id);
    fflush(stdout);
#endif

    Ptr_Chromosome chrom = NULL;

    chrom = (Ptr_Chromosome)malloc(sizeof(struct Chromosome));
    chrom->gens = (int*)malloc(chrom_length * sizeof(int));

    chrom->id = id;
    chrom->evaluation = BAD_CHROM;
    for (int i = 0; i < chrom_length; i++) {
        chrom->gens[i] = 0;
    }

    return chrom;
}

/**
 * Populates a chromosome gens with random 0 or 1 values.
 * @param chrom Chromosome.
 * @param chrom_length Number of gens in a chromosome.
 * @return new Chromosome with random gens initialized to 0.
 */
void seed_with_random_values(Ptr_Chromosome chrom, int chrom_length) {
    for (int i = 0; i < chrom_length; i++) {
        chrom->gens[i] = rand() % 2;
    }
}

/**
 * Free memory allocated for chromosome.
 * @param chrom Chromosome.
 */
void free_chromosome(Ptr_Chromosome chrom) {

    int* gens;
    gens = chrom->gens;

    free(gens);
    free(chrom);
    chrom = NULL;
    gens = NULL;
}

/**
 * Fitness function. Evaluates a chromosome and assigns the result to the fitness parameter.
 * The value of the fitness depends of the type of problem.
 * @param chrom Chromosome to evaluate.
 * @param chrom_length Number of gens in a chromosome.
 * @return fitness value.
 */
double evaluate_chromosome(Ptr_Chromosome chrom, const int chrom_length) {
    // IMPLEMENT THE FITNESS FUNCTION

    double fitness = 0.0;

    /*
        fitness = Evaluate the chromosome.
        chrom->evaluation = fitness;
    */

    return fitness;
}

/*!
 * Checks if the chromosome is valid. The validity of a chromosome depends of the problem.
 * @param chrom Chromosome to evaluate.
 * @param chrom_length Number of gens in a chromosome.
 * @return 0 if invalid, 1 if valid.
 */
int good_chromosome(Ptr_Chromosome chrom, const int chrom_length) {

    int valid = 1;
    // IMPLEMENT THE RULES OR CONDITIONS FOR A VALID/INVALID CHROMOSOME

    return valid;
}

/**
 * Sort the chromosomes list by fitness.
 * @param list Chromosomes' list.
 * @param total Total number of chromosomes.
 */
void classify_chromosomes(ChromosomeList list, const int total) {
#ifdef TRACE
    printf("---> funcion classify_chromosomes\n");
    fflush(stdout);
#endif
    int i, j;
    Ptr_Chromosome chrom;
    double valor;

    // Candidate for being parallelized
    for (i = 0; i < total; i++) {
        for (j = i + 1; j < total; j++) {
            chrom = *(list + i);
            valor = chrom->evaluation;
            if ((valor < (*(list + j))->evaluation)) {
                *(list + i) = *(list + j);
                *(list + j) = chrom;
            }
        }
    }
}

/**
 * Mutate a chromosome with a binary encoding.
 * @param chrom Chromosome.
 * @param chrom_length Number of gens in a chromosome.
 * @param mutation_type One of the define types.
 * BIT_STRING_MUTATION: flips a bit at random position.
 * FLIP_BITS: inverts the bits of the genoma.
 * @see http://en.wikipedia.org/wiki/Mutation_%28genetic_algorithm%29
 */
void mutate(Ptr_Chromosome chrom, const int chrom_length, const int mutation_type) {
#ifdef TRACE
    printf("---> mutate. type: ");
    if (mutation_type == BIT_STRING_MUTATION) {
        printf("BIT_STRING_MUTATION");
    }
    else {
        printf("FLIP_BITS");
    }
    printf("\n");
    fflush(stdout);
#endif
    int i = 0,
        position = 0,
        * genAux = (int*)malloc(sizeof(int) * chrom_length);

    switch (mutation_type) {
    case BIT_STRING_MUTATION:
        position = (int)(rand() % chrom_length);
        if (chrom->gens[position] == 0) {
            chrom->gens[position] = 1;
        }
        else {
            chrom->gens[position] = 0;
        }

        break;
    case FLIP_BITS:
        for (i = 0; i < chrom_length; i++) {
            genAux[i] = chrom->gens[i] == 0 ? 1 : 0;
        }
        free(chrom->gens);
        chrom->gens = genAux;

        break;
    }
    // TODO: Add more mutation types.
}

/**
 * Crossover function.
 * Performs the crossover operation between two chromosomes. The result are two new chromosomes
 * @param a First parent chromosome
 * @param b Second parent chromosome
 * @param c1 (Output) First child chromosome.
 * @param c2 (Output) Second child chromosome.
 * @param chrom_length Number of gens in a chromosome.
 * @param cross_type Possible values: ONE_POINT_CROSS, TWO_POINT_CROSS etc...
 * Here implemented only ONE_POINT_CROSS cutting in the middle of each parent.
 * @see http://en.wikipedia.org/wiki/Crossover_%28genetic_algorithm%29
 */
void crossover(Ptr_Chromosome a, Ptr_Chromosome b, ChromosomeList c1, ChromosomeList c2, const int chrom_length, int cross_type) {
#ifdef TRACE
    printf("---> crossover\n");
    fflush(stdout);
#endif

    int i = 0,
        j = 0;

    // Create new chromosomes and allocate memory
    *c1 = (Ptr_Chromosome)malloc(sizeof(struct Chromosome));
    *c2 = (Ptr_Chromosome)malloc(sizeof(struct Chromosome));
    (*c1)->gens = (int*)malloc(chrom_length * sizeof(int));
    (*c2)->gens = (int*)malloc(chrom_length * sizeof(int));

    (*c1)->evaluation = BAD_CHROM;
    (*c2)->evaluation = BAD_CHROM;

    int middle_point = chrom_length / 2;

    switch (cross_type) {

    case ONE_POINT_CROSS: // Basic crossover in the middle

        for (i = 0; i < middle_point; i++) {
            (*c1)->gens[i] = a->gens[i];
            (*c2)->gens[i] = b->gens[i];
        }

        for (i = middle_point; i < chrom_length; i++) {
            (*c1)->gens[i] = b->gens[i];
            (*c2)->gens[i] = a->gens[i];
        }

        break;
    }

    // TODO: Add more crossover variations.

}

/**
 * Prints a chromosome in screen
 * @param chrom Chromosome
 * @chrom_length Number of gens in chromosome.
 */
void show_chromosome(Ptr_Chromosome chrom, const int chrom_length) {
    printf("Chromosome: %6d | Fitness: %f\n", chrom->id, chrom->evaluation);
#ifdef DEBUG
    int i = 0;
    printf("gens: ");
    for (i = 0; i < chrom_length; i++) {
        printf("%d ", chrom->gens[i]);
    }
    printf("\n");
#endif
}

/**
 * Main method of genetic algorithm.
 * @param config Struct with configuration parameters like population size, number of gens, etc...
 * @see struct Chromosome_configuration
 */
int genetic_main(Ptr_config config) {
#ifdef TRACE
    printf("---> genetic_main.\n");
    fflush(stdout);
#endif

    const int TOTAL_CHROM = config->total_chrom;
    const int MAX_ITER = config->max_iter;
    const int MAX_ITER_BEST = config->max_iter_best;
    const int CHROMOSOME_LENGTH = config->chrom_length;

    int rep_best, fin, ale1, ale2, eti1, eti2, iter, i, valid_chromosomes, np;
    double best;
    ChromosomeList chromosome_list; // Array of chromosomes. Population.

    rep_best = 10;
    fin = 0;
    ale1 = 0;
    ale2 = 0;
    eti1 = 0;
    eti2 = 0;

    iter = 0;
    i = 0;
    valid_chromosomes = 0; /**< Percentage of valid chromosomes */

    // Time measurement variables
    struct timeval* tv;
    struct timezone* tz;
    long tf, ti, si, sf;
    double tiempo, mut;

    tv = (struct timeval*)malloc(sizeof(struct timeval));
    tz = NULL;

    gettimeofday(tv, tz);
    si = (tv->tv_sec);
    ti = (tv->tv_usec);
    ti = si * 1000000 + ti;

    srand(time(NULL));

    /*
     * ##########################################
     * ###### GENERATE INITIAL POPULATION #######
     * ##########################################
     */

    chromosome_list = (ChromosomeList)malloc(TOTAL_CHROM * sizeof(Ptr_Chromosome));

    // Candidate for being parallelized.
    for (i = 0; i < TOTAL_CHROM; i++) {
        chromosome_list[i] = create_chromosome(i, CHROMOSOME_LENGTH);
        seed_with_random_values(chromosome_list[i], CHROMOSOME_LENGTH);
    }

    rep_best = 0;
    best = -1.0;

    // ######### MAIN LOOP ##########
    while (fin == 0) {

        /*
         * ###########################################
         * ###### EVALUATION AND CLASSIFICATION ######
         * ###########################################
         */

         // Candidate for being parallelized
        for (i = 0; i < TOTAL_CHROM; i++) {
            if (((chromosome_list[i])->evaluation == BAD_CHROM) && (good_chromosome(chromosome_list[i], CHROMOSOME_LENGTH) == 1)) {
                chromosome_list[i]->evaluation = evaluate_chromosome(chromosome_list[i], CHROMOSOME_LENGTH);
            };
        };
        classify_chromosomes(chromosome_list, TOTAL_CHROM);
        best = chromosome_list[0]->evaluation;

        /*
         * #####################################
         * ###### CHROMOSOME REPRODUCTION ######
         * #####################################
         */
#ifdef TRACE
        printf("Reproduccion de los cromosomas\n");
        fflush(stdout);
#endif

        // Candidate for being parallelized
        for (i = TOTAL_CHROM / 2; i < TOTAL_CHROM - 1; i = i + 2) {
            // Drop the worst half part of the population
            eti1 = chromosome_list[i]->id;
            eti2 = chromosome_list[i + 1]->id;
            ale1 = (int)(rand() % (TOTAL_CHROM / 2));
            ale2 = (int)(rand() % (TOTAL_CHROM / 2));

            free_chromosome(chromosome_list[i]);
            free_chromosome(chromosome_list[i + 1]);
            chromosome_list[i] = NULL;
            chromosome_list[i + 1] = NULL;

            crossover(chromosome_list[ale1], chromosome_list[ale2], &chromosome_list[i], &chromosome_list[i + 1], CHROMOSOME_LENGTH, ONE_POINT_CROSS);
            chromosome_list[i]->id = eti1;
            chromosome_list[i + 1]->id = eti2;
        }

        /*
         * ####################################
         * #######       MUTATION      ########
         * ####################################
         */
        mut = (double)(rand() % (100));
        if (mut < 10) // el 10% de que haya mutacion
        {
            ale1 = (int)(rand() % (TOTAL_CHROM / 2));
            mutate(chromosome_list[ale1], CHROMOSOME_LENGTH, BIT_STRING_MUTATION);
        };

        iter++;

        // CHECK END CONDITIONS
        if ((best == (chromosome_list[0])->evaluation) && (best != BAD_CHROM))
            rep_best++;
        else {
            rep_best = 0;
            best = (chromosome_list[0])->evaluation;
        };

        if ((rep_best == MAX_ITER_BEST) || (iter == MAX_ITER))
            fin = 1;

        /*
         * #####################################################################
         * ###### EVALUATION AND CLASSIFICATION AFTER CROSS AND MUTATION. ######
         * #####################################################################
         */

         // Candidate for being parallelized
        for (i = 0; i < TOTAL_CHROM; i++) {
            if (((chromosome_list[i])->evaluation == BAD_CHROM) && (good_chromosome(chromosome_list[i], CHROMOSOME_LENGTH) == 1)) {
                chromosome_list[i]->evaluation = evaluate_chromosome(chromosome_list[i], CHROMOSOME_LENGTH);
            };
        };
        classify_chromosomes(chromosome_list, TOTAL_CHROM);

        printf("%d ITERATION. 3 BEST CHROMOSOMES:\n", iter);
        for (i = 0; i < 3; i++) {
            show_chromosome(chromosome_list[i], CHROMOSOME_LENGTH);
        }

    }; // ########### END OF MAIN LOOP ###########

    // TIME MEASUREMENT
    gettimeofday(tv, tz);
    sf = (tv->tv_sec);
    tf = (tv->tv_usec);
    tf = sf * 1000000 + tf;
    tiempo = (1.0 * tf - 1.0 * ti) / 1000000.0;
    printf("\nExecution time T=%lf s.\n", tiempo);
    fflush(stdout);

    // CALCULATE PERCENTAGE OF VALID CHROMOSOMES.
    for (i = 0; i < TOTAL_CHROM; i++)
        if (chromosome_list[i]->evaluation != BAD_CHROM)
            valid_chromosomes++;
    printf("%d%% of valid chromosomes.\n", (valid_chromosomes * 100) / TOTAL_CHROM);

    // Free memory
    for (i = 3; i < TOTAL_CHROM; i++)
        free_chromosome(chromosome_list[i]);
    chromosome_list = realloc(chromosome_list, 3 * sizeof(struct Chromosome));

    // TODO: free all mem or return best chromosomes list.

    return EXIT_SUCCESS;
}
