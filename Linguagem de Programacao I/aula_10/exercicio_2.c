/* 2) Fa�a uma fun��o que receba uma vari�vel inteira por refer�ncia.
Mostre o endere�o dessa vari�vel dentro do main e dentro da fun��o.*/
#include<stdio.h>
#include<stdlib.h>
int end(int *num)
{
	printf("Endereco na funcao: %d",&num);
	return 0;
}
int main()
{
	int num;
	scanf("%d",&num);
	printf("Endereco na main: %d\n",&num);
	end(&num);
	return 0;
}
