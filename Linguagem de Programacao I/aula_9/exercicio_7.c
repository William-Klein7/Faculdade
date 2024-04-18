#include <stdio.h>

float tranformTemp(float temp)
{
	float C;

	C = (temp - 32) * 5 / 9;

	return C;
}

int main()
// Criar uma função que converta uma temperatura dada em Fahrenheit em Celsius.
// A temperatura é passada como parâmetro para uma função que retorna a temperatura
// em Celsius, que deve ser mostrada
// no programa principal. A fórmula para cálculo é C = ( F - 32 ) * 5 / 9

{
	float temp;

	scanf("%f", &temp);

	printf("a temperatura em celsius e: %.2f", tranformTemp(temp));

	return 0;
}