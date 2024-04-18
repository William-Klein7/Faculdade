#include <stdio.h>
#include <stdlib.h>

// Elabore um programa que

// Explicação de como gerar números aleatórios:
// Para gerar numeros aleatorios em C utilize as funcoes srand e rand da seguinte maneira

// srand()-> inicializa sempre de forma aleatoria.
// Ex.: srand(semente);

// rand()-> gera o numero.
// Ex.: rand() % max_val
// Sorteia um numero de 0 a (max_val-1)

// Exemplo de uso

int main()
{
    int vet[10], cont = 0;

    for (int i = 0; i < 10; i++)
    {
        vet[i] = rand() % 10;
        if (vet[i] % 2 == 0)
        {
            cont++;
        }
    }

    int vet2[cont];

    int *pVet = vet2;

    for (int i = 0; i < 10; i++)
    {
        if (vet[i] % 2 == 0)
        {
            *pVet = vet[i];
            pVet++;
        }
    }
    pVet = vet2;
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
    for (int i = 0; i < cont; i++)
    {
        printf("%d ", *pVet++);
    }

    return 0;
}