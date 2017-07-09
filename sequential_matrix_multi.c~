#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


double **createMatrix(int value);
void getAveragetime();
double timeCalculation();
double **sequential_multiply(double **matrix_A,double **matrix_B,double **matrix_C);
void  empty_matrix(double **matrix);
void printMatrix(double **matrix);

static int N;
static int sample_size;

double **matrix_A;//input matrix 1
double **matrix_B;//input matrix 2
double **matrix_C;//output matrix

int i, j, k;


int main(int argc, char *argv[])
{
	
	sample_size=50;

	for(N=200;N<=2000;N+=200){
	getAveragetime();
	}
	return(0);
}

/*
allocate memory for matrixes & asign values
*/
double **createMatrix(int value){
	double **matrix;
	if(value==1){

        matrix = (double **)malloc(sizeof(double *)*N);                                 
        for(i=0; i<N; i++)
                matrix[i] = (double *)malloc(sizeof(double)*N);
	for (i= 0; i< N; i++) {
        for (j = 0; j < N; j++) {
            matrix[i][j] = (double)rand()/1000;
        }
    }

	}else{
	 matrix = (double **)malloc(sizeof(double *)*N);                           
        for(i=0; i<N; i++)
                matrix[i] = (double *)malloc(sizeof(double)*N);

	}
	return matrix;
}

/*
calculate the average time consumption
*/
void getAveragetime(){

    double total = 0.0;
    int p;
    for (p = 0; p < sample_size; p++) {
        total += timeCalculation();
    }

    double average = total / sample_size;
    printf("Sequential time consumption matrix size : %d time : %f seconds\n", N,average);

}

/*
calculate time for one multiplication
*/
double timeCalculation() {

	
    srand((unsigned) time(0));
    double timeval, start, stop;
    matrix_A=createMatrix(1);
    matrix_B=createMatrix(1);
    matrix_C=createMatrix(0);
    start = omp_get_wtime();

    matrix_C=sequential_multiply(matrix_A,matrix_B,matrix_C);

    stop = omp_get_wtime();

    timeval = (stop - start);

    //empty matrix memory
    empty_matrix(matrix_A);
    empty_matrix(matrix_B);
    empty_matrix(matrix_C);

    return timeval;
}

/*
sequential multiplication
*/
double **sequential_multiply(double **matrix_A,double **matrix_B,double **matrix_C){
for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        matrix_C[i][j] = 0.0;
                        for (k = 0; k < N; k++)
                                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
                }
        }
return matrix_C;
}


/*
clean the matrix memory
*/
void empty_matrix(double **matrix) {
    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}	
