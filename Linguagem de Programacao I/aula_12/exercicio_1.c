#include <stdio.h>
#include <stdlib.h>
// Escrever uma funcao void datecpy(struct data *dt1, struct data dt2), que atribui o conteúdo
// de dt2 para dt1.

// struct data da={1,5,1999}, db={15,8,1980};
// datecpy(&da, &db); /* copia db para da */

#include <stdio.h>

struct data
{
	int dia;
	int mes;
	int ano;
};

void datecpy(struct data *dt1, struct data *dt2);

void datecpy(struct data *dt1, struct data *dt2)
{
	dt1->dia = dt2->dia;
	dt1->mes = dt2->mes;
	dt1->ano = dt2->ano;
}

int main()
{
	struct data da = {1, 5, 1999};
	struct data db = {15, 8, 1980};

	datecpy(&da, &db);

	printf("da: %d/%d/%d\n", da.dia, da.mes, da.ano);
	printf("db: %d/%d/%d\n", db.dia, db.mes, db.ano);

	return 0;
}
