# Exercício 1:
## Guilherme Cappelli Bouzon de Amorim Cruz
## DRE: 121170269
## OBS: RELATÓRIO COMPLETO NO PDF DENTRO DESSE REPOSITÓRIO

## 1. Produto Interno com Threads
Modo de uso: 

```
gcc -o prod_thread prod_thread.c
./prod_thread -p <nthreads> <arquivo.bin>
```

onde a flag -p indica se será printado os resultados parciais de cada thread.

## 2. Gerando vetores aleatórios
```
gcc -o gen gen.c
./gen <dim> <arquivo_a_ser_criado.bin>
```
Os arquivos gerados para teste se encontram na pasta binarios_testes.

## 3. Automatizando testes:

Para gerar testes mais aleatórios e verificar funcionamento, elaborei um script em bash para executar ambos os códigos em C e comparar resultados no terminal.

```
chmod +x gen_v.sh
./gen_v.sh -p
./gen_v.sh
```

novamente -p indica se quer imprimir os valores parciais das threads.

Observe que o script executa ambos os programas C e escreve rand_{i}.bin para $1 \leq i \leq 10$ arquivos binários requisitados no enunciado do exercício no direatório em que o script se encontra, contendo dimensão dos vetores, vetor 1, vetor 2 e produto interno sequencial, respectivamente.
