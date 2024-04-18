/* 8) Qual o valor de Y no final do programa? Tente primeiro descobrir e depois verifique no computador o resultado.*/
#include<stdio.h>
int main() {
int y, *p, x;
y = 0;
p = &y;
x = *p;
x = 4;
(*p)++;

(*p) += x;
printf ("y = %d\n", y);
return(0);
}
// Y==5
