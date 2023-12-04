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
        std::string rotulo(int vertice);

        std::vector<int> vizinhos(int vertice);
        bool haAresta(int u, int v);
        int peso(int u, int v);

        // algoritmos:

        // ATIVIDADE 3:
        // item 1
        void item_1(int fonte, int sorvedouro);
        int ford_fulkerson(int s, int t);
        int edmonds_karp(int s, int t, std::vector<std::vector<int>> &rede_residual);

        // item 2
        void hopcroft_karp();
        bool BFS(std::vector<int>& paresU, const std::vector<int>& paresV, std::vector<int>& distancias);
        bool DFS(int u, std::vector<int>& paresU, std::vector<int>& paresV, const std::vector<int>& distancias);
        int dist(int u) const;

        // item 3
        void coloracao();
    private:
        bool eh_dirigido = false;
        std::vector<std::pair<int, std::string>> vertices; // vetor de pares <indice, rotulo>
        std::vector<Aresta*> arestas; // vetor de ponteiros para arestas

        // SOMENTE PARA GRAFOS BIPARTIDOS:
        std::vector<std::pair<int, std::string>> verticesU; // Vértices do conjunto U
        std::vector<std::pair<int, std::string>> verticesV; // Vértices do conjunto V


};

class GrafoBipartido {
    public:
        //GrafoBipartido();
        //~GrafoBipartido();
        std::vector<std::pair<int, std::string>> verticesU; // Vértices do conjunto U
        std::vector<std::pair<int, std::string>> verticesV; // Vértices do conjunto V
        std::vector<Aresta*> arestas; // Arestas que conectam U a V

};
#endif

