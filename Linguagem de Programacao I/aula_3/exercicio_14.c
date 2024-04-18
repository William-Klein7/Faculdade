#include <stdio.h>
int main()
// Um marciano chegou a uma floresta e se escondeu atrás de uma das 100 árvores quando viu
// um caçador. O caçador só tinha cinco balas em sua espingarda. Cada vez que ele atirava,
// e não acertava, é claro, o marciano dizia: “estou mais à direita ou mais à esquerda.
// Se o caçador não conseguir acertar o marciano, ele será levado para marte.
// Implementar este jogo para dois jogadores, onde um escolhe a árvore em que o marciano irá
// se esconder, e o outro tenta acertar.
// (Sugestão: utilize números para representar as árvores)

{
	int j1 = 0, j2 = 0;

	printf("Escolha um numero de 1 a 100 para o marciano se esconder: ");
	scanf("%d", &j1);

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

		if (i > 1)
		{
			if (j1 == j2)
			{
				printf("Voce venceu.");
				break;
			}
			else if (j2 > j1)
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
			if (j1 == j2)
			{
				printf("Voce venceu.");
				break;
			}
			else if (j2 > j1)
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