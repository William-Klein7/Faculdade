#include <stdio.h>
#include "ponto.h"

int main()
{
  int i;
  float x, y;
  ponto a, b, p[2];
  inicializa_ponto(&a);
  inicializa_ponto(&b);
  inicializa_ponto(&p[0]);
  inicializa_ponto(&p[1]);
  // Setar valores
  for (i = 0; i < 4; i++)
  {
    printf("x do %do. ponto: ", (i + 1));
    scanf("%f", &x);
    printf("y do %do. ponto: ", (i + 1));
    scanf("%f", &y);
    if (i == 0)
      set_ponto(&a, x, y);
    if (i == 1)
    {
      set_ponto_x(&b, x);
      set_ponto_y(&b, y);
    }
    if (i == 2)
      set_ponto(&p[0], x, y);
    if (i == 3)
      set_ponto(&p[1], x, y);
    printf("\n");
  }
  // Consulta dos valores
  for (i = 0; i < 4; i++)
  {
    if (i == 0)
    {
      x = get_ponto_x(&a);
      y = get_ponto_y(&a);
    }
    if (i == 1)
    {
      x = get_ponto_x(&b);
      y = get_ponto_y(&b);
    }
    if (i == 2)
    {
      x = get_ponto_x(&p[0]);
      y = get_ponto_y(&p[0]);
    }
    if (i == 3)
    {
      x = get_ponto_x(&p[1]);
      y = get_ponto_y(&p[1]);
    }
    printf("%do. ponto (%.2f,%.2f)\n", (i + 1), x, y);
  }

  x = distancia_ponto(&a, &b);
  y = distancia_ponto(&a, &p[0]);

  printf("Distancias do:\n");
  printf("1° p/ 2° ponto: %f\n", x);
  printf("1° p/ 3° ponto: %f\n", y);
}