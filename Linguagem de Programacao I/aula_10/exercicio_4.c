/* 4) Faça uma função que inverta dois valores passados como parâmetros para a função.
Mostre os valores invertidos antes e após a chamada da função
**Você deve passar os valores por referência*/
#include<stdio.h>
#include<stdlib.h>
void inverte(int *a, int *b)
{
	int *aux;
	aux=*a;
	*a=*b;
	*b=aux;
}
int main()
{
	int a,b;
	scanf("%d %d",&a,&b);
	printf("Valores antes da troca: %d  %d\n",a,b);
	inverte(&a,&b);
	printf("Valores depois da troca: %d  %d",a,b);
	return 0;
}
