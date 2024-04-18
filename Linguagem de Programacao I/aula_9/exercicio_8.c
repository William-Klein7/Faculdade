#include <stdio.h>

int area()
{
	int base, altura, area = 0;

	scanf("%d", &base);
	scanf("%d", &altura);

	area = base * altura;

	return area;
}

int main()
// Elaborar uma função para ler a base e a altura de um retângulo, calcular e
// retornar a sua área.
// Na função principal é apresentado o valor dessa área. Fórmula: Area = base * altura

{
printf("a area e %d", area());
	return 0;
}