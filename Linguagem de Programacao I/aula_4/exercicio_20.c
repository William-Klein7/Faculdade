#include <stdio.h>
#define tam 50
int main()
// Faca um programa que leia uma string fornecida pelo usuario.
// A seguir leia uma segunda string. Verifique então se a segunda string está inserida
// dentro da primeira.Por exemplo: Se a primeira string for "linguagem" e a segunda for "lingua"
// o programa deve mostrar "estah inserida".
// (limite o tamanho das duas strings em 50 caracteres)

{
	char v1[tam], v2[tam], cont = 0;

	printf("Insira a primeira string: ");
	fgets(v1, sizeof(v1), stdin);

	printf("Insira a segunda string: ");
	fgets(v2, sizeof(v2), stdin);

	v1[strlen(v1) - 1] = '\0';
	v2[strlen(v2) - 1] = '\0';

	for (int i = 0; v1[i] != '\0'; i++)
	{
		if (v1[i] == v2[i])
		{
			cont = 1;
			break;
		}
	}

	if (cont == 1)
	{
		printf("estah contida");
	}
	else
	{
		printf("nao esta contida");
	}

	return 0;
}