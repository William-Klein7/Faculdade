/* 6) Faca um programa que leia duas strings fornecidas pelo usuario de no maximo 50 posicoes.
A seguir aloque dinamicamente uma outra string (array de caracteres)
com tamanho suficiente para armazenar as duas strings lidas previamente.
Copie o conteudo dessas duas strings para esse espaco alocado dinamicamente.
Exemplo:
String 1 --> "oi"  
String 2 --> "mundo"
Espaco alocado dinamicamente no final sera --> "oi mundo"*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char str1[50],str2[50];
	printf("Digite a primeira string: ");
    fgets(str1, 50, stdin);
    printf("Digite a segunda string: ");
    fgets(str2, 50, stdin);
    
	int tam=strlen(str1)+ strlen(str2);
	char *copia=(char *) malloc (tam + 1);
	strcpy(copia,str1);
	strcat(copia, str2);
	printf("\nEspaco alocado:\n%s",copia);
	free(copia);
	return 0;
}
