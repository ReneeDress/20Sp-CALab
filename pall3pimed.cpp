//
// Created by Yijun Lin on 2021/4/21.
//
#include <cstdio>
#include <time.h>
#include <omp.h>

void pipi(double* sumarr, int i, double step) {
    double x = (i + 0.5) * step;
//    sum = sum + 4.0 / (1.0 + x * x);
    sumarr[i] = 4.0 / (1.0 + x * x) * step;
//    printf("%.15lf\n", sumarr[i]);
}

int main() {
    clock_t f, s;
    double duration;
    double pi, step;
    long num_steps = 100000000;
    int n;
    double x;
    double sum = 0;
    double* sumarr = new double[num_steps];

    int nthreads, tid;

    step = 1.0 / (double) num_steps;

    
    pi = 0;
    s = clock();
    for (n = 0; n < num_steps; n++) pipi(sumarr, n, step);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Serial Line: %f\n", duration);

    for (int j = 0; j < num_steps; j++)
        pi += sumarr[j];

    printf("Pi = %.15lf\n", pi);


    // parallel 1
    pi = 0;
    omp_set_num_threads(1);
    s = clock();
    #pragma omp parallel for private(nthreads, tid)
        for (n = 0; n < num_steps / 1; n++) pipi(sumarr, n, step);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  1: %f\n", duration);

    for (int j = 0; j < num_steps; j++)
        pi += sumarr[j];

    printf("Pi = %.15lf\n", pi);


    // parallel 2
    pi = 0;
    omp_set_num_threads(2);
    s = clock();
    #pragma omp parallel for private(nthreads, tid)
        for (n = 0; n < num_steps / 2; n++) pipi(sumarr, n, step);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  2: %f\n", duration);

    for (int j = 0; j < num_steps; j++)
        pi += sumarr[j];

    printf("Pi = %.15lf\n", pi);

    // parallel 3
    pi = 0;
    omp_set_num_threads(3);
    s = clock();
    #pragma omp parallel for private(nthreads, tid)
        for (n = 0; n < num_steps / 3; n++) pipi(sumarr, n, step);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  3: %f\n", duration);

    for (int j = 0; j < num_steps; j++)
        pi += sumarr[j];

    printf("Pi = %.15lf\n", pi);

    // parallel 4
    pi = 0;
    omp_set_num_threads(4);
    s = clock();
    #pragma omp parallel for private(nthreads, tid)
        for (n = 0; n < num_steps / 4; n++) pipi(sumarr, n, step);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  4: %f\n", duration);

    for (int j = 0; j < num_steps; j++)
        pi += sumarr[j];

    printf("Pi = %.15lf\n", pi);

    // parallel 8
    pi = 0;
    omp_set_num_threads(8);
    s = clock();
    #pragma omp parallel for private(nthreads, tid)
        for (n = 0; n < num_steps / 8; n++) pipi(sumarr, n, step);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  8: %f\n", duration);

    for (int j = 0; j < num_steps; j++)
        pi += sumarr[j];

    printf("Pi = %.15lf\n", pi);

    // parallel 16
    pi = 0;
    omp_set_num_threads(16);
    s = clock();
    #pragma omp parallel for private(nthreads, tid)
        for (n = 0; n < num_steps / 16; n++) pipi(sumarr, n, step);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel 16: %f\n", duration);

    for (int j = 0; j < num_steps; j++)
        pi += sumarr[j];

    printf("Pi = %.15lf\n", pi);
    
    return 0;
}
