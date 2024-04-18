#include <stdio.h>

int mNum(float num1, float num2)
{
	if (num1 < num2)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int main()
// Escreva uma função que retorne o menor número entre
// dois números ponto flutuante fornecidos pelo usuário
{
	float num1, num2;
	scanf("%f", &num1);
	scanf("%f", &num2);

	if (mNum(num1, num2) == 1)
	{
		printf("%.2f e o menor", num1);
	}
	else
	{
		printf("%.2f e o menor", num2);
	}

	return 0;
}