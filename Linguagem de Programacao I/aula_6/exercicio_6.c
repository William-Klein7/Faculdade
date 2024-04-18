#include <stdio.h>
int main()
// Elabore um programa que declare 4 variáveis do tipo inteiro (a, b, c, d) e 4
// do tipo ponteiro de inteiro(pa, pb, pc, pd) .  Leia os 4 valores para as variaveis inteiras
// e então efetue a soma dos quatro valores utilizando os ponteiros.
{
	int a, b, c, d;

	scanf("%d %d %d %d", &a, &b, &c, &d);
	int *pa = &a, *pb = &b, *pc = &c, *pd = &d;

	printf("Soma das 4 variaveis, utilizando ponteiros: %d", (*pa) + (*pb) + (*pc) + (*pd));
	return 0;
}