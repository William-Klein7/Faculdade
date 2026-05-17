#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
  int ent;
  float tbc;
  float ta;
  int priority;
} Base;

typedef struct
{
  int ent;
  float tcf;
  float tef;
  float tsf;
} Fila;

typedef struct
{
  int ent;
  float ti;
  float tt;
} Atendente;

int gerarNumeroAleatorio(int i, int f)
{
  return rand() % (f - i + 1) + i;
}

void ordenarPorPrioridade(Base *base, int qtdEnt)
{
  for (int i = 0; i < qtdEnt - 1; i++)
  {
    for (int j = 0; j < qtdEnt - i - 1; j++)
    {
      if (base[j].priority < base[j + 1].priority ||
          (base[j].priority == base[j + 1].priority && base[j].tbc > base[j + 1].tbc))
      {
        Base temp = base[j];
        base[j] = base[j + 1];
        base[j + 1] = temp;
      }
    }
  }
}

void ordenarPorTempoAtendimento(Base *base, int qtdEnt)
{
  for (int i = 0; i < qtdEnt - 1; i++)
  {
    for (int j = 0; j < qtdEnt - i - 1; j++)
    {
      if (base[j].ta > base[j + 1].ta ||
          (base[j].ta == base[j + 1].ta && base[j].tbc > base[j + 1].tbc))
      {
        Base temp = base[j];
        base[j] = base[j + 1];
        base[j + 1] = temp;
      }
    }
  }
}

void ordenarPorChegadaInversa(Base *base, int qtdEnt)
{
  for (int i = 0; i < qtdEnt / 2; i++)
  {
    Base temp = base[i];
    base[i] = base[qtdEnt - i - 1];
    base[qtdEnt - i - 1] = temp;
  }
}

void simular(int qtdEnt, int ti, int ci, int cf, int ai, int af)
{
  Base base[qtdEnt];
  Fila fila[qtdEnt];
  Atendente atendente[qtdEnt];

  for (int i = 0; i < qtdEnt; i++)
  {
    base[i].ent = i + 1;
    fila[i].ent = i + 1;
    base[i].ta = gerarNumeroAleatorio(ai, af);
    base[i].priority = gerarNumeroAleatorio(1, 3);
    base[i].tbc = (i == 0 && ti == 1) ? 0 : gerarNumeroAleatorio(ci, cf);
  }

  printf("\n======= BASE =======\n");
  printf("\nEnt |  TBC  |  TA  | Priority\n");
  printf("----|-------|------|---------\n");
  for (int i = 0; i < qtdEnt; i++)
  {
    printf("%3d | %5.2f | %4.2f | %8d\n", base[i].ent, base[i].tbc, base[i].ta, base[i].priority);
  }

  const char *algoritmos[] = {"FCFS", "LCFS", "PRTY", "SJF"};

  for (int alg = 0; alg < 4; alg++)
  {
    Base baseCopia[qtdEnt];
    for (int i = 0; i < qtdEnt; i++)
    {
      baseCopia[i] = base[i];
    }

    switch (alg)
    {
    case 0:
      break;
    case 1:
      ordenarPorChegadaInversa(baseCopia, qtdEnt);
      break;
    case 2:
      ordenarPorPrioridade(baseCopia, qtdEnt);
      break;
    case 3:
      ordenarPorTempoAtendimento(baseCopia, qtdEnt);
      break;
    }

    for (int i = 0; i < qtdEnt; i++)
    {
      atendente[i].ent = baseCopia[i].ent;

      if (i == 0)
      {
        fila[i].tcf = baseCopia[i].tbc;
        fila[i].tsf = (ti == 1) ? baseCopia[i].tbc : ti;
        atendente[i].ti = fila[i].tsf;
        atendente[i].tt = fila[i].tsf + baseCopia[i].ta;
        fila[i].tef = atendente[i].ti - fila[i].tcf;
      }
      else
      {
        fila[i].tcf = fila[i - 1].tcf + baseCopia[i].tbc;
        fila[i].tsf = (fila[i].tcf > atendente[i - 1].tt) ? fila[i].tcf : atendente[i - 1].tt;
        atendente[i].ti = fila[i].tsf;
        atendente[i].tt = fila[i].tsf + baseCopia[i].ta;
        fila[i].tef = atendente[i].ti - fila[i].tcf;
      }
    }

    printf("\n======= FILA (%s) =======\n", algoritmos[alg]);
    printf("\nEnt |  TCF |  TEF |  TSF\n");
    printf("----|------|------|------\n");
    for (int i = 0; i < qtdEnt; i++)
    {
      printf("%3d | %5.2f | %4.2f | %4.2f\n", fila[i].ent, fila[i].tcf, fila[i].tef, fila[i].tsf);
    }

    printf("\n======= ATENDENTE (%s) =======\n", algoritmos[alg]);
    printf("\nEnt |  TI  |  TT  |\n");
    printf("----|-------|------|\n");
    for (int i = 0; i < qtdEnt; i++)
    {
      printf("%3d | %5.2f | %4.2f\n", atendente[i].ent, atendente[i].ti, atendente[i].tt);
    }
  }
}

int main()
{
  srand(time(NULL));
  int qtdEnt, ti, ci = 0, cf = 0, ai = 0, af = 0;

  printf("Numero de Entidade a simular: ");
  scanf("%d", &qtdEnt);

  printf("Tempo Inicial de Chegada em Zero (1-Sim): ");
  scanf("%d", &ti);
  while ((ci == 0 && cf == 0) || (ci > cf))
  {
    if (ci > cf)
    {
      printf("O Intervalo inicial deve ser menor que o intervalo Final\n");
    }
    printf("Intervalo de Chegada Inicial: ");
    scanf("%d", &ci);
    printf("Intervalo de Chegada Final: ");
    scanf("%d", &cf);
  }
  while ((ai == 0 && af == 0) || (ai > af))
  {
    if (ai > af)
    {
      printf("O Intervalo inicial deve ser menor que o intervalo Final\n");
    }
    printf("Intervalo de Atendimento Inicial: ");
    scanf("%d", &ai);
    printf("Intervalo de Atendimento Final: ");
    scanf("%d", &af);
  }

  simular(qtdEnt, ti, ci, cf, ai, af);

  return 0;
}