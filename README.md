# Genetic Algorithm Skeleton

Simple [genetic algorithm](https://en.wikipedia.org/wiki/Genetic_algorithm) skeleton in C language. Used as scaffolding for my bachelor final project.

Genetic algorithm is a class of evolutionary algorithm inspired by natural selection processes, such as inheritance, mutation, selection and crossover.

The algorithm produces candidate solutions (probably not the best) to a problem. It can be applied to local search problems like decision trees, hyperparameter optimization, puzzle solving, etc.

The basic workflow if the algorithm is:

```
1. Generate a population randomly.
2. Repeat until a **termination condition** has been reached:
	2.1 Evaluate population
	2.2 Crossover population
	2.3 Mutate population
	2.4 Select individuals that survive to the next iteration.
```

## Input values

- Population size.
- Number of iterations.
- Crossover probability.
- Mutation probability.
- Elitism

## Encoding

- Binary encoding

TODO:

- Permutation
- Value encoding
- Tree encoding

## Crossover

- One-point crossover.

TODO:
- Uniform crossover
- Arithmetic crossover.
- Two-point crossover.


## Mutation

- Bit string mutation.
- Bit flip mutation.

## Tests

I've introduced [MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html), a minimal unit testing for C. I like a lot its simplicity and effectivity.

		$ make test

### Links

- [Genetic algorithms page from Wikipedia.](https://en.wikipedia.org/wiki/Genetic_algorithm)
- [MinUnit testing framework.](http://www.jera.com/techinfo/jtns/jtn002.html)


### Application examples

Some applications of the algorithm are available in [examples](examples/).
