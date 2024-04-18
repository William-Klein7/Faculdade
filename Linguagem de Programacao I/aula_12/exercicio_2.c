#include <stdio.h>
#include <stdlib.h>
// Escreva uma funcao que leia os campos numero1 e numero2 de uma estrutura.
// A seguir faca uma outra funcao inverter esses valores na estrutura original de forma que numero1 contenha
// o valor de numero2 e numero2 o valor de numero1.
// Mostre a estrutura original após essa inversão. (passe a estrutura para a função por referência)
struct number
{
	int numero1;
	int numero2;
};

void inverter(struct number *p)
{
	int aux;
	aux = p->numero1;
	p->numero1 = p->numero2;
	p->numero2 = aux;
}

int main()
{
	struct number number;

	printf("Digite o valor para numero1: ");
	scanf("%d", &(number.numero1));

	printf("Digite o valor para numero2: ");
	scanf("%d", &(number.numero2));
	printf("\nEstrutura original: numero1 = %d, numero2 = %d\n", number.numero1, number.numero2);
	inverter(&number);
	printf("Estrutura apos a inversao: numero1 = %d, numero2 = %d\n", number.numero1, number.numero2);

	return 0;
}