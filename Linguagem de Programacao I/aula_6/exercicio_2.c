#include <stdio.h>
int main()
// Faca um programa que leia o valor de duas variaveis do tipo float.
// Crie dois ponteiros apontando para cada uma delas.
// A seguir mostre o endereco de memória dessas duas variaveis e seus conteúdos.
// Mostre o endereço de memória dos ponteiros,
// o conteudo deles (que será o endereços das duas variáveis) e o conteudo do local para onde eles apontam
{
	float n1, n2;
	float *p1, *p2;

	printf("Digite o valor de n1: ");
	scanf("%f", &n1);

	printf("Digite o valor de n2: ");
	scanf("%f", &n2);

	p1 = &n1;
	p2 = &n2;

	printf("Endereco de memoria de n1: %p\n", &n1);
	printf("Conteudo de n1: %.2f\n", n1);

	printf("Endereco de memoria de n2: %p\n", &n2);
	printf("Conteudo de n2: %.2f\n", n2);

	printf("Endereco de memoria de p1: %p\n", p1);
	printf("Conteudo de p1 (valor apontado): %.2f\n", *p1);

	printf("Endereco de memoria de p2: %p\n", p2);
	printf("Conteudo de p2 (valor apontado): %.2f\n", *p2);

	return 0;
}
