### Relatório (APENAS PARTE DA ATIVIDADE 1)
#### Nome: Guilherme Cappelli Bouzon de Amorim Cruz. DRE: 121170269

O código ```MyPool.java``` implementa um pool de threads utilizando o FilaTarefas, que gerencia uma fila compartilhada de tarefas. Assim, dentro de um número fixo de threads, múltiplas tarefas podem ser executadas concorrentemente e permanecem em execução até que todas as tarefas sejam encerradas.

A classe ```FilaTarefas``` cria as n threads que ficam em aguardo (wait()) até que novas tarefas sejam adicionadas à fila. Cada vez que uma nova tarefa é submetida com o ```execute```, uma das threads é notificada notify() para tirar ela da fila e ser executada. 

A primeira tarefa já implementada no código fornecido imprime uma mensagem no console ```Hello da tarefa {i}``` e a partir desse valor $i$ do laço 'for' a segunda tarefa verifica se esse número é primo. Nesse contexto, múltiplas tarefas são processadas paralelamente pelas threads que estão disponíveis, que possui um desempenho melhor que uma versão sequencial desse programa.

Já o metodo ```shutdown()``` assegura que as threads sejam encerradas de forma ordenada, evitando assim que as threads fiquem em espera indefinidamente.

#### Saída no conjunto $\{0, \dots, 24\}$:

```
Hello da tarefa 0
Hello da tarefa 4
Hello da tarefa 5
Hello da tarefa 6
0 não é primo.
2 é primo.
4 não é primo.
6 não é primo.
8 não é primo.
Hello da tarefa 9
9 não é primo.
Hello da tarefa 10
10 não é primo.
Hello da tarefa 11
11 é primo.
Hello da tarefa 12
12 não é primo.
Hello da tarefa 13
Hello da tarefa 3
Hello da tarefa 14
Hello da tarefa 2
Hello da tarefa 15
Hello da tarefa 1
Hello da tarefa 16
15 não é primo.
Hello da tarefa 17
14 não é primo.
Hello da tarefa 18
13 é primo.
Hello da tarefa 19
Hello da tarefa 8
Hello da tarefa 20
7 é primo.
Hello da tarefa 21
21 não é primo.
Hello da tarefa 22
22 não é primo.
Hello da tarefa 23
5 é primo.
Hello da tarefa 24
3 é primo.
Hello da tarefa 7
1 não é primo.
24 não é primo.
23 é primo.
20 não é primo.
19 é primo.
18 não é primo.
17 é primo.
16 não é primo.
Terminou
```
