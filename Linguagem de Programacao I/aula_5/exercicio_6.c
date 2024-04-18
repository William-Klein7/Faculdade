#include <stdio.h>
int main()
// Considere que o cálculo da multa para o pagamento de um determinado imposto varia
// de acordo com a tabela a seguir:
// Valor do Imposto original	Multa por mês de atraso
// até R$ 99,99	R$ 2,00
// até R$ 100,00 a R$ 500,00	R$ 4,00
// mais de R$ 500,00	R$ 8,00
// Por exemplo, se um imposto no valor de R$ 200,00 estiver 3 meses atrasados,
// o valor da multa a ser paga será de R$ 12,00 (3 x 4 Reais).
// Escreva um programa completo que leia inicialmente o valor do imposto e o
// número de meses de atraso no pagamento (esses valores devem ser fornecidos
// pelo usuário do programa via o teclado). De acordo com o valor do imposto,
// o programa deve calcular a multa devida e  imprimir uma mensagem para o usuário
// com o valor da multa e o novo valor do imposto, já acrescido da multa.
// Lembre-se de que o valor deverá ser um float e a saída formatada corretamente
// no que diz respeito ao número de casas decimais

{
	int mesesA;
	float valorI, multa = 0;
	printf("Insira o valor do imposto: ");
	scanf("%f", &valorI);
	printf("Insira quantos meses de atrazados: ");
	scanf("%d", &mesesA);

	if (valorI < 100)
	{
		multa = mesesA * 2;
	}
	else if (valorI >= 100 && valorI < 500)
	{
		multa = mesesA * 4;
	}
	else
	{
		multa = mesesA * 8;
	}

	printf("valor da multa: R$%.2f", multa);
	printf("Novo valor da multa: R$%.2f", valorI + multa);

	return 0;
}