#include <stdio.h>
int main()
// Faça um programa que leia um número do teclado entre 0 e 10.
// Se o número digitado for maior que 10 uma mensagem de erro deverá ser apresentada.
// Caso contrário mostrar o dobro do valor digitado.
// Para esse programa OBRIGATÓRIAMENTE o comando switch deverá ser utilizado

{
	int num, soma = 0;

	scanf("%d", &num);
	
	switch (num)
	{
	case 1:
		soma = num * 2;
		printf("%d", soma);
		break;
	case 2:
		soma = num * 2;
		printf("%d", soma);
		break;
	case 3:
		soma = num * 2;
		printf("%d", soma);
		break;
	case 4:
		soma = num * 2;
		printf("%d", soma);
		break;
	case 5:
		soma = num * 2;
		printf("%d", soma);
		break;
	case 6:
		soma = num * 2;
		printf("%d", soma);
		break;
	case 7:
		soma = num * 2;
		printf("%d", soma);
		break;
	case 8:
		soma = num * 2;
		printf("%d", soma);
		break;
	case 9:
		soma = num * 2;
		printf("%d", soma);
		break;

	default:
		printf("ERRO NUMERO MAIOR QUE 10");
		break;
	}

	return 0;
}