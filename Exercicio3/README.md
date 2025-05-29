# Relatório do Exercício 3:

## 1. Modo de Uso:

Adiocionei a flag ```--print``` para printar resultados intermediários de cada thread consumidora, indicando qual primo ela encontrou e depois de terminar, quantos primos ela encontrou.
```
gcc -o primos primos.c -lm
./primos <N> <M> <C> [--print]
```

## 2. Implementação:

Para a implementação do padrão produtor-consumidor usando semáforos como mecanismo de sincronização, é necessário a criação de um buffer de tamanho arbitrariamente pequeno $M$ para armazenar os números da sequência $1-N$ que queremos verificar primalidade. Para sinalizar que a única thread produtora terminou de inserir a sequência no buffer, o produtor adiciona um valor $-42$ uma vez para cada thread consumidora, indicando que não há mais itens a serem processados pelos consumidores.

Além disso, a sincronização é dada pelos semáforos a seguir:

* **slotVazio**: Controla a quantidade de posições vazias no buffer.
* **slotCheio**: Controla a quantidade de itens disponíveis para consumo. 
* **mutexCons**: Como temos $C$ threads consumidoras, o mutexCons é um semáforo binário que garante que apenas uma thread consumidora leia do buffer por vez.

OBS: Não é necessário **mutexProd** para a exclusão mútua de produtores, porque já foi definido no enunciado que existe apenas uma única thread produtora, isso é, não existe concorrência na operação de escrita.

Cada thread consumidora, ao retirar um item, verifica se ele é primo e, caso seja, incrementa seu contador individual de primos na posição do vetor (**contPrimos[thread_id]++**). A flag ```--print``` na linha de comando permite ativar ou desativar os prints detalhados do funcionamento, como quais números foram encontrados por cada thread e quando cada uma finaliza sua execução, além de quais primos cada uma encontrou em cada vez.

Após o término de todas as threads, o programa calcula o total de primos encontrados e determina qual thread "venceu", ou seja, qual delas encontrou o maior número de primos.

## 3. Testes:

OBS: Os ids de threads consumidoras começam no $1$.
### 3.1. Para $N = 10$:

Sejam $M=4$ e $C=4$
```
Numero de primos encontrados: 4
Thread vencedora: Consumidor 1 que encontrou 3 primos
```
Sejam $M=4$ e $C=12$
```
Numero de primos encontrados: 4
Thread vencedora: Consumidor 1 que encontrou 3 primos
```

Em casos pequenos como este, observa-se que a thread que inicia primeiro tende a consumir praticamente todos os itens do buffer antes que as demais consigam competir. Isso ocorre devido à baixa quantidade de itens e à velocidade com que os primeiros consumidores atuam.

### 3.2. Para $N = 100$:

Sejam $M=10$ e $C=4$
```
Numero de primos encontrados: 25
Thread vencedora: Consumidor 1 que encontrou 22 primos
```

```
Numero de primos encontrados: 25
Thread vencedora: Consumidor 1 que encontrou 14 primos
```

Ainda assim, vemos uma dominância das threads que iniciam primeiro, apesar de ser perceptível uma certa mudança na quantidade de primos encontrados pela thread vencedora.

## 3.3. Para $N=10000$:

Sejam $M=25$ e $C=15$

```
Numero de primos encontrados: 1229
Thread vencedora: Consumidor 8 que encontrou 102 primos
```

```
Numero de primos encontrados: 1229
Thread vencedora: Consumidor 9 que encontrou 98 primos
```

```
Numero de primos encontrados: 1229
Thread vencedora: Consumidor 3 que encontrou 117 primos
```

Com uma sequência maior e mais threads concorrendo, observa-se uma variação natural nas threads vencedoras, além de uma distribuição mais equilibrada na quantidade de primos encontrados.

* Resultado com flag ```[--print]```: 

Pra entender melhor como as threads se comportam, foi utilizada a flag `--print` durante a execução com os parâmetros $$N = 10000$$, $$M = 25$$ e $$C = 15$$. Mesmo tendo uma thread vencedora, dá pra perceber que as outras não ficam muito atrás, mostrando que o trabalho acabou ficando bem distribuído entre os consumidores, especialmente quando tem mais concorrência e mais números pra processar. Segue abaixo um trecho da saída do programa:

```
...
Thread Consumidora 15 encontrou o primo 9857
Thread Consumidora 13 encontrou o primo 9859
Thread Consumidora 9 encontrou o primo 9883
Thread Consumidora 1 encontrou o primo 9901
Thread Consumidora 8 encontrou o primo 9907
Thread Consumidora 10 encontrou o primo 9887
Thread Consumidora 12 encontrou o primo 9871
Thread Consumidora 12 encontrou o primo 9929
Thread Consumidora 10 encontrou o primo 9931
Thread Consumidora 9 encontrou o primo 9941
Thread Consumidora 3 encontrou o primo 9923
Thread Consumidora 14 encontrou o primo 9949
Thread Consumidora 4 encontrou o primo 9967
Thread Consumidora 6 encontrou o primo 9973
Thread Consumidora 7 terminou. Encontrou 84 numeros primos.
Thread Consumidora 15 terminou. Encontrou 74 numeros primos.
Thread Consumidora 8 terminou. Encontrou 90 numeros primos.
Thread Consumidora 2 terminou. Encontrou 78 numeros primos.
Thread Consumidora 10 terminou. Encontrou 74 numeros primos.
Thread Consumidora 9 terminou. Encontrou 79 numeros primos.
Thread Consumidora 11 terminou. Encontrou 88 numeros primos.
Thread Consumidora 13 terminou. Encontrou 85 numeros primos.
Thread Consumidora 12 terminou. Encontrou 100 numeros primos.
Thread Consumidora 1 terminou. Encontrou 79 numeros primos.
Thread Consumidora 6 terminou. Encontrou 81 numeros primos.
Thread Consumidora 4 terminou. Encontrou 83 numeros primos.
Thread Consumidora 5 terminou. Encontrou 69 numeros primos.
Thread Consumidora 14 terminou. Encontrou 88 numeros primos.
Thread Consumidora 3 terminou. Encontrou 77 numeros primos.


Numero de primos encontrados: 1229
Thread vencedora: Consumidor 12 que encontrou 100 primos
```
