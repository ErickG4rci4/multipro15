#include <stdio.h>

#include <omp.h>

static long num_paso = 10000000; 
double paso;

void thra(int NUM_THREADS){
	int i, nthrads; double pi, sum[NUM_THREADS];
	paso = 1.0/num_paso; 
	omp_set_num_threads(NUM_THREADS);
	const double start = omp_get_wtime();
	#pragma omp parallel
	{
		int i, id, nthrds; 
		double x;
		id = omp_get_thread_num(); 
		nthrds = omp_get_num_threads();
		if (id == 0)
		{
			nthrads = nthrds;
		}
		for (i = id, sum[id] = 0.0; i < num_paso;i=i+nthrds)
		{
			x = (i+0.5)*paso+1;
			sum[id]+=(1/x);
		}
	}
	for (i=0,pi=0.0;i<nthrads;i++) {
		pi+=sum[i]*paso;
	}
	const double end = omp_get_wtime();
	//printf("Area = (%lf)\n", pi);
	printf("%lf\n", (end - start));
	
}

void main(int argc, char const *argv[])
{



	for (int i = 0; i <= 10; ++i){
		thra(50);
	}

	/*
	for (int i = 100; i <= 200; i+=10){
		thra(i);
	}


	for (int i = 200; i <= 1000; i+=100){
		thra(i);
	}
	*/
}