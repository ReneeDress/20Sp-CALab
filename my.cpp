//
// Created by Yijun Lin on 2021/4/20.
//
#include <stdio.h>
#include <omp.h>
#include <time.h>

void derivative(double x, double y, double res) {
    res = ((x + y) * (x + y) - x * x) / y;
}

int main() {
    int times = 10000000000;
    double duration;
    clock_t s, f, p;
    double x = 2;
    double y = 0.01;
    double res;
    int n = 0;
    int k = 0;

    int nthreads, tid;

    s = clock();
    for (n = 0; n < times; n++) derivative(x, y, res);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Serial Line: %f\n", duration);
    printf("%f\n", res);


    // parallel 1
    s = clock();
    #pragma omp parallel for
    for (n = 0; n < times / 1; n++) {
        derivative(x, y, res);
    }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  1: %f\n", duration);
    printf("%f\n", res);

    // parallel 2
    s = clock();
    #pragma omp parallel for
    for (int m = 0; m < 2; m++)
        for (n = 0; n < times / 2; n++) {
            derivative(x, y, res);
        }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  2: %f\n", duration);
    printf("%f\n", res);

    // parallel 3
    s = clock();
    #pragma omp parallel for
    for (int m = 0; m < 3; m++)
        for (n = 0; n < times / 3; n++) {
            derivative(x, y, res);
        }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  3: %f\n", duration);
    printf("%f\n", res);

    // parallel 4
    s = clock();
    #pragma omp parallel for
    for (int m = 0; m < 4; m++)
        for (n = 0; n < times / 4; n++) {
            derivative(x, y, res);
        }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  4: %f\n", duration);
    printf("%f\n", res);

    // parallel 8
    s = clock();
    #pragma omp parallel for
    for (int m = 0; m < 8; m++)
        for (n = 0; n < times / 8; n++) {
            derivative(x, y, res);
        }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  8: %f\n", duration);
    printf("%f\n", res);

    // parallel 16
    s = clock();
    #pragma omp parallel
    for (int m = 0; m < 16; m++)
        for (n = 0; n < times / 16; n++) {
            derivative(x, y, res);
        }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel 16: %f\n", duration);
    printf("%f\n", res);

    return 0;
}