/* 4) Fa�a uma fun��o que inverta dois valores passados como par�metros para a fun��o.
Mostre os valores invertidos antes e ap�s a chamada da fun��o
**Voc� deve passar os valores por refer�ncia*/
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
