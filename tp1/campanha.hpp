#ifndef GRAPH
#define GRAPH
#define MAX 20000
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class graph
// Descricao: classe responsável por representar o grafo construído
{
private:
    // Listas de adjacencia do grafo reverso e do grafo padrão 
    list<int> data[MAX];
    list<int> inverse[MAX];

    // Tamanho da instância
    int M = MAX;

    // Vetores auxiliares
    vector<int> pilha;
    vector<int> visitado;

public:
    // Inicialização de nova instância
    void set_tam(int tam);

    void add_aresta(int x, int y);
    
    // Métodos para encontrar componentes conexos 
    bool e_satisfativel();
    void dfs(int x);
    bool dfs_reversa(int x, vector<int> &componente);    
};

#endif
