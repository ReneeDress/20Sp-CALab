//
// Created by Yijun Lin on 2021/4/21.
//
#include <cstdio>

void pipi(double* sumarr, int i, double step) {
    double x = (i + 0.5) * step;
//    sum = sum + 4.0 / (1.0 + x * x);
    sumarr[i] = 4.0 / (1.0 + x * x) * step;
    printf("%.15lf\n", sumarr[i]);
}

int main() {
    double pi, step;
    long num_steps = 100000;
    int i;
    double x;
    double sum = 0;
    double* sumarr = new double[num_steps];

    step = 1.0 / (double) num_steps;
//    for (i = 0; i < num_steps; i++) {
//        x = (i + 0.5) * step;
//        sum = sum + 4.0 / (1.0 + x * x);
//        sumarr[i] = 4.0 / (1.0 + x * x) * step;
//        printf("%.15lf\n", sumarr[i]);
//    }
    for (i = 0; i < num_steps; i++) {
        pipi(sumarr, i, step);
    }

    for (int j = 0; j < num_steps; j++)
        pi += sumarr[j];
//    pi = step * sum;
    printf("Pi = %.15lf\n", pi);
    return 0;
}
