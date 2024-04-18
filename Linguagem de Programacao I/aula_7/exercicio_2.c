#include <stdio.h>

// Reescreva o programa abaixo  usando ponteiros
//  float matrx[50][50];
//     int i, j;
//     for (i = 0; i < 50; i++)
//     {
//         for (j = 0; j < 50; j++)
//         {
//             matrx[i][j] = 0.0;
//         }
//     }
int main()

{
    float matrx[50][50];
    float *pMatrx = &matrx[0][0];

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            *pMatrx = 0.0;
            pMatrx++;
        }
    }
    
    return 0;
}