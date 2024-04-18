#include <stdio.h>
int main()
// Num  frigorífico  são  recebidos  um número  variável  de bois  a cada dia.
// Cada boi traz preso no seu pescoço um cartão contendo um   número   de   identificação
// e   seu   peso.   Implementar   um programa que efetue a leitura de todos números de identificação
// e peso de cada boi, exibindo ao final o número e o peso dos bois mais gordo e mais magro,
// bem como o peso médio dos bois. Um número de  identificação 0 (zero)  indica o final  da  leitura.
// Note que não é necessário armazenar os dados de todos os bois.

{
	int nBois;
	printf("Insira a quantidade de bois recebidos:\n");
	scanf("%d", &nBois);

	int vIdent[nBois];
	float vPeso[nBois];
	int boiMI = 0, boiGI = 0;
	float boiG = 0, boiM = 0, mediaBois = 0;

	for (int i = 0; i < nBois; i++)
	{
		printf("Insira o numero de identificacao do %d boi (ou 0 para finalizar): \n", i + 1);
		scanf("%d", &vIdent[i]);

		if (vIdent[i] == 0)
		{
			break;
		}

		printf("Insira o peso do %d boi: \n", i + 1);
		scanf("%f", &vPeso[i]);

		if (i == 0 || vPeso[i] > boiG)
		{
			boiG = vPeso[i];
			boiGI = vIdent[i];
		}
		if (i == 0 || vPeso[i] < boiM)
		{
			boiM = vPeso[i];
			boiMI = vIdent[i];
		}

		mediaBois += vPeso[i];
	}

	if (nBois > 0)
	{
		printf("Numero de identificacao do boi mais gordo: %d\nPeso do boi mais gordo: %.2fKg\n\n", boiGI, boiG);
		printf("Numero de identificacao do boi mais magro: %d\nPeso do boi mais magro: %.2fKg\n\n", boiMI, boiM);
		printf("Media de todos os bois: %.2fKg\n", mediaBois / nBois);
	}
	else
	{
		printf("Nenhum boi inserido.\n");
	}
	
	return 0;
}