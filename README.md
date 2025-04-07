# Exercício 1:

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

## 3. Automatizando testes:

Para gerar testes mais aleatórios e verificar funcionamento, elaborei um script em bash para executar ambos os códigos em C e comparar resultados no terminal.

```
chmod +x gen_v.sh
./gen_v.sh
```
