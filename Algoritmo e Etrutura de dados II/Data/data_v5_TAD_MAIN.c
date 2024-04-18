#include <stdio.h>

typedef struct
{
  int dia, mes, ano;
} data;

void setdia(data *d, int _dia)
{
  d->dia = _dia;
}
void setmes(data *d, int _mes)
{
  d->mes = _mes;
}
void setano(data *d, int _ano)
{
  d->ano = _ano;
}
int getdia(data *d)
{
  return d->dia;
}
int getmes(data *d)
{
  return d->mes;
}
int getano(data *d)
{
  return d->ano;
}
void setdata(data *d, int _dia, int _mes, int _ano)
{
  d->dia = _dia;
  d->mes = _mes;
  d->ano = _ano;
}
void setdata_inteira(data *d, int _inteira)
{
  int dia, mes, ano;

  if (_inteira < 1000000)
  {
    dia = _inteira / 10000;
    mes = (_inteira / 100) % 100;
    ano = _inteira % 100;
  }
  else
  {
    dia = _inteira / 1000000;
    mes = (_inteira / 10000) % 100;
    ano = _inteira % 10000;
  }
  setdia(d, dia);
  setmes(d, mes);
  setano(d, ano);
}

int main(void)
{
  int i, data_inteira;
  data d[2];
  for (i = 0; i < 2; i++)
  {
    printf("Informe a Data[%d]: ", i);
    scanf("%d", &data_inteira);
    setdata_inteira(&d[i], data_inteira);
  }
  printf("1aData: %d-%d-%d\n", getdia(&d[0]), getmes(&d[0]), getano(&d[0]));
  printf("2aData: %d-%d-%d\n", getdia(&d[1]), getmes(&d[1]), getano(&d[1]));
  system("pause");
}
