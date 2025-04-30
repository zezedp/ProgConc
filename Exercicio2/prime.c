#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"
#include <math.h>

pthread_mutex_t mutex;
long long int next = 1;
long long int N;
long int counter = 0;

void write_csv(double time, int n_threads){
	FILE* file = fopen("results.csv", "a"); // a = append
	if (file == NULL){
		perror("Erro ao abrir arquivo");
		exit(-1);
	}
	if (ftell(file) == 0) fprintf(file, "N,Threads,Tempo(s),Primo(s) Encontrado(s)\n");
	fprintf(file, "%lld,%d,%.6f,%ld\n", N, n_threads, time, counter);
	printf("Arquivo 'results.csv' atualizado!");
	fclose(file);
}

int is_Prime(long long int n){
	int ret;
	if (n <= 1) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	long long int lim = sqrt(n);
	for (int i=3; i < lim +1; i+=2){
		if (n % i == 0) return 0;
	}
	return 1;
}

void* prime_sequence(){
	long long int local;
	while (1){
		pthread_mutex_lock(&mutex);
		/*Seção Crítica (VAR compartilhada 'next')*/
		if (next > N){
			pthread_mutex_unlock(&mutex);
			break;
		}

		local = next; next++;
		pthread_mutex_unlock(&mutex);
		/* Finaliza Seção Crítica*/
		
		/* Seção Crítica (VAR compartilhada 'counter')*/
		if (is_Prime(local)){
			pthread_mutex_lock(&mutex);
			counter++;
			pthread_mutex_unlock(&mutex);
		}
		/* Finaliza Seção Crítica */
	}	
}

int main(int argc, char* argv[]){
	pthread_t* tid;
	if (argc != 3){
		printf("ERRO: Modo de uso %s <nthreads> <numero>", argv[0]);
		exit(-1);
	}
	int nthreads = atoi(argv[1]);
	N = atoll(argv[2]);
	
	tid = (pthread_t*) malloc(sizeof(pthread_t) * nthreads);
	if (tid == NULL){
		printf("ERRO: malloc() do tid");
		exit(-2);
	}
	pthread_mutex_init(&mutex, NULL);
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	/* Cria threads */
	for (long int i = 0; i < nthreads; ++i){
		if (pthread_create(&tid[i], NULL, prime_sequence, NULL)){
			perror("ERRO: Pthread Create");
		} 
	}
	
	/* Espera Threads */
	for (long int i = 0; i < nthreads; ++i){
		if (pthread_join(tid[i], NULL)){
			perror("ERRO: Pthread Join");
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);

	double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) /1e9;
	printf("Numero de primos na sequencia 1-%lld: %ld\n", N, counter);
	printf("Tempo de execução %.6f segundos \n", time);
	
	pthread_mutex_destroy(&mutex);
	free(tid);
	
	write_csv(time, nthreads);
	return 0;
}
