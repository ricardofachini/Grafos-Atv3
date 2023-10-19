#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <stdint.h>
#include <string>
#include <iostream>
#include <map>
#define INFINITO INT32_MAX


/* Grafo não dirigido e ponderado */
class Grafo
{
    public:
        Grafo(std::string arquivo);  // construtor
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
    private:
        std::vector<int> vertices;
        std::map<std::pair<int, int>, int> arestas;

};
#endif

