#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <deque>
#include <stdint.h>
#include <string>
#include <iostream>
#include <map>
#include <tuple>
#include "aresta.h"
#define INFINITO INT32_MAX


/* Grafo não dirigido e ponderado */
class Grafo
{
    public:
        Grafo(char *nome_arquivo);  // construtor
        ~Grafo(); // destrutor

        // retorna numero de vertices
        int qtdVertices();
        // retorna numero de arestas
        int qtdArestas();
        // retorna o grau de um vertice
        int grau(int vertice);
        int rotulo(int vertice);

        std::vector<int> vizinhos(int vertice);
        bool haAresta(int u, int v);
        int peso(int u, int v);

        // algoritmos:
        // item 2:
        void buscaLargura(int origem);

        // item 4
        void dijkstra(int origem);
        int encontrarDistanciaMinima(std::vector<int>& distancia, std::vector<int>& visitados);

        // item 5
        void floyd_warshall();
    private:
        std::vector<std::pair<int, int>> vertices; // vetor de pares <indice, rotulo>
        std::vector<Aresta*> arestas; // vetor de ponteiros para arestas

};
#endif

