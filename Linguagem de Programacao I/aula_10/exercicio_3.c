/* 3) Faça uma função que incremente um valor passado como parâmetro.
Mostre o valor antes da chamada da função e ele incrementado após a chamada.
**Você deve passar o valor por referência*/
#include<stdio.h>
#include<stdlib.h>
int inc(int *num)
{
	(*num)++;
	printf("Valor depois do incremento na funcao: %d",*num);
	return 0;
}
int main()
{
	int num;
	scanf("%d",&num);
	printf("Valor antes do incremento na main: %d\n",num);
	inc(&num);
	return 0;
}
