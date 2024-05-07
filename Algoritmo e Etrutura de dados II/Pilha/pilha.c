#include <stdio.h>
#include "TAD_pilha.h"
#include "TAD_pilha_v1.h"
// #include "TAD_pilha_v2.h"
#include "william_pilha_inverte.h"

int main()
{
    pilha p, d;
    int opcao, elemento;
    inicializapilha(&p);
    while (1)
    {
        printf("PILHA: 1-Empilhar 2-Desempilhar 3-Topo 4-Tamanho 5-Duplicar 6-Replica auxiliar 7-Inverter pilha 0-Sair\n");
        printf("Informe a opcao: ");
        scanf("%d", &opcao);
        if (opcao == 0)
            break;
        if (opcao == 1)
        {
            if (pilhacheia(&p))
                printf("A pilha esta cheia para empilhar...\n");
            else
            {
                printf("Qual elemento empilhar: ");
                scanf("%d", &elemento);
                empilha(&p, elemento);
            }
        }
        if (opcao == 2)
        {
            if (pilhavazia(&p))
                printf("A pilha esta vazia para desempilhar...\n");
            else
            {
                printf("O elemento %d sera' desempilhado...\n", topopilha(&p));
                desempilha(&p);
            }
        }
        if (opcao == 3)
        {
            if (!pilhavazia(&p))
                printf("Elemento do Topo da Pilha: %d\n", topopilha(&p));
            else
                printf("Pilha vazia ...\n");
        }
        if (opcao == 4)
        {
            printf("Tamanho da Pilha: %d\n", tamanhopilha(&p));
        }
        if (opcao == 5)
        {
            if (pilhavazia(&p))
            {
                printf("A primeira pilha esta vazia, nao e possivel replica-la\n");
            }
            else
            {
                replicapilha(&p, &d);
                printf("Pilha duplicada");
            }
        }
        if (opcao == 6)
        {
            if (pilhavazia(&p))
            {
                printf("A primeira pilha esta vazia, nao e possivel replica-la\n");
            }
            else
            {
                replicapilhaauxiliar(&p, &d);
                printf("Pilha duplicada aux");
            }
        }
        if (opcao == 7)
        {
            if (pilhavazia(&p))
            {
                printf("A pilha esta vazia, nao e possivel inverte-la\n");
            }
            else
            {
                invertepilha(&p);
                printf("Pilha invertida");
            }
        }
        printf("\n");
    }
    printf("Tecle <enter> para continuar...");
    getchar();
}