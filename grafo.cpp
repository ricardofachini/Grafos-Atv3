#include "grafo.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <bits/stdc++.h>

using namespace std;

// construtor, lê o arquivo
Grafo::Grafo(char *nome_arquivo)
{
    ifstream arquivo; // c++ stream para leitura de arquivo
    arquivo.open(nome_arquivo);
    string linha;

    // le o arquivo
    if (arquivo.is_open()) {
        bool le_vertice = false;
        bool le_aresta = false;
        while (arquivo) {
            getline (arquivo, linha); // carrega uma linha do arquivo na variável linha

            if (linha.find("*vertices") != string::npos) {  // verifica se a linha atual dita os vertices
                le_vertice = true;
                continue;
            }

            if (linha.find("*edges") != string::npos) { // verifica se a linha atual dita as arestas
                le_vertice = false;
                le_aresta = true;
                continue;
            }
            if (linha.find("*arcs") != string::npos) { // verifica se a linha atual dita os arcos
                le_vertice = false;
                le_aresta = true; // adicionar arco é igual adicionar aresta,
                eh_dirigido = true; // mas na hora de usar os arcos, como retornar seu peso ou direção vai mudar
                continue;
            }
            if (linha == "") {
                break;
            }

            if (le_vertice == true) {
                // adiciona vertice ao grafo
                string s;
                stringstream ss(linha);
            
                vector<string> v;
                while (getline(ss, s, ' ')) {
                    v.push_back(s);
                }
                pair<int, string> vertice;
                if (v.size() > 1) {
                    vertice.first = stoi(v[0]);
                    vertice.second = v[1]; 
                } else {
                    vertice.first = stoi(v[0]);
                    vertice.second = v[0];
                }
                vertices.push_back(vertice);
            }

            if (le_aresta == true) {
                // adiciona aresta ao grafo
                string s;
                stringstream ss(linha);
            
                vector<string> v;
                while (getline(ss, s, ' ')) {
                    v.push_back(s);
                }
                Aresta *aresta = new Aresta();
                aresta->vertice1 = stoi(v[0]);
                aresta->vertice2 = stoi(v[1]);
                aresta->peso = stoi(v[2]);
                arestas.push_back(aresta);
            }
        }
    }
    else {
        cerr << "erro ao abrir arquivo!\n";
        cerr << "erro: " << strerror(errno) << endl;
        throw(errno);
    }
}

// destrutor
Grafo::~Grafo() {
    // desaloca memória das arestas
    for (auto aresta: arestas) {
        delete aresta;
    }
}

// retorna o peso da aresta entre (int: u) e (int: v)
int Grafo::peso(int u, int v)
{
    int peso = 0;
    for (const Aresta *aresta: arestas) {
        if (!eh_dirigido) {
            if ((aresta->vertice1 == u && aresta->vertice2 == v) ||
                    (aresta->vertice1 == v && aresta->vertice2 == u)) {
                        peso = aresta->peso;
                        break;
            }
        }
        if (aresta->vertice1 == u && aresta->vertice2 == v) {
            peso = aresta->peso;
            break;
        }
    }
    if (peso == 0)  {
        return INFINITO;
    } else {
        return peso;
    }
}

int Grafo::qtdVertices()
{
    return vertices.size();
}

int Grafo::qtdArestas()
{
    return arestas.size();
}

string Grafo::rotulo(int v)
{
    for (auto& vertice: vertices) {
        if (vertice.first == v) {
            return vertice.second;
        }
    }
    return 0;
}

int Grafo::grau(int vertice)
{
    int grau = 0;
    for (const auto& aresta : arestas) {
        if (aresta->vertice1 == vertice || aresta->vertice2 == vertice) {
            grau++;
        }
    }
    return grau;
}

bool Grafo::haAresta(int u, int v)
{
    for (auto& aresta: arestas) {
        if ((aresta->vertice1 == u && aresta->vertice2 == v) || (aresta->vertice1 == v && aresta->vertice2 == u)) {
            return true;
        }
    }
    return false;
}

// retorna um vetor de indices dos vertices vizinhos ao v
vector<int> Grafo::vizinhos(int v)
{
    vector<int> vizinhos;
    for (auto& aresta: arestas) {
        if (aresta->vertice1 == v) {
            vizinhos.push_back(aresta->vertice2);
        }
        if (aresta->vertice2 == v) {
            vizinhos.push_back(aresta->vertice1);
        }
    }
    return vizinhos;
}


void Grafo::item_1(int fonte, int sorvedouro)
{
    // printa o fluxo encontrado por fordFulkerson com EdmondsKarp
    cout << "-- Algoritmo de Edmonds Karp --\n";
    int fluxo = ford_fulkerson(fonte, sorvedouro);
    cout << "Fluxo máximo encontrado: " << fluxo << endl;
}

int Grafo::ford_fulkerson(int s, int t)
{
    int fluxo_maximo = 0;
    int fluxo_aumentante;

    vector<vector<int>> capacidade_residual;
    capacidade_residual.resize(qtdVertices(), std::vector<int>(qtdVertices(), 0));
    // cria uma rede(grafo) residual com os arcos invertidos zerados
    for (auto *arco : this->arestas) {
        int u = arco->vertice1;
        int v = arco->vertice2;
        capacidade_residual[u-1][v-1] = arco->peso;
    }

    while ((fluxo_aumentante = edmonds_karp(s, t, capacidade_residual)) > 0) {
        fluxo_maximo += fluxo_aumentante;
        cout << "fluxo aumentante " << fluxo_aumentante << endl;
    }
    return fluxo_maximo; // fluxo maximo encontrado
}

