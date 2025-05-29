# Relatório do Exercício 2:

# OBS: A análise de resultados se encontra neste README.md

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
* Para $N = 10$:

Sejam $M=4$ e $C=4$:
```
Numero de primos encontrados: 4
Thread vencedora: Consumidor 1 que encontrou 3 primos
```
Sejam $M=4$ e $C=12$:
```
Numero de primos encontrados: 4
Thread vencedora: Consumidor 1 que encontrou 3 primos
```

Rodando casos pequenos, não é perceptível uma mudança na thread vencedora. Isso ocorre provavelmente pela pouca quantidade de itens no buffer, que faz com que as primeiras threads iniciadas consumam rapidamente os elementos disponíveis antes que as outras consigam competir.

* Para $N = 100$
* Resultados com flag ```[--print]```: 

```
Thread Consumidora 1 encontrou o primo 2
Thread Consumidora 1 encontrou o primo 5
Thread Consumidora 1 encontrou o primo 7
Thread Consumidora 1 terminou. Encontrou 3 numeros primos.
Thread Consumidora 2 encontrou o primo 3
Thread Consumidora 2 terminou. Encontrou 1 numeros primos.

Numero de primos encontrados: 4
Thread vencedora: Consumidor 1 que encontrou 3 primos

Numero de primos encontrados: 4
Thread vencedora: Consumidor 1 que encontrou 3 primos
```
