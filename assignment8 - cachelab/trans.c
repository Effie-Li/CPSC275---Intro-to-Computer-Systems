/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{

	int i, j, i1, j1;
	int temp;
	
	/* 
	 * For 32 * 32 matrix, transpose by blocking the matrix to 8 * 8 matrices and
	 *  transpose them one by one. Also, delay trasposing diagonal entries until
	 *  every other element within the little blocks are transposed.
	 */
	if (N == 32) {
		
		for(i=0; i<N; i+=8) 
			for(j=0; j<M; j+=8)
				for(i1=i; i1<i+8; i1++) {
					for(j1=j; j1<j+8; j1++) {
						if (i == j && i1 == j1) temp = i1;
						else B[j1][i1] = A[i1][j1];
					}
					if (i == j && i1 == temp) 
						B[temp][temp] = A[temp][temp];
				}
	}
	
	/*
	 * For 64 * 64 matrix, transpose by blocking the matrix to 8 * 8 matrices,
	 *  and then block each 8 * 8 matrix into 4 * 4 matrices, and transpose by
	 *  a U shaped order. Within each 4 * 4 matrix, delay transposing diagonal
	 *  entries until every other element within the little blocks are transposed.
	 */
	
	else if (N == 64) {
		
		for(i=0; i<N; i+=8) 
			for(j=0; j<N; j+=8) {
				
				for(i1=i; i1<i+4; i1++) {
					for(j1=j;j1<j+4; j1++) {
						if (i == j && i1 == j1) temp = i1;
						else B[j1][i1] = A[i1][j1];
					}
					if (i ==j && i1 == temp)
						B[temp][temp] = A[temp][temp];
				}
				
				for(i1=i+4; i1<i+8; i1++) {
					for(j1=j; j1<j+4; j1++) {
						if (i == j && i1 == j1) temp = i1;
						else B[j1][i1] = A[i1][j1];
					}
					if (i ==j && i1 == temp)
						B[temp][temp] = A[temp][temp];
				}
				
				for(i1=i+4; i1<i+8; i1++) {
					for(j1=j+4; j1<j+8; j1++) {
						if (i == j && i1 == j1) temp = i1;
						else B[j1][i1] = A[i1][j1];
					}
					if (i ==j && i1 == temp)
						B[temp][temp] = A[temp][temp];
				}
				
				for(i1=i; i1<i+4; i1++) {
					for(j1=j+4; j1<j+8; j1++) {
						if (i == j && i1 == j1) temp = i1;
						else B[j1][i1] = A[i1][j1];
					}
					if (i ==j && i1 == temp)
						B[temp][temp] = A[temp][temp];
				}
						 
			}

	}
	
	/*
	 * For the 61 * 67 matrix, block it into 12 * 8 matrices, and transpose
	 *  each block.
	 */
	
	else {
		
		for(i=0; i<N; i+=12) {
			for(j=0; j<M; j+=8) {
				for(i1=i; i1<i+12; i1++) {
					if (i1 >= 67) break;
					for(j1=j; j1<j+8; j1++) {
						if (j1 >= 61) break;
						B[j1][i1] = A[i1][j1];
					}
				}
			}
		}
		
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

