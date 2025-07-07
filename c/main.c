#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 500000
#define T 1.0
#define DT (T / (double)N)
#define THETA 1.0
#define MU 1.0
#define SIGMA 1.0
#define NUM_RUNS 1000

double rand_uniform() {
    return ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
}

long run_once() {
    double *gn = malloc((N - 1) * sizeof(double));
    double *ou = malloc(N * sizeof(double));

    if (gn == NULL || ou == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    srand((unsigned int)time(NULL));

    const double dt_sqrt = sqrt(DT);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    int i = 0;
    while (i < N - 1) {
        double u1 = rand_uniform();
        double u2 = rand_uniform();
        double r = sqrt(-2.0 * log(u1));
        double theta = 2.0 * M_PI * u2;

        double z0 = r * cos(theta);
        double z1 = r * sin(theta);

        gn[i] = z0 * dt_sqrt;
        if (i + 1 < N - 1) {
            gn[i + 1] = z1 * dt_sqrt;
        }
        i += 2;
    }

    ou[0] = 0.0;
    for (int j = 1; j < N; j++) {
        ou[j] = ou[j - 1] + THETA * (MU - ou[j - 1]) * DT + SIGMA * gn[j - 1];
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    long seconds = end_time.tv_sec - start_time.tv_sec;
    long nanoseconds = end_time.tv_nsec - start_time.tv_nsec;
    long elapsed_ns = seconds * 1e9 + nanoseconds;

    free(gn);
    free(ou);

    return elapsed_ns;
}

int main() {
    long total_ns = 0;

    for (int run = 0; run < NUM_RUNS; run++) {
        total_ns += run_once();
    }

    long avg_ns = total_ns / NUM_RUNS;
    printf("Average elapsed time over %d runs: %ld ns\n", NUM_RUNS, avg_ns);
    printf("Total: %ld ns\n", total_ns);

    return 0;
}
