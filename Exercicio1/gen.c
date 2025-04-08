#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    long int dim;
    double *v1, *v2, prod_int = 0.0;
    
    if (argc != 3){
    	printf("Uso: %s <dimensao> <arquivo.bin>\n", argv[0]);
    	exit(-1);
    }
    
    dim = atol(argv[1]);
    FILE* f = fopen(argv[2], "wb");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return 1;
    }
    
    v1 = malloc(sizeof(double) * dim);
    v2 = malloc(sizeof(double) * dim);
    srand(time(NULL)+ getpid());
    for (int long i = 0; i < dim; ++i){
    	v1[i] = 110 + ((double) rand() / RAND_MAX) * 31.0;
	v2[i] = 40 + ((double) rand() / RAND_MAX) * 20.0;
    }
     // Escreve a dimensão
    fwrite(&dim, sizeof(long int), 1, f);

    // Escreve os vetores
    fwrite(v1, sizeof(double), dim, f);
    fwrite(v2, sizeof(double), dim, f);

    for (long int i = 0; i < dim; ++i){
    	prod_int += v1[i] * v2[i];
    }

    fwrite(&prod_int, sizeof(double), 1, f);
    printf("Arquivo %s gerado com sucesso!\n", argv[2]);
    free(v1);
    free(v2);
    fclose(f);
    return 0;
}
