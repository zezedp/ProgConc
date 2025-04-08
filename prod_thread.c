#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double *v1, *v2;
long int dim, nthreads;
int exibir_threads;
double var_relativa(double prod_thread, double prod_seq){
	double e = (prod_seq - prod_thread) / prod_seq;
	if (e<0) return -e;
	return e;
}

void* produto_interno(void* arg) {
    long int tid = (long int) arg;
    long int start, end, chunk;
    double* soma_local = (double*) malloc(sizeof(double));
    if (soma_local == NULL) {
        fprintf(stderr, "ERRO malloc() thread %ld\n", tid);
        pthread_exit(NULL);
    }
    // Calcula quantos elementos dos vetores cada thread vai cuidar
    // determinando onde cada thread começa e termina (em posições dos vetores) para balancear a carga de trabalho
    chunk = dim / nthreads;
    start = tid * chunk;
    if (tid == nthreads-1) end = dim;
    else end = start + chunk;

    *soma_local = 0.0;
    for (long int i = start; i < end; ++i) {
        *soma_local += v1[i] * v2[i];
    }
    // Retorna produto interno parcial
    pthread_exit((void*) soma_local);
}

int main(int argc, char* argv[]) {
    int opt;
    // Gerencia flag -p, para exibir resultados parciais das flags.
    while ((opt = getopt(argc, argv, "p")) != -1) {
    	switch (opt) {
		case 'p':
		    exibir_threads = 1;
		    break;
		default:
		    fprintf(stderr,"Uso: %s [-p] <nthreads> <arquivo.bin>\n");
		    exit(EXIT_FAILURE);
	}
    }

    // Verifica se inseriu os argumentos necessários
    if (argc - optind != 2) {
    	fprintf(stderr, "Uso: %s [-p] <nthreads> <arquivo.bin>\n");
    }    
    
    // Declara variáveis
    double produto_sequencial, e;
    nthreads = atol(argv[optind]);
    FILE* ptr_file = fopen(argv[optind+1], "rb");
    // Verifica se deu erro no fopen()
    if (ptr_file == NULL) {
        perror("ERRO: fopen()");
        return -1;
    }
   
    size_t r = fread(&dim, sizeof(long int), 1, ptr_file);
    // Verifica leitura da dimensão dos vetores
    if (!r) {
        fprintf(stderr, "ERRO na leitura da dimensão dos vetores.\n");
        return -1;
    }

    v1 = (double*) malloc(sizeof(double) * dim);
    v2 = (double*) malloc(sizeof(double) * dim);
    
    // Verifica alocacao dos vetores 1 e 2
    if (!v1 || !v2) {
        fprintf(stderr, "ERRO: malloc() vetores\n");
        return -1;
    }

    r = fread(v1, sizeof(double), dim, ptr_file);
    size_t t = fread(v2, sizeof(double), dim, ptr_file);
    // Verifica leitura dos vetores 1 e 2
    if (!r || !t) {
        fprintf(stderr, "ERRO de leitura dos vetores\n");
        return -1;
    }
    r = fread(&produto_sequencial, sizeof(double), 1, ptr_file);
    
    // Verifica leitura do produto interno SEQUENCIAL feito no gen.c
    if (!r){
    	fprintf(stderr, "ERRO de leitura do produto interno sequencial");
	exit(-1);
    }
    fclose(ptr_file);
    
    // Começa parte das threads
    pthread_t* sys_tid = (pthread_t*) malloc(sizeof(pthread_t) * nthreads);
    void* retorno;
    double produto_final = 0.0;
    
    // Criando threads para executar produto_interno(), passando como argumento o id=0 até nthreads-1
    for (long int i = 0; i < nthreads; ++i) {
        if (pthread_create(&sys_tid[i], NULL, produto_interno, (void*) i)) {
            fprintf(stderr, "ERRO no pthread_create\n");
            return -1;
        }
    }

    // Espera resultados parciais das threads, ou ainda, espera o retorno das threads
    for (long int i = 0; i < nthreads; ++i) {
        if (pthread_join(sys_tid[i], &retorno)) {
            fprintf(stderr, "ERRO no pthread_join\n");
            return -1;
        }
        double* prod_parcial = (double*) retorno;
	// Verifica se flag -p foi passada no ./prod_thread
        if (exibir_threads) { 
		printf("Thread %ld retornou %lf \n", i, *prod_parcial);
	}
	// Adiciona prod_parcial das threads ao produto_final total
	produto_final += *prod_parcial;
        free(prod_parcial);
    }
    printf("Produto interno (THREADS): %.35lf\n", produto_final);
    printf("Produto interno (SEQUENCIAL): %.35lf\n", produto_sequencial);
    e = var_relativa(produto_sequencial, produto_final);

    free(v1);
    free(v2);
    free(sys_tid);
    printf("Variacao Relativa: %.35lf\n", e);
    return 0;
}
