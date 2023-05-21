#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define N_CAPACIDADE 5 
#define N_MACHINES 2
#define N_EXERCISES 4  
#define N_USERS 8

sem_t espera_entrada;                   // Semaforo de espera representando a capacidade maxima da academia
sem_t exercise_available[N_EXERCISES];  // Semaforos para distribuicao das maquinas livres por cada exercicio.
sem_t exercise_done[N_EXERCISES];       // Semaforos para distribuicao do sinal de completude do exercicio por maquina
sem_t exercise_in_use[N_EXERCISES];     // Semaforos para indicar a ocupação das maquinas para cada exercicio

// User function
void* f_maromba(void* user_arg) {
    int* id = (int*)user_arg;

    int user_id = *id;
    int machine_slot = -9; 
    // sleep(1);

    if (sem_trywait(&espera_entrada) == 0) {
        printf("%d : Entrei na OitoEncaixes.\n", user_id);

        for (int i = 0; i < N_EXERCISES; i++) {

            int machine_id = (user_id + i) % N_EXERCISES;
            sem_wait(&exercise_available[machine_id]);
            sem_getvalue(&exercise_available[machine_id], &machine_slot);

            printf("%d : Fazendo Exercicio %c na maquina %d.\n", user_id, 'A' + machine_id, machine_slot );
            sem_post(&exercise_in_use[machine_id]);
            sem_wait(&exercise_done[machine_id]);
            printf("%d : Terminou Exercicio %c na maquina %d.\n", user_id, 'A' + machine_id, machine_slot);
            sem_post(&exercise_available[machine_id]);

        }

        sem_post(&espera_entrada);

        printf("%d : Terminou o treino e vai embora!.\n", user_id);
    }
    else {
        printf("%d : Academia esta cheia!! Vai embora!\n", user_id);
    }

    return NULL;
}

// Exercise machine function
void* f_exercise_machine(void* machine_args) {
    int* arg = (int*)machine_args;
    int machine_id = *arg;

    while (1) {
        sem_wait(&exercise_in_use[machine_id]);
        sleep(1); // pausa para simular a execucao dos exercicios
        sem_post(&exercise_done[machine_id]);
    }

    return NULL;
}

int main() {

    printf("Parameters:\nCAPACIDADE DA ACADEMIA:%d\nNUMERO DE MAQUINAS:%d\nNUMERO DE EXERCICIOS:%d\n\n", N_CAPACIDADE, N_MACHINES, N_EXERCISES);

    int att[N_USERS];
    int exercises[N_EXERCISES];
    
    pthread_t th_vec[N_USERS];
    pthread_t exercise_machine[N_EXERCISES];


    sem_init(&espera_entrada, 0, N_CAPACIDADE);
    for (int i = 0; i < N_EXERCISES; i++) {
        sem_init(&exercise_available[i], 0, N_MACHINES);
        sem_init(&exercise_done[i], 0, 0);
        sem_init(&exercise_in_use[i], 0, 0);
        exercises[i] = i;
    }

    for (int i = 0; i < N_USERS; i++) {
        att[i] = i;
        if (pthread_create(th_vec + i, NULL, &f_maromba, &att[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < N_EXERCISES; i++) {
        if(pthread_create(exercise_machine + i, NULL, &f_exercise_machine, &exercises[i]) != 0){
            return 2;
        }
    }

    // Wait for all threads to finish
    for (int t = 0; t < N_USERS; t++) {
        if (pthread_join(th_vec[t], NULL)) {
            return 3;
        }
    }


    return 0;
}
