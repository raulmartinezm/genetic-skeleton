Genetic Algorithm Skeleton
===========================

Simple genetic algorithm skeleton in C language. Used as scaffolding for my bachelor final project.


Encoding
--------

- Binary encoding

TODO:
- Permutation
- Value encoding
- Tree encoding

Crossover
---------

- One-point crossover.

TODO:

- Two-point crossover.
- Uniform crossover.

Future Implementations
======================

- OpenMP support.


Example code
============

In directory *examples/binary_encoding* it's include an implmentation example of a genetic algorithm applied to the `Knapsack problem`.

Description of Knapsack problem
-------------------------------

There are a collection of things with a given size and value and a knapsack with a limited capcity. `Maximize` the total value of things in knapsack.
Each bit says if the corresponding thing is in knapsack.

Sources
-------

http://en.wikipedia.org/wiki/Genetic_algorithm
http://en.wikipedia.org/wiki/Knapsack_problem
http://www.obitko.com/tutorials/genetic-algorithms/encoding.php
