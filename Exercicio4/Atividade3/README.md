### Relatório (APENAS DA ATIVIDADE 3)
#### Nome: Guilherme Cappelli Bouzon de Amorim Cruz. DRE: 121170269

Nesse código, criamos um pool de threads fixo que executa tarefas assíncronas com uso de ```Future```. Nessa atividade, contamos quantos números primos têm em um conjunto de números ${1, \dots, N}$ dividindo o problema em blocos indepentens de trabalho.

A classe ```PrimoCheckerBlocos```implementa a interface ```Callable<Integer>```e recebe um intervalo (```start``` e ```end```) para verificar quantos primos têm nesse chunk. Cada instância da tarefa é submetida ao executor por meio do ```submit()```, que vai retornar um objeto do tipo ```Future<Integer>``` armazenados em seguida em um lista para coletar os resultados.

Nesse sentido, a thread principal pode continuar trabalhando enquanto as tarefas são processadas em paralelo. No final, a função ```get()``` de cada ```Future``` é chamada para recuperar o valor retornado por cada bloco e a soma desses valores nos informa o total de primos no conjunto de $1-N$.

Vale ressaltar, que a divisão em chunks reduz o overhead de criação de tarefas e melhora a performance, pois cada thread executa mais trabalho por tarefa.

```
N = 1000
Tamanho da list = 10
Quantidade de primos entre 1-N: 359
```
