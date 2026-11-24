/* PDC Lab Assignment 3: OpenMP program built and run by the Jenkins pipeline
   Muhammad Abdullah, FA23-BCS-109
   Sums an array in parallel with an OpenMP reduction, checks it against a
   serial sum, and reports the time and speedup for 1, 2 and 4 threads. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define N 20000000L

static long long parallel_sum(const int *a, long n, int threads) {
    long long sum = 0;
    #pragma omp parallel for num_threads(threads) reduction(+:sum) schedule(static)
    for (long i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

int main(int argc, char **argv) {
    int ROLL_NO = 109;
    int REG_SEED = ROLL_NO * 17 + 103;
    int test_mode = (argc > 1 && strcmp(argv[1], "--test") == 0);

    int *a = malloc(N * sizeof(int));
    if (!a) { fprintf(stderr, "out of memory\n"); return 1; }
    for (long i = 0; i < N; i++)
        a[i] = (int)((i * REG_SEED) % 100);

    long long serial = 0;
    for (long i = 0; i < N; i++) serial += a[i];

    if (test_mode) {
        int ok = 1;
        int counts[] = {1, 2, 4};
        for (int k = 0; k < 3; k++) {
            long long p = parallel_sum(a, N, counts[k]);
            printf("TEST threads=%d parallel=%lld serial=%lld %s\n",
                   counts[k], p, serial, p == serial ? "PASS" : "FAIL");
            if (p != serial) ok = 0;
        }
        free(a);
        printf(ok ? "ALL TESTS PASSED\n" : "TESTS FAILED\n");
        return ok ? 0 : 1;
    }

    printf("Muhammad Abdullah (FA23-BCS-109), REG_SEED = %d, N = %ld\n", REG_SEED, N);
    printf("Machine has %d processors available to OpenMP\n", omp_get_num_procs());
    double t1 = 0;
    int counts[] = {1, 2, 4};
    for (int k = 0; k < 3; k++) {
        double start = omp_get_wtime();
        long long p = parallel_sum(a, N, counts[k]);
        double t = omp_get_wtime() - start;
        if (k == 0) t1 = t;
        printf("threads=%d  sum=%lld  time=%.4f s  speedup=%.2fx  %s\n",
               counts[k], p, t, t1 / t, p == serial ? "MATCH" : "MISMATCH");
    }
    free(a);
    return 0;
}
