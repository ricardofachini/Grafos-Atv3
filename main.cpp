#include "grafo.h"

int main() {
    Grafo *grafo1 = new Grafo("fluxo.net"); // passar como parâmetro o arquivo de grafo
    //Grafo grafo_bipartido = Grafo("pequeno.net");
    grafo1->item_1(1, 4); // item 1 da atividade, com Edmonds-Karp
    //grafo1->edmonds_karp(1, 2, nullptr); // colocar a origem e sorvedouro como parâmetros aqui
    delete grafo1;
    return 0;
}