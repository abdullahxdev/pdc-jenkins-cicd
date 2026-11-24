# PDC Lab Assignment 3: Jenkins CI/CD on AWS EC2

Muhammad Abdullah, FA23-BCS-109, CSC334 Parallel and Distributed Computing

Every push to this repository sends a GitHub webhook to Jenkins running on an AWS EC2
instance. Jenkins then runs the pipeline in `Jenkinsfile`:

1. **Checkout**: pulls the pushed commit.
2. **Build**: compiles `parallel_sum.c` with `gcc -fopenmp`.
3. **Test**: runs the program in test mode; it fails the build if the OpenMP sum differs from the serial sum.
4. **Run**: runs the parallel sum with 1, 2 and 4 threads and prints time and speedup.

The program sums 20 million integers with an OpenMP `reduction(+:sum)`.
