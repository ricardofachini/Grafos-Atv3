#include "grafo.h"

int main() {
    Grafo *grafo1 = new Grafo("fluxo.net"); // passar como parâmetro o arquivo de grafo
    grafo1->edmonds_karp(1, 2); // colocar a origem e sorvedouro como parâmetros aqui
    delete grafo1;
    return 0;
}