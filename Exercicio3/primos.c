#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <string.h>

sem_t mutexCons, slotCheio, slotVazio;
int* Buffer, N, M, C;
int *contPrimos;
int FLAG_PRINT = 0;
int ehPrimo(long long int n){
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (long long int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void Insere(int item){
        static int in = 0;
        sem_wait(&slotVazio);
        Buffer[in] = item;
        in = (in + 1) % M;
        sem_post(&slotCheio);
}

int Retira(void){
        int item;
        static int out = 0;
        sem_wait(&slotCheio);
        sem_wait(&mutexCons);
        item = Buffer[out];
        out = (out + 1) % M;
        sem_post(&mutexCons);
        sem_post(&slotVazio);
        return item;
}

void *produtor(void* arg){
        for (int i = 1; i <= N; ++i) Insere(i);
        for (int i = 0; i < C; ++i) Insere(-42);
        pthread_exit(NULL);
}

void *consumidor(void* arg){
        long int id = (long int) arg;
        contPrimos[id] = 0;
        while (1){
                int item = Retira();
                if (item == -42) break;

                if (ehPrimo(item)){
                        contPrimos[id]++;
                        if (FLAG_PRINT) printf("Thread Consumidora %d encontrou o primo %d\n", id+1, item);
                }
        }
        if (FLAG_PRINT) printf("Thread Consumidora %d terminou. Encontrou %d numeros primos.\n", id+1, contPrimos[id]);
        pthread_exit(NULL);
}

int main(int argc, char* argv[]){
        // 1 THREAD PRODUTORA
        // C THREADS CONSUMIDORAS
        // N INTEIROS NA SEQUENCIA
        // BUFFER DE TAMANHO M
        if (argc < 4 || argc > 5){
                printf("Modo de uso: %s <1 ATÉ ?> <tamanho buffer> <nthreads consumidoras> [--print]", argv[0]);
                exit(-1);
        }
        N = atoi(argv[1]);
        M = atoi(argv[2]);
        C = atoi(argv[3]);

        if (argc == 5 && strcmp(argv[4], "--print") == 0) FLAG_PRINT = 1;
        Buffer = (int *) malloc(M *sizeof(int));
        contPrimos = (int *) malloc(C*sizeof(int));

        if (Buffer == NULL || contPrimos == NULL) {
                perror("Erro no malloc()\n");
                exit(EXIT_FAILURE);
        }

        sem_init(&mutexCons, 0, 1);
        sem_init(&slotCheio, 0, 0);
        sem_init(&slotVazio, 0, M);

        pthread_t tidProd;
        pthread_t tidCons[C];


        if (pthread_create(&tidProd, NULL, produtor, NULL)){
                perror("ERRO: pthread_create Produtor");
                exit(EXIT_FAILURE);
        }

        for (long int i = 0; i < C; ++i){
                if (pthread_create(&tidCons[i], NULL, consumidor, (void*) i)){
                        perror("ERRO: pthread_create() Consumidor\n");
                        exit(EXIT_FAILURE);
                }
        }

        if (pthread_join(tidProd, NULL)){
                perror("ERRO: pthread_join Produtor");
                exit(EXIT_FAILURE);
        }

        for (int i = 0; i < C; ++i){
                if (pthread_join(tidCons[i], NULL)){
                        perror("ERRO: pthread_join\n");
                        exit(EXIT_FAILURE);
                }
        }

        int primos = 0;
        int thread_vencedora = 0;

        for (int id = 0; id < C; ++id){
                primos += contPrimos[id];
                if (contPrimos[id] > contPrimos[thread_vencedora]){
                        thread_vencedora = id;
                }
        }
        if (FLAG_PRINT) printf("\n");
        printf("Numero de primos encontrados: %d\n", primos);
        printf("Thread vencedora: Consumidor %d que encontrou %d primos\n", thread_vencedora+1, contPrimos[thread_vencedora]);

        sem_destroy(&mutexCons);
        sem_destroy(&slotCheio);
        sem_destroy(&slotVazio);
        free(Buffer);
        free(contPrimos);
        return 0;
}

