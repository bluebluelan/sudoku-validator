
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define LENGTH 9
#define BLOCK_LENGTH 3
#define NUM_OF_THREAD 27
#define FALSE 0
#define TRUE 1

static int *solution[LENGTH];

static int duplicate = FALSE;

pthread_mutex_t lock;


typedef enum {
	ROW,
	COLUMN,
	BLOCK
} chk_t;

void *runner(void *para);

int main(int argc, const char *argv[]) {
	
	int i, j, k, l;
	int status;

	pthread_t workers[NUM_OF_THREAD];

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
	// load file completed

	pthread_mutex_init(&lock, NULL);


	// generate threads by NUM_OF_THREAD

	for(int i=0;i<NUM_OF_THREAD;i++){

		int thread_args[4];
		int initialrow;
		int initialcol;
		chk_t chk;
		
		if (i < 9) {
			chk = ROW;
			initialrow = i;
			initialcol = 0;
		}

		else if (i < 18) {
			chk = COLUMN;
			initialrow = 0;
			initialcol = (i-9);
		}
		else {
			chk = BLOCK;
			switch(i){
				case 18:

					initialrow = 0;
					initialcol = 0;
					break;
				case 19:
					initialrow = 0;
					initialcol = 3;	
					break;				
				case 20:
					initialrow = 0;
					initialcol = 6;
					break;
				case 21:
					initialrow = 3;
					initialcol = 0;
					break;
				case 22:
					initialrow = 3;
					initialcol = 3;
					break;
				case 23:
					initialrow = 3;
					initialcol = 6;
					break;					
				case 24:
					initialrow = 6;
					initialcol = 0;
					break;
				case 25:
					initialrow = 6;
					initialcol = 3;
					break;
				case 26:
					initialrow = 6;
					initialcol = 6;
					break;
			}
		}
		
		thread_args[0] = chk;
		thread_args[1] = initialrow;
		thread_args[2] = initialcol;
		thread_args[3] = i;
 		// create the new thread 
 		//printf("we create in [%d][%d] thread %d \n", initialrow, initialcol, i);
        pthread_create(&workers[i], NULL, runner, (void *)thread_args);
	}

	for (i = 0; i < NUM_OF_THREAD; i++){
         pthread_join(workers[i], NULL);
         //printf("Thread %d complete\n",i);
    }

	pthread_mutex_destroy(&lock);

	if (duplicate == TRUE){

		printf("Is a invalid solution\n");
	}
	else{

		printf("Is a valid solution\n");
	}
	
 	for (i = 0; i < LENGTH; i++)
 		free(solution[i]);
	
	return 0;
}

void *runner(void *para){
	int *thread_params = (int *)para;
	chk_t type = thread_params[0];
	int initialrow = thread_params[1];
	int initialcol = thread_params[2];
	int thread_num = thread_params[3];
	int i, j, val1, val2;
	if (type == ROW){
		for (i = 0; i < LENGTH; i++) {
				val1 = solution[initialrow][i];
				for (j = 0; j < LENGTH; j++) {
					val2 = solution[initialrow][j];
					if (val1 == val2) {		
						if (i != j){
							printf("we found duplicate in [%d][%d]-[%d][%d] in thread %d \n", initialrow, i, initialrow, j, thread_num);
							pthread_mutex_lock(&lock);
							duplicate = TRUE;
							pthread_mutex_unlock(&lock);		
							break;
							break;
						}
				}
			}
		}
		printf("row down %d \n" , thread_num);
	}
	
	else if (type == COLUMN){
		for (i = 0; i < LENGTH; i++) {
			val1 = solution[i][initialcol];
			for (j = 0; j < LENGTH; j++) {
				val2 = solution[j][initialcol];
				if (val1 == val2) {		
					if (i != j){
						printf("we found duplicate in [%d][%d]-[%d][%d] in thread %d \n", i, initialcol, j, initialcol, thread_num);
						pthread_mutex_lock(&lock);
						duplicate = TRUE;
						pthread_mutex_unlock(&lock);
						break;
						break;
					}
				}
			}
		}
		printf("column down %d  \n" , thread_num);
	}
	else if (type == BLOCK) {
		int clonearr[9]={1,2,3,4,5,6,7,8,9};
		for (i = initialrow; i < initialrow+BLOCK_LENGTH; i++){
			for (j = initialcol; j < initialcol+BLOCK_LENGTH; j++){
				val2=solution[i][j];
				if(clonearr[val2-1] == 0){
					printf("we found duplicate in [%d][%d] in thread %d \n", i, j, thread_num);
					pthread_mutex_lock(&lock);
					duplicate = TRUE;
					pthread_mutex_unlock(&lock);
					break;
					break;
				}
				clonearr[val2-1]=0;
			}
		}
		printf("block down %d  \n" , thread_num);
	}

	pthread_exit(0);
}