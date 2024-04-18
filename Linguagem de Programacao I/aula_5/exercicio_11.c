#include <stdio.h>
int main()
// Escreva um programa completo que leia inicialmente as duas notas de um aluno,
// fornecidas pelo usuário via o teclado. Se as notas não forem suficiente para o aluno
// passar direto, o programa deve capturar a nota da terceira prova, também fornecida
// via o teclado. Como saída, o programa deve imprimir a média final do aluno, seguida  da mensagem
// “Aprovado” ou “Reprovado”, conforme o critério descrito acima.

{
	float nota1 = 0, nota2 = 0, nota3 = 0, media = 0;
	printf("Insira as duas notas do aluno:\n");
	scanf("%f", &nota1);
	scanf("%f", &nota2);
	media = (nota1 + nota2) / 2;
	if (media >= 7)
	{
		printf("Media: %.2f\n", media);
		printf("Aprovado");
	}
	else
	{
		printf("Insira a terceira nota:");
		scanf("%f", &nota3);
		media = (nota1 + nota2 + nota3) / 3;
		if (media >= 5)
		{
			printf("Media: %.2f\n", media);
			printf("Aprovado");
		}
		else
		{
			printf("Media: %.2f\n", media);
			printf("Reprovado");
		}
	}
	return 0;
}