#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


#define N_MACHINES_PER_EXERCISE 1
#define N_EXERCISES 2
#define N_USERS 1

typedef struct {
	int reps;
	int sets;
	long id;
} User;


/* ----- Semaphores  ------  */  

sem_t sem_fila_exercicios[N_EXERCISES];
sem_t sem_machines[N_EXERCISES]; // entrou ou nao na maquina 
sem_t sem_aloca_fila;

int fila[N_EXERCISES][N_MACHINES_PER_EXERCISE];


// sem_t sem_escreve_visor;
// sem_t sem_le_visor;

// int machine;
// int usersWaiting[N_USERS];
// int machineUsers[N_BENCHES];

int get_menor_fila_id(){


	// for(int i = 0; i < N_EXERCISES; i++){
		
	// 	int fila_size = 0;

	// 	for (int j = 0; j < N_MACHINES_PER_EXERCISE; j++){
			
	// 		if (fila[i][j] != -1){
	// 			fila_size += 1
	// 		}

	// 	}

	// }
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
	

	sem_wait(&sem_fila_exercicios[fila_id]);

	sem_post(&sem_aloca_fila);

	// aloca o user na fila


	sem_post(&sem_fila_exercicios[fila_id]);


	sem_wait(&sem_machines[fila_id]);



}

void* f_machine(void *v) {
	int id = *(int*)v;
  
  	while(1) {
    	sem_wait(&sem_escreve_visor); //outra maquina nao pode escrever no visor enquanto um usuario nao pega-la
		machine = id;
		sem_post(&sem_le_visor); //um novo usuario pode ler o visor, ja que ele foi atualizado
		
		/* Para o exc nao ser imediato.*/
		sleep(1);
		
		sem_wait(&sem_machine_seat[id]); // cadeira da maquina fica ocupada
 	}
  	return NULL;
}

int main() {   

	//long t;

	//User att[N_USERS];
	//pthread_t th_vec[N_USERS];
	pthread_t thr_users[N_USERS], thr_machines[N_BENCHES];
  	int i, id_cl[N_USERS], id_mac[N_BENCHES];

	sem_init(&sem_escreve_visor, 0, 1);
	sem_init(&sem_le_visor, 0, 0);
	sem_init(&sem_fila, 0, 0);



	printf("odaodai\n");

	for (i = 0; i < N_EXERCISES; i++) {
		// sem_init(&sem_machine_seat[i], 0, 0);
		sem_init(&sem_machines[i], 0, N_MACHINES_PER_EXERCISE);
    }

	for (i = 0; i < N_USERS; i++) {
		id_cl[i] = i;
		pthread_create(&thr_users[i], NULL, f_user, (void*) &id_cl[i]);
	}

	for (i = 0; i < N_BENCHES; i++) {
		id_mac[i] = i;
		pthread_create(&thr_machines[i], NULL, f_machine, (void*) &id_mac[i]);
	}

	for (i = 0; i < N_USERS; i++) {
		pthread_join(thr_users[i], NULL);
	}

	for (i = 0; i < N_BENCHES; i++) {
		pthread_join(thr_machines[i], NULL);
	}

	return 0;
}