int Grafo::edmonds_karp(int s, int t, vector<vector<int>> &capacidade_residual) {
    //s: source/origem
    //t: sorvedouro ou sink

    deque<int> fila; // C
    vector<int> visitados; // Q
    vector<int> predecessores(vertices.size(), 0); // A
    int fluxo = 0;
    visitados.push_back(s);
    fila.push_back(s);

    while (!fila.empty()) {
        //fila nao vazia
        int u = fila.front();
        fila.pop_front();

        auto vizinhos_de_u = vizinhos(u);
        for (auto& v: vizinhos_de_u) {
            if ((find(visitados.begin(), visitados.end(), v) == visitados.end()) && (capacidade_residual[u-1][v-1] > 0)) {
                visitados.push_back(v);
                predecessores[v-1] = u;

                // encontrar o sink
                if (v == t) {
                    int capacidadeAumentante = numeric_limits<int>::max();
                    deque<int> p{t}; // caminho aumentante
                    int w = t;

                    while (w != s) {
                        int u = predecessores[w-1];
                        capacidadeAumentante = min(capacidadeAumentante, capacidade_residual[u-1][w-1]);
                        p.push_front(w);
                        w = u;
                    }
                    w = t;

                    while (w != s) {
                        int u = predecessores[w-1];
                        capacidade_residual[u-1][w-1] -= capacidadeAumentante;
                        capacidade_residual[w-1][u-1] += capacidadeAumentante;
                        w = u;
                    }
                    return capacidadeAumentante;
                }
                fila.push_back(v);
            }
        }
    }
}


bool Grafo::BFS(std::vector<int>& paresU, const std::vector<int>& paresV, std::vector<int>& distancias) {
        std::queue<int> fila;

        // Inicializa distâncias para vértices em U não emparelhados
        for (long unsigned int u = 0; u < verticesU.size(); ++u) {
            if (paresU[u] == -1) {
                distancias[u] = 0;
                fila.push(u);
            }
        }

        // Executa busca em largura
        while (!fila.empty()) {
            int u = fila.front();
            fila.pop();

            for (const auto& aresta : arestas) {
                if (aresta->vertice1 == u) {
                    int v = aresta->vertice2;
                    if (paresV[v] == -1) {
                        return true; // Caminho aumentante encontrado
                    } else if (distancias[paresV[v]] == std::numeric_limits<int>::max()) {
                        distancias[paresV[v]] = distancias[u] + 1;
                        fila.push(paresV[v]);
                    }
                }
            }
        }

        return false;

    }

bool Grafo::DFS(int u, std::vector<int>& paresU, std::vector<int>& paresV, const std::vector<int>& distancias) {
        if (u != -1) {
            if (u != -1) {
            for (const auto& aresta : arestas) {
                if (aresta->vertice1 == u) {
                    int v = aresta->vertice2;
                    if (paresV[v] == -1 || (distancias[paresV[v]] == distancias[u] + 1 && DFS(paresV[v], paresU, paresV, distancias))) {
                        paresU[u] = v;
                        paresV[v] = u;
                        return true;
                    }
                }
            }
            return false;
        }
        return true;
    }
}


int Grafo::dist(int u) const {
    return (u == -1) ? std::numeric_limits<int>::max() : 0;
}

void Grafo::hopcroft_karp() {

    //separa os vertices em U e V
    for (int i = 0; i < qtdVertices(); i++ ) {
        if (i < qtdVertices()/2) {
            verticesU.push_back(vertices[i]);
        } else {
            verticesV.push_back(vertices[i]);
        }
    }

    vector<int> distancias(verticesU.size(), std::numeric_limits<int>::max()); // Distâncias para busca em largura
    vector<int> paresU(verticesU.size(), -1); // Pares dos vértices em U
    vector<int> paresV(verticesV.size(), -1); // Pares dos vértices em V
    int tamanhoEmparelhamento = 0;

    int resultado = 0;

    while (BFS(paresU, paresV, distancias)) {
        // Para cada vértice em U
        for (long unsigned int u = 0; u < verticesU.size(); ++u) {
            // Se o vértice ainda não foi emparelhado
            if (paresU[u] == -1) {
                // Se encontrar caminho aumentante a partir desse vértice
                if (DFS(u, paresU, paresV, distancias)) {
                    ++tamanhoEmparelhamento;
                }
            }
        }
    }

    cout << "emparelhamento: " << tamanhoEmparelhamento << "\n";

}

void Grafo::coloracao() {
    vector<vector<int>> adjacencias; // Lista de adjacências
    adjacencias.resize(qtdVertices());
    vector<int> cores(adjacencias.size(), -1); // Vetor de cores
    int numero_cromatico = 0;

    for (auto& aresta: arestas) {
        int u = aresta->vertice1;
        int v = aresta->vertice2;
        adjacencias[u-1].push_back(v-1);
        adjacencias[v-1].push_back(u-1);
    }

    for (long unsigned int vertice = 0; vertice < adjacencias.size(); ++vertice) {
        unordered_set<int> coresAdjacentes;

        // Verifica cores dos vértices adjacentes
        for (int adjacente : adjacencias[vertice]) {
            if (cores[adjacente] != -1) {
                coresAdjacentes.insert(cores[adjacente]);
            }
        }

        // Atribui a menor cor disponível ao vértice
        int cor = 0;
        while (coresAdjacentes.count(cor) > 0) {
            ++cor;
        }

        cores[vertice] = cor;
        numero_cromatico = max(numero_cromatico, cor + 1);
    }

    // Imprime a coloração mínima e o número cromático de cada vértice
    cout << "Coloração minima: " << numero_cromatico << endl;
    for (long unsigned int i = 0; i < adjacencias.size(); ++i) {
        cout << "Vértice " << i+1 << ": Cor " << cores[i]+1 << endl;
    }
}
