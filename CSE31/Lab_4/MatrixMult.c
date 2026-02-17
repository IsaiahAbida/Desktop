
#include <stdio.h>
#include <stdlib.h>

int** matMult(int **a, int **b, int size) {
	// (4) Implement your matrix multiplication here. 
	// You will need to create a new matrix to store the product.

	 int i, j, k;
    
    // allocate memory for the result matrix
    int **result = (int **) malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        *(result + i) = (int *) malloc(size * sizeof(int));
        for (j = 0; j < size; j++)
            *(*(result + i) + j) = 0; // Initialize with 0
    }

    // perform matrix multiplication
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                *(*(result + i) + j) += (*(*(a + i) + k)) * (*(*(b + k) + j));
            }
        }
    }
return result;
}

void printArray(int **arr, int n) {
	// (2) Implement your printArray function here
	int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%d ", *(*(arr + i) + j)); // access arr[i][j] using pointers
        }
        printf("\n");
    }
    printf("\n");

}

int main() {
	int n = 0;
	int **matA, **matB, **matC;
	// (1) Define 2 (n x n) arrays (matrices). 
	
	int i, j;
n = 3; // Example size, you can later ask the user to input n

// Allocate matA
matA = (int **) malloc(n * sizeof(int *));
for(i = 0; i < n; i++) {
    *(matA + i) = (int *) malloc(n * sizeof(int));
    // Initialize elements to 0
    for(j = 0; j < n; j++)
        *(*(matA + i) + j) = 0;
}

// Allocate matB
matB = (int **) malloc(n * sizeof(int *));
for(i = 0; i < n; i++) {
    *(matB + i) = (int *) malloc(n * sizeof(int));
    for(j = 0; j < n; j++)
        *(*(matB + i) + j) = 0;
}

	// (3) Call printArray to print out the 2 arrays here.
	
printf("Matrix A:\n");
printArray(matA, n);

printf("Matrix B:\n");
printArray(matB, n);

	// (5) Call matMult to multiply the 2 arrays here.
	
	matC = matMult(matA, matB, n);
	
	// (6) Call printArray to print out resulting array here.

	printArray(matC, n);

    return 0;
}