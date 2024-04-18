#include <stdio.h>

// Explique o que o progama abaixo faz

int main()

{
    float vet[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float *f;
    int i;
    f = vet;
    //atribui o ponteiro para q ele aponte para vet

    printf("contador/valor/valor/endereco/endereco");

    for (i = 0; i <= 4; i++)
    {
        printf("\ni = %d", i);
        //faz print de i
        printf("   vet[%d] = %.1f", i, vet[i]);
         //faz print das casas de vet
        printf("   *(f + %d) = %.1f", i, *(f + i));
         //faz print das casas de vet por meio do ponteiro
        printf("   &vet[%d] = %X", i, &vet[i]);
         //faz print do local de memoria de cada casa de vet
        printf("   (f + %d) = %X", i, f + i);
         //faz print do local de memoria de cada casa de vet por meio do ponteiro
    }

    return 0;
}