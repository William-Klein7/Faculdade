#include <stdio.h>
int main()
// Uma pesquisa sobre o sabor de um novo refrigerante  foi
// feita com várias pessoas. As mesmas preenchiam uma tabela com 'O' de ótimo,
// 'B'  de bom,   'R'  de  regular  e  'U'  de  ruim.  Faça um programa   que
// leias   as   respostas   coletadas   pela   pesquisa   (as letras   'O',   'B',   'R'   e   'U')
// sendo  que   o   fim  das   respostas   será indicado   por   um   traço   '-'.   Outras   letras
// devem   ser desconsideradas. O programa deve também:
// • indicar a quantidade de cada resposta,
// • indicar o total de respostas,
// • calcular a porcentagem de cada uma das respostas, e
// • indicar se a soma de respostas 'O' e 'B' é maior ou não que a soma de respostas 'R' e 'U'.

{
	char car = 'a';
	int contO = 0, contB = 0, contR = 0, contU = 0;

	printf("Insira as letras da pesquisa, ou ' - ' para finalizar o prorama: \n");
	while (1)
	{
		scanf("%c", &car);

		if (car == '-')
		{
			break;
		}
		if (car != '-')
		{
			if (car == 'O')
			{
				contO++;
			}
			else if (car == 'B')
			{
				contB++;
			}
			else if (car == 'R')
			{
				contR++;
			}
			else if (car == 'U')
			{
				contU++;
			}
		}
	}
	if (contO > 0 || contB > 0 || contR > 0 || contU > 0)
	{
		printf("Total de cada resposta:\nO (Otimo): %d\nB (Bom): %d\nR (Regular): %d\nU (Ruim): %d\n\n", contO, contB, contR, contU);
		printf("O total de cada resposta: %d\n", contO + contB + contR + contU);
		printf("\nResultados da pesquisa:\n");
		printf("Otimo (O): %.2f%%\n", (float)contO / (contO + contB + contR + contU) * 100.0);
		printf("Bom (B): %.2f%%\n", (float)contB / (contO + contB + contR + contU) * 100.0);
		printf("Regular (R): %.2f%%\n", (float)contR / (contO + contB + contR + contU) * 100.0);
		printf("Ruim (U): %.2f%%\n\n", (float)contU / (contO + contB + contR + contU) * 100.0);

		if (contO + contB > contR + contU)
		{
			printf("A soma das respostas 'O' e 'B' e maior do que a soma das respostas 'R' e 'U'.\n");
		}
		else if (contO + contB < contR + contU)
		{
			printf("A soma das respostas 'O' e 'B' e menor do que a soma das respostas 'R' e 'U'.\n");
		}
		else
		{
			printf("A soma das respostas 'O' e 'B' e igual à soma das respostas 'R' e 'U'.\n");
		}
	}
	else
	{
		printf("Nao houve votos");
	}

	return 0;
}