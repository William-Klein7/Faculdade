#include <stdio.h>
#include "grafo.h"

void mostraMenu();
void mostraVertices();
int existeVertice(int v, int qtd);

int main()
{
  grafo g;
  int qtdv, qtda, inicio, fim, option = -1, valor = -1, vet[2];

  printf("Criacao de Grafos: \n");
  printf("Digite a quantidade de vertices do seu grafo: ");
  scanf("%d", &qtdv);
  inicializaGrafo(&g, qtdv);
  printf("Sabendo que seus vertices foram criados da seguinte forma:\n");
  for (int i = 0; i < qtdv; i++)
  {
    printf("%do vertice: %d\n", i + 1, i);
  }
  printf("\n");
  printf("Quantas arestas possui o seu grafo? ");
  scanf("%d", &qtda);
  printf("\n");
  for (int i = 0; i < qtda; i++)
  {
    printf("%da aresta: \n Inicio: ", i + 1);
    scanf("%d", &inicio);
    printf(" Fim: ");
    scanf("%d", &fim);
    while (!existeVertice(inicio, qtdv) || !existeVertice(fim, qtdv))
    {
      printf("Insira vertices validos!\n");
      printf("%da aresta: \n Inicio: ", i + 1);
      scanf("%d", &inicio);
      printf(" Fim: ");
      scanf("%d", &fim);
    }
    adicionaAresta(&g, inicio, fim);
  }

  while (option != 0)
  {
    mostraMenu();
    printf("\nFuncao: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
      mostraVertices(g.tamanho);
      printf("Digite um vertice: ");
      scanf("%d", &valor);
      while (!existeVertice(valor, g.tamanho))
      {
        printf("Insira um vertice valido!\nDigite novamente: ");
        scanf("%d", &valor);
      }
      printf("Grau do vertice %d: %d\n", valor, grauVertice(&g, valor));
      break;

    case 2:
      for (int i = 0; i < g.tamanho; i++)
      {
        printf("Grau do vertice %d: %d\n", i, grauVertice(&g, i));
      }
      break;

    case 3:
      grauMaxMin(&g, g.tamanho, vet);
      printf("Grau maximo: %d\n", vet[0]);
      printf("Grau minimo: %d\n", vet[1]);
      break;

    case 4:
      mostraVertices(g.tamanho);
      printf("Digite o primeiro vertice: ");
      scanf("%d", &inicio);
      printf("Digite o segundo vertice: ");
      scanf("%d", &fim);
      while (!existeVertice(inicio, g.tamanho) || !existeVertice(fim, g.tamanho))
      {
        printf("Insira vertices validos!\n");
        printf("Digite o primeiro vertice: ");
        scanf("%d", &inicio);
        printf("Digite o segundo vertice: ");
        scanf("%d", &fim);
      }
      printf(saoVizinhos(&g, inicio, fim) ? "Sao vizinhos!\n" : "Nao sao vizinhos!\n");
      break;

    case 5:
      printf(ehGrafoSimples(&g) ? "O grafo eh simples.\n" : "O grafo nao eh simples.\n");
      break;

    case 6:
      printf("Digite os dois vertices para verificar conexao:\n");
      scanf("%d %d", &vet[0], &vet[1]);
      if (!existeVertice(vet[0], g.tamanho) || !existeVertice(vet[1], g.tamanho))
      {
        printf("Vertice(s) invalido(s).\n");
        break;
      }
      printf(saoVizinhos(&g, vet[0], vet[1]) ? "Existe conexao\n" : "Nao existe conexao\n");
      break;

    case 7:
      printf(ehCiclo(&g, g.tamanho) ? "E um ciclo!\n" : "Nao e um ciclo!\n");
      break;

    case 8:
    {
      int vizinhos[g.tamanho];
      printf("Digite o vertice: ");
      scanf("%d", &valor);
      if (!existeVertice(valor, g.tamanho))
      {
        printf("Vertice invalido.\n");
        break;
      }
      todosVizinhos(&g, valor, vizinhos);
      printf("Vizinhos do vertice %d: ", valor);
      for (int i = 0; i < g.tamanho; i++)
      {
        if (saoVizinhos(&g, valor, i))
          printf("%d ", i);
      }
      printf("\n");
      break;
    }

    case 9:
      verticesIsolados(&g);
      break;

    case 10:
      printf(ehConexo(&g) ? "O grafo eh conexo\n" : "O grafo nao eh conexo\n");
      break;

    case 11:
      mostrarGrafo(&g);
      break;

    case 12:
      dijkstra(&g);
      break;

    case 13:
      adicionarVertice(&g);
      printf("Vertice adicionado! Novo total: %d\n", g.tamanho);
      break;

    case 14:
      printf("Digite o vertice a ser removido: ");
      scanf("%d", &valor);
      if (!existeVertice(valor, g.tamanho))
      {
        printf("Vertice invalido.\n");
        break;
      }
      removerVertice(&g, valor);
      printf("Vertice %d removido. Novo total: %d\n", valor, g.tamanho);
      break;

    case 15:
      printf("Digite os vertices da aresta (inicio e fim): ");
      scanf("%d %d", &inicio, &fim);
      if (!existeVertice(inicio, g.tamanho) || !existeVertice(fim, g.tamanho))
      {
        printf("Vertices invalidos.\n");
        break;
      }
      adicionaAresta(&g, inicio, fim);
      printf("Aresta adicionada.\n");
      break;

    case 16:
      printf("Digite os vertices da aresta a ser removida: ");
      scanf("%d %d", &inicio, &fim);
      if (!existeVertice(inicio, g.tamanho) || !existeVertice(fim, g.tamanho))
      {
        printf("Vertices invalidos.\n");
        break;
      }
      removerAresta(&g, inicio, fim);
      printf("Aresta removida.\n");
      break;

    case 0:
      printf("Saindo...\n");
      break;

    default:
      printf("Opcao invalida.\n");
    }
  }

  free(g.vertices);
  free(g.arestas);

  return 0;
}

void mostraMenu()
{
  printf("\n");
  printf("============== MENU ==============\n");
  printf("1 - Mostrar grau de um vertice\n");
  printf("2 - Mostrar grau de todos os vertices\n");
  printf("3 - Mostrar grau maximo e minimo\n");
  printf("4 - Verificar se dois vertices sao vizinhos\n");
  printf("5 - Verificar se o grafo eh simples\n");
  printf("6 - Verificar se existe conexao entre dois vertices\n");
  printf("7 - Verificar se eh um ciclo\n");
  printf("8 - Mostrar todos os vizinhos de um vertice\n");
  printf("9 - Mostrar vertices isolados\n");
  printf("10 - Verificar se o grafo eh conexo\n");
  printf("11 - Mostrar representacao do grafo\n");
  printf("12 - Executar algoritmo de Dijkstra\n");
  printf("13 - Adicionar vertice\n");
  printf("14 - Remover vertice\n");
  printf("15 - Adicionar aresta\n");
  printf("16 - Remover aresta\n");
  printf("0 - Sair\n");
  printf("==================================\n");
}

void mostraVertices(int count)
{
  printf("Vertices: \n");
  for (int i = 0; i < count; i++)
  {
    printf("%do vertice: %d\n", i + 1, i);
  }
  printf("\n");
}
int existeVertice(int v, int qtd)
{
  return (v >= 0 && v < qtd);
}