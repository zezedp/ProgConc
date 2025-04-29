#!/bin/bash

threads=(1 2 4 8)
numeros=(1000 10000 100000 1000000)

for n in "${numeros[@]}"; do
	for t in "${threads[@]}"; do
		for i in {1..10}; do
			echo "Executando ./prime $t $n (execução $i)"
			./prime "$t" "$n"
			sleep 1
		done
	done
done
