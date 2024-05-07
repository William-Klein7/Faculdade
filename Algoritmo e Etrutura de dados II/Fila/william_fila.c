#include <stdio.h>
#include "william_fila.h"

int main()
{
  fila f;
  inicializar(&f);
  for (int i = 0; i < f.tamMax; i++)
  {
    insere(&f, i + 1);
  }

  printf("Fila:\n");
  printf("{ ");
  for (int i = 0; i < f.tamMax; i++)
  {
    printf("%d ", inicio(&f));
    retira(&f);
  }
  printf("}\n");

  return 0;
}
