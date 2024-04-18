/* 7) Assumindo que M1[] é um vetor do tipo int, quais das seguintes  expressões referenciam o valor do terceiro elemento de M1?
a) *(M1 + 2)          b) *(M1 + 4)             c) M1 + 4                       d) M1 + 2 */
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int m1[5]={1,2,3,4,5};
	printf("elemento 3: %d",*(m1+2));
	return 0;
}
// RESPOSTA: LETRA A; 
//Letra B daria o quinto elemento; As letras C e D aumentariam o ponteiro resultando em overflow, nesse caso.
