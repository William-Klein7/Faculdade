#include <stdio.h>

// Explique o que o progama abaixo faz

int main()

{
    int vet[] = {4, 9, 12};
    int i, *ptr;
    ptr = vet;
    // atribui vet ao ponteiro
    for (i = 0; i < 3; i++)
    {
        printf("%d ", *ptr++);
        // faz print das casas ocupadas de vet 4 9 12
    }
    return 0;
}