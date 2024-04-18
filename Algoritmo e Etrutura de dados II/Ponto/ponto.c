#include <stdio.h>
#include "ponto.h"
#define tam 2

int main()
{
  ponto p[tam];
  float x, y;
  int i = 0;

  printf("Digite os valores do primeiro plano cartesiano:\nx=");
  scanf("%f", &x);
  setx(&p[0], x);
  printf("y=");
  scanf("%f", &y);
  sety(&p[0], y);

  printf("Digite os valores do segundo plano cartesiano:\nx=");
  scanf("%f", &x);
  printf("y=");
  scanf("%f", &y);
  setponto(&p[1], x, y);
  for (i = 0; i < tam; i++)
  {
    printf("\nValores do %do plano cartesiano: (%.1f , %.1f)", i + 1, getx(&p[i]), gety(&p[i]));
  }
  printf("\nPonto de origem do ponto 1: %.1f", ponto_origem(&p[0]));
  printf("\nDistancia entre os dois pontos: %.1f", ponto_distancia(&p[0], &p[1]));

  return 0;
}