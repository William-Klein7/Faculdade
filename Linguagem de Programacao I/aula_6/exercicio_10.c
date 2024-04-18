#include <stdio.h>
int main()
// Lembra do jogo do Marciano na floresta ? Então, novamente você deve implementa-lo novamente,
// porém agora TODAS AS VARIÁVEIS devem ser manipuladas usando ponteiros.

{
	int j1 = 0, j2 = 0;

	printf("Escolha um numero de 1 a 100 para o marciano se esconder: ");
	scanf("%d", &j1);
	int *pJ1 = &j1;

	for (int i = 5; i > 0; i--)
	{

		if (i == 1)
		{
			printf("Voce possui %d tentativa: ", i);
		}
		else
		{
			printf("Voce possui %d tentativas: ", i);
		}

		scanf("%d", &j2);
		int *pJ2 = &j2;

		if (i > 1)
		{
			if (*pJ1 == *pJ2)
			{
				printf("Voce venceu.");
				break;
			}
			else if (*pJ2 > *pJ1)
			{
				printf("O marciano esta para a esquerda\n");
			}
			else
			{
				printf("O marciano esta para a direita\n");
			}
		}
		else
		{
			if (*pJ1 == *pJ2)
			{
				printf("Voce venceu.");
				break;
			}
			else if (*pJ2 > *pJ1)
			{
				printf("Voce perdeu\n");
			}
			else
			{
				printf("Voce perdeu\n");
			}
		}
	}
	return 0;
}