#include <stdio.h>
#include <stdlib.h>
// Escrever uma funcão int dia(struct data *dt) que retorna qual o dia da data passada por parâmetro.

// struct data teste={15, 4, 1999};
// int ult;
// ult = dia(&teste);    /*ult recebe 15 */
typedef struct
{
	int d;
	int m;
	int a;
} data;

int dia(data *dt)
{
	return dt->d;
}

int main()
{
	data teste = {15, 4, 1999};

	printf("%d", dia(&teste));
	return 0;
}