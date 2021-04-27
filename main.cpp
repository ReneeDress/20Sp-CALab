#include <omp.h>
#include <stdio.h>
#include <iostream>
using namespace std;

void helloworld() {
	int nthreads, tid;
	#pragma omp parallel private(nthreads, tid)
	{
		tid=omp_get_thread_num();
		printf("Hello World from OMP thread %d\n", tid);
		if (tid==0)
		{
			nthreads=omp_get_num_threads();
			printf("Number of threads is %d\n", nthreads);
		}
	}
}

void hellomp() {
    int nthreads, tid;
    omp_set_num_threads(8);
    #pragma omp parallel private(nthreads, tid)
    {
        tid=omp_get_thread_num();
        printf("Hello World from OMP thread %d\n", tid);
        if (tid==0)
        {
            nthreads=omp_get_num_threads();
            printf("Number of threads is %d\n", nthreads);
        }
    }
}

//int main() {
//    cout << "helloworld" << endl;
//    helloworld();
//    cout << "hellomp" << endl;
//    hellomp();
//}
