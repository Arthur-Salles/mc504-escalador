#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define FILA_LIMITE 3
#define N_MACHINES_PER_EXERCISE 1
#define N_EXERCISES 2
#define N_USERS 1

typedef struct {
	int reps;
	int sets;
	long id;
} User;


/* ----- Semaphores  ------  */  

sem_t sem_espera_exercicio[N_EXERCISES];
sem_t sem_maquina_disponivel[N_EXERCISES]; // entrou ou nao na maquina 
sem_t sem_aloca_fila;
sem_t sem_maq_ocupada[N_EXERCISES];
sem_t sem_exercicio_feito[N_EXERCISES];

int fila[N_EXERCISES][N_MACHINES_PER_EXERCISE];


// sem_t sem_escreve_visor;
// sem_t sem_le_visor;

// int machine;
// int usersWaiting[N_USERS];
// int machineUsers[N_BENCHES];

int get_menor_fila_id(){

	return 0;
} 

void* f_user(void *v) {

	int id = *(int*) v;
	int my_machine, my_position;
	int i = 0;
	

	sem_wait(&sem_aloca_fila);

	// aloca o usuario na menor fila 

	// SUPOR QUE ELE ENTRE NA MENOR FILA

	int fila_id = get_menor_fila_id();
	

	// e o espera
	sem_wait(&sem_espera_exercicio[fila_id]);

	sem_post(&sem_aloca_fila);

	// aloca o user na fila

	sem_wait(&sem_maquina_disponivel[fila_id]);

	printf("entrou na maquina da fila %d\n", fila_id);
	
	sem_post(&sem_espera_exercicio[fila_id]); //esper
	sem_post(&sem_maq_ocupada[fila_id]);

	sem_wait(&sem_exercicio_feito[fila_id]);
	sem_post(&sem_maquina_disponivel[fila_id]);
	printf("e o treinas \n");

}

void* f_machine(void *v) {
	int id = *(int*)v;
  
  	while(1) {


		sem_wait(&sem_maq_ocupada[id]);
		printf("anabolico\n");
		sleep(1);
		sem_post(&sem_exercicio_feito[id]);

 	}
  	return NULL;
}

int main() {   

	//long t;

	//User att[N_USERS];
	//pthread_t th_vec[N_USERS];
	pthread_t thr_users[N_USERS], thr_machines[N_EXERCISES * N_MACHINES_PER_EXERCISE] ;
  	int i, id_cl[N_USERS], id_mac[N_EXERCISES * N_MACHINES_PER_EXERCISE];

	sem_t sem_espera_exercicio[N_EXERCISES];

	for (int i = 0; i < N_EXERCISES; i++){
		sem_init(&sem_espera_exercicio[i], 0, FILA_LIMITE);
	}

	for (i = 0; i < N_EXERCISES; i++) {
		sem_init(&sem_maquina_disponivel[i], 0, N_MACHINES_PER_EXERCISE);
    }
	
	sem_init(&sem_aloca_fila, 0, 1);
	
	for (int i = 0; i < N_EXERCISES; i++){
		sem_init(&sem_maq_ocupada[i], 0, 1);
		sem_init(&sem_exercicio_feito[i], 0, 1);

	}
	

	for (i = 0; i < N_USERS; i++) {
		id_cl[i] = i;
		pthread_create(&thr_users[i], NULL, f_user, (void*) &id_cl[i]);
	}

	for (i = 0; i < N_EXERCISES * N_MACHINES_PER_EXERCISE; i++) {
		id_mac[i] = i;
		pthread_create(&thr_machines[i], NULL, f_machine, (void*) &id_mac[i]);
	}

	for (i = 0; i < N_USERS; i++) {
		pthread_join(thr_users[i], NULL);
	}

	for (i = 0; i < N_EXERCISES * N_MACHINES_PER_EXERCISE; i++) {
		pthread_join(thr_machines[i], NULL);
	}

	return 0;
}