// Base (Entidade, TBC, TA)
// TBC = Tempo Base de Chegada
// TA = Tempo de Atendimento

// Fila (Entidade, TCF, TEF, TSF)
// TCF = Tempo de Chegada na Fila
// TEF = Tempo de Espera na Fila
// TSF = Tempo de Saída da Fila

// Atendente n (Entidade, TI, TT)
// TI =Tempo de Início do Atendimento
// TT = Tempo de Término do Atendimento

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct 
{
    int ent;
    float tbc;
    float ta;
}Base;

typedef struct 
{
    int ent;
    float tcf;
    float tef;
    float tsf;
}Fila;

typedef struct 
{
    int ent;
    float  ti;
    float tt;
}Atendente;

int gerarNumeroAleatorio(int i, int f)
{
    int random = rand() % (f - i + 1) + i;
    return random;
}

void simular(int qtdEnt,int ci,int cf, int ti,int ai,int af){
    Base base[qtdEnt];
    Fila fila[qtdEnt];
    Atendente atendente[qtdEnt];

    for (int i = 0; i < qtdEnt; i++)
    {
        base[i].ent = i + 1;
        fila[i].ent = i + 1;
        atendente[i].ent = i + 1;
        base[i].ta = gerarNumeroAleatorio(ai, af);

        if (i == 0 && ti == 1)
            base[i].tbc = 0;
        else
            base[i].tbc = gerarNumeroAleatorio(ci, cf);

        if (i == 0)
        {
            fila[i].tcf = base[i].tbc;
            fila[i].tsf = ti ? base[i].tbc : ti;
            atendente[i].ti=fila[i].tsf;
            atendente[i].tt = fila[i].tsf + base[i].ta;
            fila[i].tef = ti ? base[i].tbc : ti;
        }
        else
        {
            fila[i].tcf = fila[i - 1].tcf + base[i].tbc;
            fila[i].tsf = (fila[i].tcf > atendente[i - 1].tt) ? fila[i].tcf : atendente[i - 1].tt;
            atendente[i].ti=fila[i].tsf;
            atendente[i].tt = fila[i].tsf + base[i].ta;
            fila[i].tef = fila[i].tsf - fila[i].tcf;
        }

    }
    printf("\n======= BASE =======\n");
    printf("\nEnt |  TBC  |  TA  |\n");
    printf("----|-------|------|\n");
        for (int i = 0; i < qtdEnt; i++)
        {
            printf("%3d | %5.2f | %4.2f \n",base[i].ent,base[i].tbc,base[i].ta);
        }
        
    printf("\n======= FILA =======\n");
    printf("\nEnt |  TCF |  TEF |  TSF \n");
    printf("----|-------|------|-----\n");
        for (int i = 0; i < qtdEnt; i++)
        {
            printf("%3d | %5.2f | %4.2f | %4.2f \n",fila[i].ent,fila[i].tcf,fila[i].tef,fila[i].tsf);
        }


    printf("\n======= ATENDENTE =======\n");
    printf("\nEnt |  TI  |  TT  |\n");
    printf("----|-------|------|\n");
        for (int i = 0; i < qtdEnt; i++)
        {
            printf("%3d | %5.2f | %4.2f \n",atendente[i].ent,atendente[i].ti,atendente[i].tt);
        }



    // printf("\nEnt |  TBC  |  TC  | TEF  | TEA  |  TA  |  TS\n");
    // printf("----|-------|------|------|------|------|------\n");
    // for (int i = 0; i < qtdEnt; i++)
    // {
    //     printf("%3d | %5d | %4d | %4d | %4d | %4d | %4d\n", base[i].ent, base[i].tbc, fila[i].tcf, fila[i].tef, fila[i].tsf, base[i].ta, atendente[i].tt);
    // }
}




int main()
{
    int qtdEnt,ti,ci=0,cf=0,ai=0,af=0;
    
    printf("Numero de Entidade a simular: ");
    scanf("%d", &qtdEnt);

    printf("Tempo Inicial de Chegada em Zero (1-Sim): ");
    scanf("%d", &ti);
    while (ci == 0 && cf == 0 || (ci > cf))
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
    while (ai == 0 && af == 0 || (ai > af))
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
    if (ti != 1)
        ti = 0;
    simular(qtdEnt,ci,cf, ti,ai,af);


    return 0;
}


