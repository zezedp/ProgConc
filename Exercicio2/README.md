# Relatório do Exercício 2:

# OBS: A análise de resultados se encontra neste README.md

## 1. Modo de Uso:

```
gcc -o prime prime.c -lm
./prime <nthreads> <N>
```

### 1.2. Script para executar prime várias vezes

```
chmod +x script.sh
./script.sh
```

### 1.3. Cálculo de Aceleração e Eficiência e Plot dos Gráficos
```
python3 plot.py
```


## 2. Implementação:

Diferentemente do Exercício 1, neste código, a distribuição de carga entre as threads é feita através da variável compartilhada **next**, que representa o pŕoximo número que a thread deve verificar a primalidade.

Inicialmente, **next=1** e, à medida que as threads são criadas, cada uma entra no loop da função **prime_sequence** e tenta verificar a primalidade dos números. Cada thread verifica um número da sequência de 1 até $N$ e para isso, a thread pega sempre o próximo número disponível, usando a variável compartilhada *next*.

A variável **local** é utilizada para armazenar o valor de **next** antes de ele ser incrementado. Isso garante que cada thread tenha um número único para verificar se é primo, pois esse **local** não é compartilhado, na verdade é uma variável local dentro da função.

Contudo, depois da thread selecionar o número **next**, entramos numa seção crítica, pois incrementamos **next++**. Para lidar com isso, usamos o mutex para garantir que somente uma thread vá manipular essa variável por vez. Ao finalizar essa manipulação, liberamos o mutex para que a próxima thread tenha  acesso a seção crítica.

O loop **while** em **prime_sequence** permite que as threads continuem a procurar números até que todos da sequência 1-N tenham sido verificados. O **while** permanece funcionando até que a variável **next** seja maior que **N**, o que indica que os números da sequência 1-N esgotaram. Dentro do loop, cada thread pega o próximo número  disponível, armazena em **local**, incrementa **next** e, em seguida, verifica se **local** é primo.

A função isPrime é chamada com o parâmetro do número da sequência que a thread atual quer descobrir se é primo. Se o número for primo, a thread precisa bloquear o mutex novamente, pois incrementaremos o contador global de números primos na sequência. Após a linha do **counter++** ser executada, podemos liberar o mutex com o 'unlock', finalizando assim a última seção crítica.

Para analisarmos os resultados em gráficos, implementei a função que escreve em um arquivo .csv o tempo de execução com colunas N, Nthreads, Tempo(s), Primo(s) Encontrado(s), de forma que se o arquivo estiver vazio, ele adiciona a linha com essas categorias, mas caso já existam dados no .csv, ele vai apenas adicionar à ultima linha do arquivo sem sobrescrever dados passados.

## 3. Resultados:

Configurações:

* CPU: AMD Ryzen 5 3600 6-Core (12 threads)

* Placa de Vídeo: GTX 1660 Super (6 GiB)

* Memória: 16 GiB DDR4

O programa foi executado para os seguintes valores de entrada:

* **Tamanhos de entrada (N):** 1000, 10000, 100000 e 1000000
* **Números de threads:** 1, 2, 4 e 8.

Para cada configuração, o programa foi rodado 10 vezes e o tempo de execução guardado em um arquivo .csv para tirarmos a média aritmética dessas amostras. A partir disso, essas médias são usadas para calcular a **aceleração** e **eficiência**:

* Aceleração:  Mede o quanto um programa fica mais rápido à medida que aumentamos o número de threads comparado com a execução de uma única thread.

É dada pela razão entre o tempo de execução do programa sequencial - que nesse caso será fornecido pela execução de 1 thread - e o tempo de execução com múltiplas threads.

$$
A = \frac{T_{seq}}{T_{n\_{threads}}}
$$

* Eficiência: Mede o quanto cada thread adicional contribui para a aceleração do programa. Essencialmente, a métrica busca explicitar se o uso de múltiplas threads está trazendo resultados proporcionais, isto é, contribuindo para o desempenho.

$$
E = \frac{A}{n\_{threads}}
$$

Para isso, calculamos para cada configuração $(N, n\_threads)$ suas respectivas acelerações e eficiências.

### 3.1. Tempo de Execução:

![plot1](./graficos/tempo_execucao_por_threads.png)

Nesse gráfico, observamos que para valores pequenos de N, a redução do tempo de execução é minúscula. Mesmo para N=10^5, a melhoria do tempo de execução ao comparar a versão sequencial com o uso de 2 threads é razoável, mas, para outros valores de N menores que 10^5, o tempo de execução permanece praticamente constante, independentemente do número de threads utilizadas. 
Já para N = 10^6, percebe-se uma redução significativa no tempo de execução ao passar do sequencial para 2 threads, seguida de uma nova diminuição ao passarmos para 4 threads. No entanto, a melhoria ao aumentar para 8 threads não é tanta quanto as anteriores, apesar de diminuir o tempo de execução.

Isso nos diz que para valores de N maiores, a concorrência começa a mostrar seus benefícios, visto que com o aumento de N, o programa sequencial se torna mais custoso, permitindo que a adoção de múltiplas threads ajude numa redução maior do tempo total de execução, superando assim o overhead de inicialização e sincronização de threads.

### 3.2. Aceleração:

![plot2](./graficos/aceleração_por_threads.png)

Percebe-se que para valores pequenos de N, como 1000 e 10000, a utilização de múltiplas threads não nos ajudou, porque resultou em uma piora no desempenho. Conforme o número de threads aumenta, para esses valores de N, a aceleração diminui, porque o tempo gasto na criação e sincronização das threads é significativo comparado com o tempo de processamento verdadeiro, ou seja, esse overhead impede um ganho de performance nessa execução paralela.

Para valores maiores de N, como 10^5 e 10^6, observamos uma mudança no comportamento da gráfico, porque para 10^6 há um aumento significativo na aceleração ao usarmos duas threads, e ainda mais quando adotamos quatro ou oito threads. Entretanto, em um cenário ideal, a aceleração deveria se aproximar do número de threads, que não ocorre quando analisamos o aumento de threads para valores de N abaixo de 10^5 (incluso), visto que o ganho de velocidade é inferior à ele. Nesse caso, alguns dos fatores que podem estar limitando essa performance além do overhead de inicialização das threads e o mutex, é que recursos como memória e cache são compartilhados, e portanto outros processos competem pelo seu uso.

### 3.3. Eficiência:

![plot3](./graficos/eficiência_por_threads.png)


Para valores pequenos de N, a eficiência cai rapidamente à medida que aumentamos o número de threads, que pode ser um indicador de que o custo desse manejo de threads é maior que os ganhos da divisão de carga de trabalho entre as threads. Isso se deve ao fato de que o tempo de execução já é pequeno sequencialmente e o overhead da concorrência supera ele.

Conforme aumentamos os valores de N nos testes, a eficiência se torna melhor comparado com valores de N's pequenos, porque para N=10^6, por exemplo, pelo tempo de processamento ser maior que os outros, o uso de múltiplas threads compensa o overhead da concorrência ao dividir a carga de trabalho entre as threads. Entretanto, ainda assim, a eficiência cai conforme aumentamos o número de threads. 

Assim, percebemos que o uso de threads causa uma melhora na performance quando N for grande o suficiente, além de que o uso excessivo de threads em problemas com N pequeno acarreta em desperdício de recursos.

