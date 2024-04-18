#include <stdio.h>
int main()
// Crie um programa que imprima a tabuada do 1 ao 9.

{

    for (int i = 1; i < 10; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            printf("%d X %d = %d \n", i, j, i * j);
        }
        printf("\n");
    }

    return 0;
}