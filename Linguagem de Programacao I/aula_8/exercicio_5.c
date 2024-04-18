/* 5) Aloque de forma din�mica dois arrays com o n�mero de posi��es informadas pelo usu�rio.
Preencha seus elementos de forma rand�mica (utilize a fun��o rand() ).
Efetue a soma de cada posi��o do array 1 com a sua correspondente no array 2.
Mostre o resultado. Ap�s isso, libere o espa�o alocado em mem�ria para os arrays.*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int tam,i,j;
	printf("Informe o tamanho dos vetores: ");
	scanf("%d",&tam);
	int *vet1=(int *) malloc (sizeof(int)*tam);
	int *vet2=(int *) malloc (sizeof(int)*tam);
	
	srand(time(NULL));
	for(i=0;i<tam;i++)
	{
		vet1[i]=rand();
		vet2[i]=rand();
	}

	printf("Vetor 1: ");
	for(i=0;i<tam;i++)
	printf("%d  ",vet1[i]);
	
	printf("\n");
	
	printf("Vetor 2: ");
	for(i=0;i<tam;i++)
	printf("%d  ",vet2[i]);
	
	int soma[tam];
	for(i=0;i<tam;i++)
	{
		soma[i]=vet1[i]+vet2[i];
	}
	
	printf("\nSomas: ");
	for(i=0;i<tam;i++)
	{
		printf("%d ",soma[i]);
	}
	
	free(vet1);
	free(vet2);
	return 0;
}
