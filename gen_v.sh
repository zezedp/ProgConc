#!/bin/bash

# Códigos de cor ANSI
RED='\033[1;31m'
GREEN='\033[1;32m'
BLUE='\033[1;34m'
CYAN='\033[1;36m'
YELLOW='\033[1;33m'
RESET='\033[0m'

MOSTRAR_THREADS=0

if [ "$1" == "-p" ]; then
    MOSTRAR_THREADS=1
fi

for i in $(seq 1 10); do
    ARQ="rand_${i}.bin"

    DIM=$((500 + RANDOM % 4501))

    ./gen "$DIM" "$ARQ"

    NTHREADS=$((DIM / 20))

    echo -e "${CYAN}Rodando ./prod_thread com ${YELLOW}$NTHREADS threads${CYAN} no arquivo ${BLUE}$ARQ${CYAN} (dim = ${GREEN}$DIM${CYAN})...${RESET}"

    if [ "$MOSTRAR_THREADS" -eq 1 ]; then
        ./prod_thread -p "$NTHREADS" "$ARQ" | sed "s/Thread/${YELLOW}Thread${RESET}/g"
    else
        ./prod_thread "$NTHREADS" "$ARQ"
    fi

    echo -e "${RED}-----------------------------${RESET}"
done

