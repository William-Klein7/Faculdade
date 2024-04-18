#include <stdio.h>
int main()
// A série de RICCI difere da série de FIBONACCI porque os dois números iniciais
// são dados pelo usuário e os outros termos são gerados a partir da soma dos dois anteriores.
// Escreva um programa que imprime os 20 primeiros números a partir de duas entradas do usuário.

{
    int a, b, c;

    printf("Digite um valor: ");
    scanf("%d", &a);
    printf("\nDigite outro valor: ");
    scanf("%d", &b);

    printf("%d ", a);
    printf("%d ", b);

    for (int i = 3; i <= 20; i++)
    {
        c = a + b;
        printf("%d ", c);
        a = b;
        b = c;
    }

    return 0;
}