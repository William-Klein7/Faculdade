#include <stdio.h>
int main()
// Faca um programa que leia uma variavel e então incremente o
// valor dessa variavel 10 vezes utilizando ponteiro

{
	int x;
	int *p;

	scanf("%d", &x);
	p = &x;

	for (int i = 0; i < 10; i++)
	{
		(*p)++;
	}
	printf("Variavel incrementada 10 vezes: %d", *p);

	return 0;
}