#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>

#define RANDLIMIT	7	/* Magnitude limit of generated randno.*/
#define N		10  	/* Matrix Size */
#define NUMLIMIT 120.0

double matrix_A[N][N];//input matrix 1
double matrix_B[N][N];//input matrix 2
double matrix_C[N][N];//output matrix

int main(int argc, char *argv[])
{
	struct timeval start, stop;
	int i, j, k;


	/*Geenerate matrixes */
	for (i = 0; i < N; i++){
	for (j = 0; j < N; j++) {
		matrix_A[i][j] = 1 + (int)(NUMLIMIT*rand() / (RAND_MAX + 1.0));
		matrix_B[i][j] = (double)(rand() % RANDLIMIT);

	}
	}


	/*Matrix multiplication*/
	gettimeofday(&start, 0);//start the time

	#pragma omp parallel shared(matrix_A, matrix_B, matrix_C) private(i, j, k)
	{
	#pragma omp for schedule(static)
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			matrix_C[i][j] = 0.0;
			for (k = 0; k < N; k++)
				matrix_C[i][j] = matrix_C[i][j] + matrix_A[i][k] * matrix_B[k][j];
			} 
		}
	}
	gettimeofday(&stop, 0);//stop the time

	//Consumed time
	fprintf(stdout, "Time = %.6f\n\n",
		(stop.tv_sec + stop.tv_usec*1e-6) - (start.tv_sec + start.tv_usec*1e-6));
	return(0);
}

