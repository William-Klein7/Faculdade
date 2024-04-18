#include <stdio.h>
int main()
// Considere uma disciplina que adota o seguinte critério de aprovação:
// os alunos fazem duas provas (P1 e P2) iniciais; se a média nessas duas provas for
// maior ou igual a 5.0,  e se nenhuma das duas notas for inferior a 3.0, o aluno passa direto.
// Caso contrário, o aluno faz uma terceira prova (P3) e a média é calculada considerando-se essa
// terceira  nota e a maior das notas entre P1 e P2.
// Neste caso, o aluno é aprovado se a média final for maior ou igual a 5.0.

{
	float p1, p2, p3, media = 0;

	printf("Insira a primeira nota: ");
	scanf("%f", &p1);
	printf("Insira a segunda nota: ");
	scanf("%f", &p2);

	media = (p1 + p2) / 2;

	if (media >= 5)
	{
		if (p1 || p2 >= 3)
		{
			media = 0;
			printf("Insira a terceira nota: ");
			scanf("%f", &p3);
			if (p1 >= p2)
			{
				media = (p1 + p3) / 2;
			}
			else
			{
				media = (p2 + p3) / 2;
			}

			if (media >= 5)
			{
				printf("Aprovado");
			}
			else
			{
				printf("Reprovado");
			}
		}
		else
		{
			printf("Aprovado");
		}
	}
	else
	{
		media = 0;
		printf("Insira a terceira nota: ");
		scanf("%f", &p3);
		if (p1 >= p2)
		{
			media = (p1 + p3) / 2;
		}
		else
		{
			media = (p2 + p3) / 2;
		}

		if (media >= 5)
		{
			printf("Aprovado");
		}
		else
		{
			printf("Reprovado");
		}
	}

	return 0;
}