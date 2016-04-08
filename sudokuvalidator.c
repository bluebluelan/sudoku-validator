
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 27
#define LENGTH 9
#define ONE_THIRD_LENGTH 3
#define FALSE 0
#define TRUE 1
#define MIN_ARGC 2
#define FILE_PATH_ARG 1
#define TEST_TYPE 0
#define START_VAL 1


static int *puz[LENGTH];
static int lastRegion = 0;
static int duplicate = FALSE;


int main(int argc, const char *argv[]) {
	
	int i, j, k;

	if (argc < 2) {
		printf("no input\n");
		return 0;
	}
	for (i = 0; i < LENGTH; i++)
		puz[i] = (int *)malloc(sizeof(int) * LENGTH);
	
	FILE *file;
	
	if ((file = fopen(argv[1], "r")))
	{

		for (i = 0; i < LENGTH; i++) {

			int *ptr = puz[i];
			fscanf(file, "%d %d %d %d %d %d %d %d %d", ptr, ptr+1, ptr+2, ptr+3, ptr+4, ptr+5, ptr+6, ptr+7, ptr+8);
		}
		printf("File Parsed.\n");
	
		fclose(file);
	}

	int val1, val2;
/*
	for (i = 0; i < LENGTH; i++){
		for (j = 0; j < LENGTH; j++){
			printf("%d ", puz[i][j]);
		}
		printf("\n");
	}
*/
	for (k = 0;k< LENGTH; k++){
		for (i = 0; i < LENGTH; i++) {
				val1 = puz[k][i];
				for (j = 0; j < LENGTH; j++) {
					val2 = puz[k][j];
					if (val1 == val2) {		
						if (!(i == j))
						{
							printf("we found duplicate in [%d][%d][%d][%d]  \n", k, i, k, j);
							return 0;					
						}
				}
			}
		}
	}
	printf("column down\n");

	for (k = 0;k< LENGTH; k++){
		for (i = 0; i < LENGTH; i++) {
				val1 = puz[i][k];
				for (j = 0; j < LENGTH; j++) {
					val2 = puz[j][k];
					if (val1 == val2) {		
						if (!(i == j))
						{
							printf("we found duplicate in [%d][%d][%d][%d]  \n", i, k, i, k);
							return 0;
					}
				}
			}
		}
	}
	printf("row down\n");
	int l;
	for (k = 0; k < ONE_THIRD_LENGTH; k++){
		for (l = 0; l < ONE_THIRD_LENGTH; l++){
			int clonearr[9]={1,2,3,4,5,6,7,8,9};
			val1=puz[k*3][l*3];
			if(clonearr[val1-1]!=0){
				clonearr[val1-1]=0;
			}
			for (i = 0; i < ONE_THIRD_LENGTH; i++){
				for (j = 0; j < ONE_THIRD_LENGTH; j++){
					val2=puz[k*3+i][l*3+j];
					if(clonearr[val2-1]!=0){
						clonearr[val2-1]=0;
					}
					else if(clonearr[val2-1]==0 && i+j != 0){

						printf("we found duplicate in [%d][%d]\n" k*3+i, l*3+j);
						return 0;
					}

				}
			}
		}
	}
			
	printf("block down\n");

	
 	/* Free memory for the columns in each row */
 	for (i = 0; i < LENGTH; i++)
 		free(puz[i]);
	
	printf("done\n");
	// return with success status
	return 0;
}