# Genetic Algorithm Skeleton


Simple [genetic algorithm](https://en.wikipedia.org/wiki/Genetic_algorithm) skeleton in C language. Used as scaffolding for my bachelor final project.

Genetic algorithm is a class of evolutionary algorthim inspired by natural selection processes, such as inheritance, mutation, selection and crossover.

Steps:

```
1. Generate a population randomly.
2. Repeat until **termination condition** has been reached:
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
- Uniform crossover
- Arithmetic crossover.
- Two-point crossover.


## Mutation

- Uniform Mutation.
- Non-uniform mutation.
- Exchange.

## Tests

I've introduced [MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html), a minimal unit testing for C. I like a lot its simplicity and efectivity.

		$ make test

### Links

- https://en.wikipedia.org/wiki/Genetic_algorithm
- http://www.jera.com/techinfo/jtns/jtn002.html


Example code
============

In directory *examples/binary_encoding* it's include an implmentation example of a genetic algorithm applied to the `Knapsack problem`.

Description of Knapsack problem
-------------------------------

There are a collection of things with a given size and value and a knapsack with a limited capcity. `Maximize` the total value of things in knapsack.
Each bit says if the corresponding thing is in knapsack.
