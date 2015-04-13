/** @file genetic.c
 *  @brief Partial implementation ofgenetic algorithm.
 */

#include "genetic.h"

/**
 * Creates a new chromosome with a binary encoding.
 * @param id Label for the chromosome.
 * @return new Chromosome.
 */
Ptr_Chromosome create_chromosome(int id, const int chrom_length)
{
#ifdef TRACE
    printf("\n---> create_chromosome. Chromosome: %d", id);
    fflush(stdout);
#endif

    int  i = 0;
    Ptr_Chromosome chrom = NULL;

    // Random seed initialization from current system time.
    srand(time(NULL));

    // Memory allocation
    chrom = (Ptr_Chromosome)malloc(sizeof(struct Chromosome));
    chrom->gens = (int*)malloc(chrom_length * sizeof(int));

    chrom->id = id;
    chrom->evaluation = BAD_CHROM;
    // Initialize chromosome with random values
    for ( i = 0 ; i < chrom_length ; i++ ) {
        chrom->gens[i] = rand() % 2;
    }

    return chrom;
}

/**
 * Free memory allocated for chromosome.
 * @param chrom Cromosoma.
 */
void free_chromosome( Ptr_Chromosome chrom ) {

    int *gens;
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
 * Short the chromosomes list by fitness.
 * @param list Chromosomes' list.
 * @param total Total number of chromosomes.
 */
void classify_chromosome(Ptr_Chromosome * list, const int total) {
#ifdef TRACE
    printf("\n---> funcion classify_chromosome");
    fflush(stdout);
#endif
    int i, j;
    Ptr_Chromosome chrom;
    double valor;

// #pragma omp parallel for private (i,j) schedule (static) //SEGMENTATION FAULT
    for ( i = 0 ; i < total ; i++ )
    {
        for ( j = i + 1 ; j < total ; j++ )
        {
            chrom = *(list + i);
            valor = chrom->evaluation;
            if ( ( valor < (*(list + j))->evaluation  ) )
            {
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
 * @param mutation_type One of the define types. BIT_STRING_MUTATION: flips a bit at random position. FLIP_BITS: inverts the bits of the genoma.
 * @see http://en.wikipedia.org/wiki/Mutation_%28genetic_algorithm%29
 */
void mutate (Ptr_Chromosome chrom, const int chrom_length, const int mutation_type)
{
#ifdef TRACE
    printf("\n---> mutate. type: ");
    if (mutation_type == BIT_STRING_MUTATION) {
        printf("BIT_STRING_MUTATION");
    } else {
        printf("FLIP_BITS");
    }
    fflush(stdout);
#endif
    int i = 0,
        position = 0,
        *genAux = (int*)malloc(sizeof(int) * chrom_length);

    switch (mutation_type) {
    case BIT_STRING_MUTATION:
        position  = (int)(rand() % chrom_length);
        if ( chrom->gens[position] == 0 ) {
            chrom->gens[position] = 1;
        } else {
            chrom->gens[position] = 0;
        }

        break;
    case FLIP_BITS:
        for ( i = 0 ; i < chrom_length ; i++ ) {
            genAux[i] = chrom->gens[i] == 0 ? 1 : 0;
        }
        free(chrom->gens);
        chrom->gens = genAux;

        break;
    }
    // MORE MUTATION TYPES...

}

/**
 * Crossover function.
 * Performs the crossover operation between two chromosomes. The result are two new chromosomes
 * @param a First parent chromosome
 * @param b Second parent chromosome
 * @param *c1 (Output) First child chromosome.
 * @param *c2 (Output) Second child chromosome.
 * @param chrom_length Number of gens in a chromosome.
 * @param cross_type Possible values: ONE_POINT_CROSS, TWO_POINT_CROSS etc... Here implemented only ONE_POINT_CROSS cutting in the middle of each parent.
 * @see http://en.wikipedia.org/wiki/Crossover_%28genetic_algorithm%29
 */
void crossover(Ptr_Chromosome a, Ptr_Chromosome b, Ptr_Chromosome *c1, Ptr_Chromosome *c2, const int chrom_length, int cross_type)
{
#ifdef TRACE
    printf("\n---> crossover");
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


    switch (cross_type) {

    case ONE_POINT_CROSS:
        // Basic crossover in the middle
        for (i = 0 , j = chrom_length / 2 ; i < chrom_length / 2 , j < chrom_length ; i++, j++ )
        {
            (*c1)->gens[i] = a->gens[i];
            (*c2)->gens[i] = b->gens[i];
            (*c1)->gens[j] = b->gens[j];
            (*c2)->gens[j] = a->gens[j];
        }


        break;
    }

} // END crossover

int genetic_main(Ptr_config config)
{
#ifdef TRACE
    printf("\n---> genetico. col %d", col);
    fflush(stdout);
#endif
    const int TOTAL_CHROM = config->total_chrom;
    const int MAX_ITER = config->max_iter;
    const int MAX_REP_MEJOR = config->max_iter_best;
    const int CHROMOSOME_LENGTH = config->chrom_length;

    int rep_mejor, fin,  ale1, ale2, eti1, eti2, iter, i, validos, np;
    double mejor;
    Ptr_Chromosome *List_Chromosome;

    rep_mejor = 10;
    fin = 0;
    ale1 = 0;
    ale2 = 0;
    eti1 = 0;
    eti2 = 0;

    iter = 0;
    i = 0;
    validos = 0; // para calcular el porcentaje de validos.

    // Estructuras para medir el tiempo de ejecucion.
    struct timeval *tv;
    struct timezone *tz;
    long tf, ti, si, sf;
    double tiempo, mut;

    tv = (struct timeval *)malloc(sizeof(struct timeval));
    tz = NULL;

    gettimeofday(tv, tz);
    si = (tv->tv_sec);
    ti = (tv->tv_usec);
    ti = si * 1000000 + ti;

    srand (time (NULL));

    /*
     * #########################################
     * ###### GENERAR PROBLACION INICIAL #######
     * #########################################
     */
    //Reservar memoria para todos los cromosomas
    List_Chromosome = (Ptr_Chromosome*)malloc(TOTAL_CHROM * sizeof(Ptr_Chromosome));

#ifdef PARALELO
    #pragma omp parallel for private (i) schedule (static)
#endif
    for ( i = 0 ; i < TOTAL_CHROM ; i++ ) // Genera cromosomas.
    {
        List_Chromosome[i] = create_chromosome(i);
    }

    rep_mejor = 0;
    mejor = -1.0; //se le da un valor que no tiene ninguno para que no coincida

#ifndef PARCIAL
//Si esta definida la constante no ejecuta el algoritmo entero, solo generar poblacion inicial.
    while ( fin == 0 ) // ######### BUCLE PRINCIPAL ##########
    {

        /*
         * ########################################
         * ###### EVALUACION Y CLASIFICACION ######
         * ########################################
         */

#ifdef PARALELO
        #pragma omp parallel for private (i) schedule (static)
#endif
        for ( i = 0  ; i < TOTAL_CHROM ; i++ )
        {
            if ( ((List_Chromosome[i])->evaluation == BAD_CHROM) && (good_chromosome(List_Chromosome[i]) == 1) )
            {
                List_Chromosome[i]->evaluation = evaluate_chromosome(List_Chromosome[i]);
            };
        };
        classify_chromosome(List_Chromosome, TOTAL_CHROM);
        mejor = List_Chromosome[0]->evaluation;

        /*
         * ############################################
         * ###### REPRODUCCION DE LOS CROMOSOMAS ######
         * ############################################
         */
#ifdef TRACE
        printf("\nReproduccion de los cromosomas");
        fflush(stdout);
#endif

#ifdef PARALELO
        #pragma omp parallel for private (i,ale1,ale2,eti1,eti2) schedule (static)
#endif
        for ( i = TOTAL_CHROM / 2 ; i < TOTAL_CHROM - 1 ; i = i + 2 )
        {
            //vamos a eliminar la mitad y la otra mitad sobrevivira
            eti1 = List_Chromosome[i]->id;
            eti2 = List_Chromosome[i + 1]->id;
            ale1 = (int)(rand() % (TOTAL_CHROM / 2)); //solo se reproducen los primeros. Coge 2 aleatorios entre la primera mitad
            ale2 = (int)(rand() % (TOTAL_CHROM / 2));

            free_chromosome(List_Chromosome[i]);// Borra dos de los ultimos
            free_chromosome(List_Chromosome[i + 1]);
            List_Chromosome[i] = NULL;
            List_Chromosome[i + 1] = NULL;
// MOSTRAMOS LOS 3 MEJORES

            crossover(List_Chromosome[ale1], List_Chromosome[ale2], &List_Chromosome[i], &List_Chromosome[i + 1]);
            List_Chromosome[i]->id = eti1;
            List_Chromosome[i + 1]->id = eti2;
        }
        /*
         * ####################################
         * #######       MUTACION      ########
         * ####################################
        */
        mut = (double)(rand() % (100));
        if ( mut < 10 ) //el 10% de que haya mutacion
        {
            ale1 = (int)(rand() % (TOTAL_CHROM / 2));
            mutate(List_Chromosome[ale1], BIT_STRING_MUTATION);
        };

        iter++;

        //CONDICION DE FIN
        if ((mejor == (List_Chromosome[0])->evaluation) && (mejor != BAD_CHROM))
            rep_mejor++;
        else
        {
            rep_mejor = 0;
            mejor = (List_Chromosome[0])->evaluation;
        };

        if ( (rep_mejor == MAX_REP_MEJOR) || (iter == MAX_ITER)   )
            fin = 1;

        /*
         * #####################################################################
         * ###### EVALUACION Y CLASIFICACION DESPUES DE CRUCE Y MUTACION. ######
         * #####################################################################
         */

#ifdef PARALELO
        #pragma omp parallel for private(i) schedule(static)
#endif
        for ( i = 0  ; i < TOTAL_CHROM ; i++ )
        {
            if ( ((List_Chromosome[i])->evaluation == BAD_CHROM) && (good_chromosome(List_Chromosome[i]) == 1) )
            {
                List_Chromosome[i]->evaluation = evaluate_chromosome(List_Chromosome[i]);
            };
        };
        classify_chromosome(List_Chromosome, TOTAL_CHROM);
// MOSTRAMOS LOS 3 MEJORES

//        printf("\n===================== ITERACION %d. 3 MEJORES CROMOSOMAS: =====================",iter);
//        for ( i=0 ; i<3 ; i++)
//        {
//            show_chromosome(List_Chromosome[i]);
//            show_constraints(List_Chromosome[i],X,Y,col);
//        }

    };// ########### FIN BUCLE PRINCIPAL ###########
#endif // Fin de condicion para ejecutar el algoritmo completo

    gettimeofday(tv, tz);
    sf = (tv->tv_sec);
    tf = (tv->tv_usec);
    tf = sf * 1000000 + tf;
    tiempo = (1.0 * tf - 1.0 * ti) / 1000000.0;
    printf("\n----------------Tiempo llamada T=%lf", tiempo);
    fflush(stdout);

    // CALCULAR CROMOSMAS VALIDOS
    for ( i = 0 ; i < TOTAL_CHROM ; i++ )
        if ( List_Chromosome[i]->evaluation != BAD_CHROM )
            validos++;
    printf("\nCromosomas validos: %d%%", (validos * 100) / TOTAL_CHROM);

    // Liberar memoria
    for ( i = 3 ; i < TOTAL_CHROM ; i++ )
        free_chromosome(List_Chromosome[i]);
    List_Chromosome = realloc(List_Chromosome, 3 * sizeof(struct Chromosome));
    /*

        information->list_size = 3;
        information->list = List_Chromosome;
        information->time = tiempo;
        information->column = col;
        information->valids_ratio = (validos * 100) / TOTAL_CHROM;
        information->population = TOTAL_CHROM;
        // Devuelve los 3 mejores resultados.
        return information;
    */
}
