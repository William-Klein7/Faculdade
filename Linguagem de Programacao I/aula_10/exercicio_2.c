/* 2) Faça uma função que receba uma variável inteira por referência.
Mostre o endereço dessa variável dentro do main e dentro da função.*/
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
