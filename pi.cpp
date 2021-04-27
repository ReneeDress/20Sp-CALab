//
// Created by Yijun Lin on 2021/4/20.
//
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <cstdlib>

void CaculatePi(int len, int carry, int i, int result, char* temp, int numberator, int denominator, int flag, char* pi)
{
    carry = 0;
    for(i = len-1; i > 0; i--)     //从低位到高位相乘
    {
        result = temp[i] * numberator+carry; //用每一位去乘，再加上进位
        temp[i] = result % 10;               //保存个数
        carry = result / 10;                 //进位
    }

    carry = 0;
    for(i = 0; i < len; i++)                 //有高位到低位进行除法运算
    {
        result = temp[i] + carry*10;         //当前位加上前一位的余数
        temp[i] = result / denominator;      //当前位的整数部分
        carry = result % denominator;        //当前位的余数，累加到下一位的运算
    }
    flag = 0; //清除标志
    for(i = len-1; i > 0; i--)
    {
        result = pi[i] + temp[i];            //将计算结果累加到result中
        pi[i] = result % 10;                 //保留一位
        pi[i-1] += result / 10;              //向高位进位
        flag |= temp[i];                     //若temp中的数全为0,退出循环
    }
    numberator++;       //累加分子
    denominator += 2;   //累加分母

//    printf("\n计算了%d次\n",count);              //输出循环次数
//    printf("\t--- 第1-1000为小数----\n");
//    printf("PI = \n");
//    printf("%d.",pi[1]);
//    for(i = 2; i < len; i++)
//    {
//        if((i>2) && (i-2)%10 == 0)        //每10位小数间加一个空格
//            printf(" ");
//        if((i>2) && (i-2)%50 == 0)       //每50位小数换行
//            printf("\n");
//
//        printf("%d",(int)pi[i]);         //输出一位小数
//    }
//    printf("\n");

}


int mainpi() {
    int len = 100000;
    double duration;
    clock_t s, f;

    int i;                   //len为小数长度
    int numberator = 1,denominator = 3,result,carry;
    int flag = 1,count = 0;      //继续循环的标志及循环的次数
    char *pi,*temp;              //指向保存pi值和临时计算结果的数据

    len += 2;   //增加两位
    if(!(pi = (char*)malloc(sizeof(char)*len)))   //分配保存pi值的内存
    {
        printf("分配内存失败！\n");
        exit(0);
    }
    if(!(temp = (char*)malloc(sizeof(char)*len))) //分配保存呢临时值的内存
    {
        printf("分配内存失败！\n");
        exit(0);
    }

    for(i = 0; i < len; i++)  //初始化数组
    {
        pi[i] = temp[i] = 0;
    }
    pi[1] = 2;         //置初值
    temp[1] = 2;

    int nthreads, tid;

    s = clock();
    CaculatePi(len, carry, i, result, temp, numberator, denominator, flag, pi);
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Serial Line: %f\n", duration);
//    for (y = 0; y < 4; y++) {
//        for (x = 0; x < 4; x++)
//            printf("%f,\t", C[y*4+x]);
//        printf("\n");
//    }


    // parallel 1
    omp_set_num_threads(1);
    s = clock();
    #pragma omp parallel private(nthreads, tid)
    {
        tid=omp_get_thread_num();
        // printf("Hello World from OMP thread %d\n", tid);
        if (tid==0)
        {
            nthreads=omp_get_num_threads();
            printf("Number of threads is %d\n", nthreads);

        }
        CaculatePi(len, carry, i, result, temp, numberator, denominator, flag, pi);
    }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  1: %f\n", duration);

    printf("\n计算了%d次\n",count);              //输出循环次数
    printf("\t--- 第1-1000为小数----\n");
    printf("PI = \n");
    printf("%d.",pi[1]);
    for(i = 2; i < len; i++)
    {
        if((i>2) && (i-2)%10 == 0)        //每10位小数间加一个空格
            printf(" ");
        if((i>2) && (i-2)%50 == 0)       //每50位小数换行
            printf("\n");

        printf("%d",(int)pi[i]);         //输出一位小数
    }
    printf("\n");

    // parallel 2
    omp_set_num_threads(2);
    s = clock();
    #pragma omp parallel private(nthreads, tid)
    {
        tid=omp_get_thread_num();
        // printf("Hello World from OMP thread %d\n", tid);
        if (tid==0)
        {
            nthreads=omp_get_num_threads();
            printf("Number of threads is %d\n", nthreads);

        }
        CaculatePi(len, carry, i, result, temp, numberator, denominator, flag, pi);
    }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  2: %f\n", duration);

    // parallel 3
    omp_set_num_threads(3);
    s = clock();
    #pragma omp parallel private(nthreads, tid)
    {
        tid=omp_get_thread_num();
        // printf("Hello World from OMP thread %d\n", tid);
        if (tid==0)
        {
            nthreads=omp_get_num_threads();
            printf("Number of threads is %d\n", nthreads);

        }
        CaculatePi(len, carry, i, result, temp, numberator, denominator, flag, pi);
    }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  3: %f\n", duration);

    // parallel 4
    omp_set_num_threads(4);
    s = clock();
    #pragma omp parallel private(nthreads, tid)
    {
        tid=omp_get_thread_num();
        // printf("Hello World from OMP thread %d\n", tid);
        if (tid==0)
        {
            nthreads=omp_get_num_threads();
            printf("Number of threads is %d\n", nthreads);

        }
        CaculatePi(len, carry, i, result, temp, numberator, denominator, flag, pi);
    }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  4: %f\n", duration);

    // parallel 8
    omp_set_num_threads(8);
    s = clock();
    #pragma omp parallel private(nthreads, tid)
    {
        tid=omp_get_thread_num();
        // printf("Hello World from OMP thread %d\n", tid);
        if (tid==0)
        {
            nthreads=omp_get_num_threads();
            printf("Number of threads is %d\n", nthreads);

        }
        CaculatePi(len, carry, i, result, temp, numberator, denominator, flag, pi);
    }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    printf("Parallel  8: %f\n", duration);

    // parallel 16
    omp_set_num_threads(16);
    s = clock();
    #pragma omp parallel private(nthreads, tid)
    {
        tid=omp_get_thread_num();
        // printf("Hello World from OMP thread %d\n", tid);
        if (tid==0)
        {
            nthreads=omp_get_num_threads();
            printf("Number of threads is %d\n", nthreads);

        }
        CaculatePi(len, carry, i, result, temp, numberator, denominator, flag, pi);
    }
    f = clock();
    duration = (double)(f - s) / CLOCKS_PER_SEC;
    
    printf("Parallel 16: %f\n", duration);

    printf("\n计算了%d次\n",count);              //输出循环次数
    printf("\t--- 第1-1000为小数----\n");
    printf("PI = \n");
    printf("%d.",pi[1]);
    for(i = 2; i < len; i++)
    {
        if((i>2) && (i-2)%10 == 0)        //每10位小数间加一个空格
            printf(" ");
        if((i>2) && (i-2)%50 == 0)       //每50位小数换行
            printf("\n");

        printf("%d",(int)pi[i]);         //输出一位小数
    }
    printf("\n");


//    for (y = 0; y < 4; y++) {
//        for (x = 0; x < 4; x++)
//            printf("%f,\t", C[y*4+x]);
//        printf("\n");
//    }

    return 0;
}