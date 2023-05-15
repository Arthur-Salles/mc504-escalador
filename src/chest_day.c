#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_BENCHES 2
#define N_USERS 5

typedef struct {
	int reps;
	int sets;
	long id;
} User;


/* ----- Semaphores  ------  */  

sem_t sem_fila;
sem_t sem_machine[N_BENCHES];
sem_t sem_machine_seat[N_BENCHES];
sem_t sem_escreve_visor;
sem_t sem_le_visor;

int machine;
int usersWaiting[N_USERS];
int machineUsers[N_BENCHES];

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

void* f_user(void *v) {
	int id = *(int*) v;
	int my_machine, my_position;
	int i = 0;

	// usuario chegou na academia
	sem_wait(&sem_fila);

	/* Aloca um lugar na fila pro usuario */

    for (i = 0; i < N_USERS; i++) {
    	usersWaiting[id] = id;
	}

	//imprime que o user chegou na academia e esta esperando
	sem_post(&sem_fila);

	
    sem_wait(&sem_le_visor); /* Cliente espera o visor mostrar uma maquina livre. */
    my_machine = machine; 
    sem_post(&sem_escreve_visor); /* Permite que outra maquina escreva informe que esta livre. */

	sem_wait(&sem_machine[my_machine]); // começa a usar a maquina

	sem_wait(&sem_fila);
	usersWaiting[id] = -1;
	sem_post(&sem_fila);

	machineUsers[my_machine] = id;
	// faz o exercicio: pode chamar a func bench_set()
	printf("User %p", id, " is using bench %p", my_machine);

	sem_post(&sem_machine_seat[my_machine]); //libera a cadeira da maquina
	sem_post(&sem_machine[my_machine]); // libera maquina que vc usou
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

	//sem_init(&sem_cadeiras, 0, N_CADEIRAS);
	sem_init(&sem_escreve_visor, 0, 1);
	sem_init(&sem_le_visor, 0, 0);
	sem_init(&sem_fila, 0, 1);

	// for (t = 0; t < N_USERS; t++) {

	// 	att[t].id = t;
	// 	att[t].reps = 8;
	// 	att[t].sets = 3;

	// 	if (pthread_create(th_vec + t, NULL, &bench_set, &att[t]) != 0){ // th + i = &th[i]
	// 		perror("Failed to create thread");
	// 		return 1;
	// 	}
	// }

	// Wait for all threads to finish
	// for (t = 0; t < N_USERS; t++) {
	// 	if  (pthread_join(th_vec[t], NULL)){
	// 		return 2;
	// 	}
	// }

	for (i = 0; i < N_BENCHES; i++) {
		sem_init(&sem_machine_seat[i], 0, 1);
		sem_init(&sem_machine[i], 0, 0);
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