#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double **createMatrix(int value);
void getAveragetime();
double timeCalculation();
double **matrix_multiply_parallel_optimized(double **A, double **B, double **C);
double **parallel_multiply(double **matrix_A,double **matrix_B,double **matrix_C);
void  empty_matrix(double **matrix);


static int N;
static int sample_size;

double **matrix_A;//input matrix 1
double **matrix_B;//input matrix 2
double **matrix_C;//output matrix

int i, j, k;
int thread_count=8;

int main(int argc, char *argv[])
{

	if (argc != 3) {
        printf("Issue in arguments");
       }else{
	sscanf(argv[1], "%d", &N);
    	sscanf(argv[2], "%d", &sample_size);
	omp_set_num_threads(thread_count);		
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
            matrix[i][j] = (double)rand();
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
    printf("Optimized parallel time consumption : %f seconds\n", average);
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
    matrix_C=parallel_multiply(matrix_A,matrix_B,matrix_C);
    stop = omp_get_wtime();
    // calculate the time consumption
    timeval = (stop - start);

    //empty matrix memory
    empty_matrix(matrix_A);
    empty_matrix(matrix_B);
    empty_matrix(matrix_C);
    return timeval;
}

void to_transpose(int size, double** matrix_any) //function for transpose a givn matrix
{
    int i,j;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            double temp = matrix_any[i][j];
            matrix_any[i][j] = matrix_any[j][i];
            matrix_any[j][i] = temp;
        }
    }
}

/*
parallel multiplication
*/
double **parallel_multiply(double **matrix_A,double **matrix_B,double **matrix_C){
to_transpose(N,matrix_B);

//#pragma omp for schedule(static)
#pragma omp parallel for private(i, j, k)
for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        matrix_C[i][j] = 0.0;
						double temp = 0;
                        for (k = 0; k < N; k++)
                                temp += matrix_A[i][k] * matrix_B[k][j];
						matrix_C[i][j] = temp;
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

void printMatrix(double **matrix){
for (i = 0; i < N; i++) {
for (j = 0; j < N; j++) {
printf("%f \t",matrix[i][j]);
    }
printf("\n");
    }}
