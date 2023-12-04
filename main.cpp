#include "grafo.h"

int main() {
    //Grafo *grafo_dirigido_fluxo = new Grafo("fluxo.net");
    //grafo_dirigido_fluxo->item_1(1, 4); // item 1 (Edmonds-Karp), passar origem e sorvedouro como argumentos


    // Grafo *grafo_bipartido = new Grafo("pequeno.net"); // passar como parâmetro o arquivo de grafo
    // grafo_bipartido->hopcroft_karp(); // item 1 da atividade, com Edmonds-Karp

    Grafo *grafo_colorir = new Grafo("cor3.net");
    grafo_colorir->coloracao();

    delete grafo_colorir;
    //delete grafo_bipartido;
    //delete grafo_dirigido_fluxo;
    return 0;
}