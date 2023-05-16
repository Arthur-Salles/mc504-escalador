#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define N_FILA 1
#define N_BENCHES 1
#define N_EXERCISES 3 

#define N_USERS 8
#define seed 142022

sem_t espera; 				// somente uma pessoa espera, se tiver mais do que alguem esperando você sai
sem_t supino_disponivel; 		// 
sem_t supino_feito;		//
sem_t banco_ocupado;		//

typedef struct{

	char name_ab;
	int user_id;
	int machine_id;

} Exercise;

typedef struct {
	int reps_per_exercise[N_EXERCISES];
	int sets_per_exercise[N_EXERCISES];
	int id;
} User;


// user function
void* f_maromba(void* maromba_args) {

	User * args = (User *) maromba_args;

	// sleep(1);

	if (sem_trywait(&espera) == 0){

		printf("%d : TO NA FILA DO SUPINO\n", args->id);
		sem_wait(&supino_disponivel);

		printf("%d : sentou no banco\n", args->id);

		sem_post(&espera);
		sem_post(&banco_ocupado);
		
		sem_wait(&supino_feito);
		sem_post(&supino_disponivel);
		
		printf("%d : Terminei a serie meno\n", args->id);
	}
	else{
		// no futuro inserir codigo pra ir em outra maquina tambem
		printf("%d: seloko vou esperar nao six ta cheia\n", args->id);
	}

	return NULL;
}


// bench press
void* f_treino(void* exercises_args){

	Exercise * arg = (Exercise*) exercises_args;

	while(1){
		sem_wait(&banco_ocupado);
		printf("fez uma serie de %c no banco %d\n", arg->name_ab, arg->machine_id);
		sleep(1);
		sem_post(&supino_feito);
	}

	return NULL;
}



int main() {   

	printf("im working\n");

	long t;
	User att[N_USERS];
	pthread_t th_vec[N_USERS];
	pthread_t banco_supininho;

	Exercise supino;

	sem_init(&espera, 0, N_FILA);
	sem_init(&supino_disponivel, 0, N_BENCHES);
	sem_init(&supino_feito, 0, 0);
	sem_init(&banco_ocupado, 0, 0);


	supino.machine_id = 0;
	supino.name_ab = 'S';
	supino.user_id = 88;

	for (t = 0; t < N_USERS; t++) {

		att[t].id = t;

		if (pthread_create(th_vec + t, NULL, &f_maromba, &att[t]) != 0){ // th + i = &th[i]
			perror("Failed to create thread");
			return 1;
		}
	}

	pthread_create(&banco_supininho, NULL, f_treino, &supino);



	// Wait for all threads to finish
	for (t = 0; t < N_USERS; t++) {
		if  (pthread_join(th_vec[t], NULL)){
			return 2;
		}
	}
	printf("not deadlocked baby\n");
}