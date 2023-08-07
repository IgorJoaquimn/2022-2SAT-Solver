#include "campanha.hpp"

void graph::add_aresta(int x, int y)
// Descricao: Adiciona uma nova aresta no grafo, trata os casos em que x e/ou y são zeros 
// Entrada: x e y : representação da fórmula CNF
// Saida: nova aresta no grafo, se já não existir
{

    // Caso base   
    if (x == 0 && y == 0)
        return;

    // Cálculo dos Literais X e Y negados
    // Caso 1: Variavel não negada para variável negada
    // Caso 2: Variavel negada para variável não negada
    int Xnegado = (x <= M) ? (x - 1 + M) : (x - 1 - M);
    int Ynegado = (y <= M) ? (y - 1 + M) : (y - 1 - M);
    if (x == 0)
    {
        this->data[Ynegado].push_back(y - 1);
        this->inverse[y - 1].push_back(Ynegado);
        return;
    }

    if (y == 0)
    {
        add_aresta(y, x);
        return;
    }
    this->data[Xnegado].push_back(y - 1);
    this->data[Ynegado].push_back(x - 1);

    this->inverse[y - 1].push_back(Xnegado);
    this->inverse[x - 1].push_back(Ynegado);
}

void graph::dfs(int x)
// Descricao: executa a DFS a partir de X , se ele já não foi visitado 
// Entrada: x vértice a ser visitado
// Saida: Visitado[x] = true, pilha agora contém x;
{
    if (visitado[x] == true)
        return;

    visitado[x] = true;
    for (auto u : data[x])
    {
        // Se tem arresta (x,u) e u nao foi visitado, dfs nele
        if ((visitado[u] == false))
            dfs(u);
    }
    // Pilha usada para o algoritmo de Kosaraju
    pilha.push_back(x);
    return;
}

bool graph::dfs_reversa(int x, vector<int> &componente)
// Descricao: executa a DFS a partir de X, no grafo reverso
//            Além disso, retorna false se o componente encontrado tiver caminho de u para ~u, para algum vertice u;
// Entrada: x: vértice a ser visitado, componente: componente conexo a ser encontrado; 
// Saida: Visitado[x] = true, pilha agora contém x;
{

    // Variavel de controle;
    bool sat = 1;
    visitado[x] = true;
    for (auto u : inverse[x])
    {
        // Se tem arresta (x,u) e u nao foi visitado, dfs nele
        if (visitado[u] == false)
            sat &= dfs_reversa(u, componente);
    }

    if (componente[x % M] == false)
    // Se x nem ~x foram visitados, visite-os e retorne a variável de controle;
    {
        componente[x % M] = true;
        return sat;
    }
    else
    // Se x e ~x foram visitados, a fórmula é insatisfatível;
        return false;
}

bool graph::e_satisfativel()
// Descricao: método que usa o Kosaraju para verificar satisfabilidade de fórmulas cnf;
// Saida: Sim se a fórmula for satisfatível, não caso contrário;
{
    //Dfs para descobrir todos os vértices;
    for (int x = 0; x < 2 * M; x++)
        dfs(x);

    //Reescrita do vetor de visitados para segunda dfs;  
    for (int i = 0; i < 2 * M; i++)
        visitado[i] = false;

    //u percorre a pilha em ordem decrescente de posições;
    for (auto u = pilha.rbegin(); u != pilha.rend(); ++u)
    {
        int x = *u;
        //Se u nao esta em algum componente conexo, encontre o componente conexo de u;
        if (visitado[x] == false)
        {
            vector<int> componente(M, 0);
            int sat = dfs_reversa(x, componente);
            // Se existe componente com um literal e sua negação, a fórmula é insatisfatível;
            if (!sat)
                return false;
        }
    }
    // True se e somente se Todo Componente não possui caminho entre um literal e sua negação;
    return true;
}

void graph::set_tam(int tam)
// Descricao: método que inicializa os vetores auxiliares;
// Entrada: tam: quantidade de literais presente na CNF; 2*tam == quantidade de vértices no grafo;
{
    pilha.clear();
    vector<int> copy(2 * tam, 0);
    visitado = copy;
    this->M = tam;
    for (int i = 0; i < 2 * M; i++)
    {
        data[i].clear();
        inverse[i].clear();
    }
}
