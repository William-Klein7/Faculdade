/* 3) Fa�a uma fun��o que incremente um valor passado como par�metro.
Mostre o valor antes da chamada da fun��o e ele incrementado ap�s a chamada.
**Voc� deve passar o valor por refer�ncia*/
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
