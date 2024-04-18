#include <stdio.h>
#include "TAD_pilha.h"
#include "TAD_pilha_v1.h"
// #include "TAD_pilha_v2.h"
int main()
{
    pilha p, d;
    int opcao, elemento;
    inicializapilha(&p);
    while (1)
    {
        printf("PILHA: 1-Empilhar 2-Desempilhar 3-Topo 4-Tamanho 5-Duplicar 6-Replica auxiliar 0-Sair\n");
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

            replicapilha(&p, &d);
            printf("Pilha duplicada");
        }
        if (opcao == 6)
        {

            replicapilhaauxiliar(&p, &d);
            printf("Pilha duplicada aux");
        }
        printf("\n");
    }
    printf("Tecle <enter> para continuar...");
    getchar();
}