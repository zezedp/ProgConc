/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 11 */
/* Codigo: Exemplo de uso de futures */
/* -------------------------------------------------------------------*/

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import java.util.ArrayList;
import java.util.List;

class PrimoCheckerBlocos implements Callable<Integer> {
        private final int start;
	private final int end;

        public PrimoCheckerBlocos(int start, int end){
                this.start = start;
		this.end = end;
        }

        public Integer call() throws Exception {
		int count = 0;
		for (int i = start; i <= end; ++i){
                	if (i < 2) continue;
			boolean ehPrimo = true;
                	for (int j = 3; j <= Math.sqrt(i); j+= 2){
                        	if (i % j == 0){
					ehPrimo = false;
					break;
				}
                	}
                	if (ehPrimo) count++;
		}
        	return count;
	}
	

}

//classe do método main
public class FutureBlocos  {
  private static final int N = 1000;
  private static final int NTHREADS = 10;

  public static void main(String[] args) {
    //cria um pool de threads (NTHREADS)
    ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
    //cria uma lista para armazenar referencias de chamadas assincronas
    List<Future<Integer>> list = new ArrayList<Future<Integer>>();
	
    int blocos = 10;
    int chunk = N / blocos;

    for (int i = 0; i < blocos; ++i) {

	int start = i * chunk + 1;
	int end = (i == blocos - 1) ? N : (i+1) * chunk;
	Callable<Integer> worker = new PrimoCheckerBlocos(start, end);
	Future<Integer> submit = executor.submit(worker);
	list.add(submit);
    }

    System.out.println("Tamanho da list = " + list.size());

    long sum = 0;
    for (Future<Integer> future : list) {
      try {
        sum += future.get(); //bloqueia se a computação nao tiver terminado
      } catch (InterruptedException e) {
        e.printStackTrace();
      } catch (ExecutionException e) {
        e.printStackTrace();
      }
    }
    System.out.println("Quantidade de primos entre 1-N: " + sum);
    executor.shutdown();
  }
}

