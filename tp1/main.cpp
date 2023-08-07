#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "campanha.hpp"
using namespace std;

// Linha para otimizar leitura
#define _                           \
  ios_base::sync_with_stdio(false); \
  std::cin.tie(0);

int main()
// Descricao: leitura da entrada
// Entrada: entrada padrão
// Saida: sim se a entrada for satisfatível, não se o contrário
{
  _ int x, y;
  int N, M;

  // Objeto grafo, responsável pela modelagem do problema
  graph g;
  while (cin >> N >> M)
  {
    if (N == 0 && M == 0)
      break;
    // Inicialização do grafo
    g.set_tam(M);

    // Leitura da instancia
    for (int i = 0; i < N; i++)
    {
      // Cnf = (x ou y)
      cin >> x >> y;
      g.add_aresta(x, y);

      // Cnf = (~x ou ~y)
      cin >> x >> y;
      if (x == 0)
        g.add_aresta(0, y + M);
      else if (y == 0)
        g.add_aresta(x + M, 0);
      else
        g.add_aresta(x + M, y + M);
    }

    if (g.e_satisfativel())
      cout << "sim" << endl;
    else
      cout << "nao" << endl;
  }
}