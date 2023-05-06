#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_BENCHES 2
#define N_USERS 5
#define seed 142022

typedef struct {
	int reps;
	int sets;
	long id;
} User;


// user function
void* bench_set(void* args) {

	User* arg = (User *) args;
	long tid = (long) arg->id;
	
	printf("%ld -> Adjusting weights...\n", tid);
	sleep(2);

	int missing_reps = arg->reps;
	int missing_sets = arg->sets;
	while (missing_sets > 0){
		
		while (missing_reps > 0){
			missing_reps -= 1;
		}
		missing_sets -= 1;
		printf("%ld -> Remaining Sets:%d\n", tid, missing_sets);
	}
	
	return NULL;
}

int main() {   

	long t;

	User att[N_USERS];
	pthread_t th_vec[N_USERS];

	for (t = 0; t < N_USERS; t++) {

		att[t].id = t;
		att[t].reps = 8;
		att[t].sets = 3;

		if (pthread_create(th_vec + t, NULL, &bench_set, &att[t]) != 0){ // th + i = &th[i]
			perror("Failed to create thread");
			return 1;
		}
	}

	// Wait for all threads to finish
	for (t = 0; t < N_USERS; t++) {
		if  (pthread_join(th_vec[t], NULL)){
			return 2;
		}
	}
}