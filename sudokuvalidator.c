
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define LENGTH 9
#define BLOCK_LENGTH 3

static int *solution[LENGTH];

int main(int argc, const char *argv[]) {
	
	int i, j, k, l;

	if (argc < 2) {
		printf("no input\n");
		return 0;
	}
	for (i = 0; i < LENGTH; i++)
		solution[i] = (int *)malloc(sizeof(int) * LENGTH);
	
	FILE *file;
	
	if ((file = fopen(argv[1], "r")))
	{

		for (i = 0; i < LENGTH; i++) {

			int *ptr = solution[i];
			fscanf(file, "%d %d %d %d %d %d %d %d %d", ptr, ptr+1, ptr+2, ptr+3, ptr+4, ptr+5, ptr+6, ptr+7, ptr+8);
		}
		printf("File Parsed.\n");
	
		fclose(file);
	}

	int val1, val2;

	for (k = 0;k< LENGTH; k++){
		for (i = 0; i < LENGTH; i++) {
				val1 = solution[k][i];
				for (j = 0; j < LENGTH; j++) {
					val2 = solution[k][j];
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
				val1 = solution[i][k];
				for (j = 0; j < LENGTH; j++) {
					val2 = solution[j][k];
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

	for (k = 0; k < BLOCK_LENGTH; k++){
		for (l = 0; l < BLOCK_LENGTH; l++){
			int clonearr[9]={1,2,3,4,5,6,7,8,9};
			val1=solution[k*3][l*3];
			if(clonearr[val1-1]!=0){
				clonearr[val1-1]=0;
			}
			for (i = 0; i < BLOCK_LENGTH; i++){
				for (j = 0; j < BLOCK_LENGTH; j++){
					val2=solution[k*3+i][l*3+j];
					if(clonearr[val2-1]!=0){
						clonearr[val2-1]=0;
					}
					else if(clonearr[val2-1]==0 && i+j != 0){

						printf("we found duplicate in [%d][%d]\n", k*3+i, l*3+j);
						return 0;
					}

				}
			}
		}
	}
			
	printf("block down\n");

	
 	for (i = 0; i < LENGTH; i++)
 		free(solution[i]);
	
	printf("done\n");
	return 0;
}