#include <stdio.h>
int main()
// Faça um programa que imprima a seguinte saída:
// (inicia em 10 caracteres # e passa a deslocar casas)
// ##########
// #########
// ########
// #######
// ######
// #####
// ####
// ###
// ##
// #

{
	int count = 10;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < count; j++)
		{
			printf("#");
		}
		printf("\n");
		count--;
	}

	return 0;
}