### Relatório (APENAS PARTE DA ATIVIDADE 1)
#### Nome: Guilherme Cappelli Bouzon de Amorim Cruz. DRE: 121170269

O código ```MyPool.java``` implementa um pool de threads utilizando o FilaTarefas, que gerencia uma fila compartilhada de tarefas. Assim, dentro de um número fixo de threads, múltiplas tarefas podem ser executadas concorrentemente e permanecem em execução até que todas as tarefas sejam encerradas.

A classe ```FilaTarefas``` cria as n threads que ficam em aguardo (wait()) até que novas tarefas sejam adicionadas à fila. Cada vez que uma nova tarefa é submetida com o ```execute```, uma das threads é notificada notify() para tirar ela da fila e ser executada. 

A primeira tarefa já implementada no código fornecido imprime uma mensagem no console ```Hello da tarefa {i}``` e a partir desse valor $i$ do laço 'for' a segunda tarefa verifica se esse número é primo. Nesse contexto, múltiplas tarefas são processadas paralelamente pelas threads que estão disponíveis, que possui um desempenho melhor que uma versão sequencial desse programa.

Já o metodo ```shutdown()`` assegura que as threads sejam encerradas de forma ordenada, evitando assim que as threads fiquem em espera indefinidamente.
