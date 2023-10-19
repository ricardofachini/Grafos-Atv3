#include "grafo.h"


int main() {
    Grafo *grafo1 = new Grafo("cor3.net"); // passar como parâmetro o arquivo de grafo
    grafo1->buscaLargura(4); // exercicio 2: busca em largura -> origem como argumento
    grafo1->dijkstra(2); // exercicio 4: dijkstra -> origem como argumento
    grafo1->floyd_warshall(); // exercicio 5: floyd-warshall
    delete grafo1;
    return 0;
}