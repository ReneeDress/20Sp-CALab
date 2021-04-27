//
// Created by Yijun Lin on 2021/4/20.
//
#include <stdio.h>
#include <omp.h>
#include <time.h>

void comput(float* A, float* B, float* C) { // 两个矩阵相乘传统方法
    int x, y;
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            C[4*y+x] = A[4*y+0] * B[4*0+x] + A[4*y+1] * B[4*1+x] + A[4*y+2] * B[4*2+x] + A[4*y+3] * B[4*3+x];
        }
    }
}

int main() {
    int times = 10000000;
    double duration;
    clock_t s, f, p;
    int x = 0;
    int y = 0;
    int n = 0;
    int k = 0;
    float A[] = {
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16
    };
    float B[] = {
            0.1f,0.2f,0.3f,0.4f,
            0.5f,0.6f,0.7f,0.8f,
            0.9f,0.10f,0.11f,0.12f,
            0.13f,0.14f,0.15f,0.16f
    };
    float C[16];

    int nthreads, tid;

    s = clock();
    #pragma omp parallel if(false)
        for (n = 0; n < times; n++) comput(A, B, C);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Serial Line: %f\n", duration);
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++)
            printf("%f,\t", C[y*4+x]);
        printf("\n");
    }


    // parallel 1
    omp_set_num_threads(1);
    s = clock();
    #pragma omp parallel for firstprivate(nthreads, tid)
        for (n = 0; n < times / 1; n++) comput(A, B, C);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  1: %f\n", duration);

    // parallel 2
    omp_set_num_threads(2);
    s = clock();
    #pragma omp parallel for firstprivate(nthreads, tid)
        for (n = 0; n < times / 2; n++) comput(A, B, C);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  2: %f\n", duration);

    // parallel 3
    omp_set_num_threads(3);
    s = clock();
        for (n = 0; n < times / 3; n++) comput(A, B, C);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  3: %f\n", duration);

    // parallel 4
    omp_set_num_threads(4);
    s = clock();
    #pragma omp parallel for firstprivate(nthreads, tid)
        for (n = 0; n < times / 4; n++) comput(A, B, C);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  4: %f\n", duration);

    // parallel 8
    omp_set_num_threads(8);
    s = clock();
    #pragma omp parallel for firstprivate(nthreads, tid)
        for (n = 0; n < times / 8; n++) comput(A, B, C);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  8: %f\n", duration);

    // parallel 16
    omp_set_num_threads(16);
    s = clock();
    #pragma omp parallel for firstprivate(nthreads, tid)
        for (n = 0; n < times / 16; n++) comput(A, B, C);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    
    printf("Parallel 16: %f\n", duration);


    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++)
            printf("%f,\t", C[y*4+x]);
        printf("\n");
    }

    return 0;
}