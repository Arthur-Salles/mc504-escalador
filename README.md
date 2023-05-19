# Programa Multithread

O repositorio contém o código para a execução do projeto do primeiro modulo da disciplina de MC504 - Sistemas Operacionais

## Overview

O objetivo deste projeto é adaptar e melhorar o problema do barbeiro dorminhoco. Utilizando threads e semaforos.

## Instrucoes CMake

CMake automatiza o processo de construcao.
O arquivo `CMakeLists.txt` descreve como encontrar e linkar o programa com a biblioteca do pthreads.

## Como Rodar

Apos clonar o repositorio, run:

```sh
 mkdir build
 cd build
 cmake ..
 make
```
Isso irá criar os executáveis na pasta build. Para compilar, rode `make`

Para a visualização foi gerado um log com o programa em C. E a visualização foi construída por cima do log em Swift.

## Construcao do Projeto

Como dito anteriormente este trabalho é uma adaptação do problema do barbeiro dorminhoco. O trabalho conta a realidade da academia OitoEncaixes que se situa no bairro de Marquês Geraldo, em uma realidade alternativa.

Assim como todas academias de rede, ela se aproveita de que grande parte dos que estão matriculados não comparecem a academia, ou seja, não possui infraestrutura para atender a todos inscritos. Porém com o poder dos influencers, todos os moradores do bairro Marquês Geraldo resolveram ir a OitoEncaixes causando o caos na academia.

Porém em Marquês Geraldo, as leis que governam os marombeiros são diferentes do mundo em que vivemos. Sendo elas:

1. Todos fazem os mesmos exercícios, afinal o shape é um só.
2. Como treinam muito pesado, é preciso fazer somente uma série para cada exercício.
3. Todos são extremamente ratos de academia, ou seja, não saem da academia até fazerem todos exercícios.
4. Não respeitam a ordem da ficha, se for preciso pular a ordem do exercício, o farão.
5. São muito metodologicos com o treino, isto é, ao entrar na máquina só saem até completarem a série.
6. Respeitam o distanciamento social, isto é , se a academia está cheia eles vão embora.

Para adequar-se as necessidades do povo de Marquês Geraldo, a Oito Encaixes possui:

1. Um monitor que avisa a capacidade disponível da academia na porta.
2. Possuem `M` máquinas para os `N` exercícios na ficha dos marombeiros. 
