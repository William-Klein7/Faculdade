#include <stdio.h>
#include <stdlib.h>

int main()
// Aloque de forma dinamica um array bidimensional com o numero de posicoes fornecidas pelo usuario. 
// Preencha esse array com valores randomicos (utilize a função rand() ). 
// A seguir utilizando ponteiros mostre o conteudo desse array. Nao esqueca de liberar o espaco alocado em memoria

{
	
      int linhas, colunas;

    printf("Informe o numero de linhas: ");
    scanf("%d", &linhas);

    printf("Informe o numero de colunas: ");
    scanf("%d", &colunas);

    int **array = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        array[i] = (int *)malloc(colunas * sizeof(int));
    }

    srand(1);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            array[i][j] = rand() % 100; 
        }
    }

    printf("Conteudo do array:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d\t", *(*(array + i) + j));
        }
        printf("\n");
    }

    for (int i = 0; i < linhas; i++) {
        free(array[i]);
    }
    free(array);
	return 0;
}