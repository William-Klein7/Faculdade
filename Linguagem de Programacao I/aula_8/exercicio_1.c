#include <stdio.h>
#include <conio.h>

// Qual serão as saídas do seguinte programa? Explique o motivo.

int main() {
int    valor;
int   *p1;
float  temp;
float *p2;
char   aux;
char  *nome = "Algoritmos";
char  *p3;
int    idade;
int    vetor[3];
int   *p4;
int   *p5;

/* (a) */
valor = 10;

p1 = &valor;
*p1 = 20;
printf("(a) %d \n", valor);
// (a) O valor da variável valor é definido como 10, depois é criado um ponteiro p1 apontando para valor, 
// e o valor de valor é alterado para 20. Portanto, a saída será 20.

/* (b) */
temp = 26.5;
p2 = &temp;
*p2 = 29.0;
printf("(b) %.1f \n", temp);
// (b) Similar ao (a), o valor da variável temp é definido como 26.5, um ponteiro p2 é criado apontando para 
// temp, e o valor de temp é alterado para 29.0. A saída será 29.0.

/* (c) */
p3 = &nome[0];
aux = *p3;
printf("(c) %c \n", aux);
// (c) O ponteiro p3 aponta para o primeiro caractere da string "Algoritmos", que é 'A'. 
// O valor é então armazenado na variável aux e impresso. A saída será A.

/* (d) */
p3 = &nome[4];
aux = *p3;
printf("(d) %c \n", aux);
// (d) O ponteiro p3 é movido para o quarto caractere da string, que é 'r'. 
// O valor é armazenado na variável aux e impresso. A saída será r.

/* (e) */
p3 = nome;
printf("(e) %c \n", *p3);
// (e) O ponteiro p3 volta a apontar para o primeiro caractere da string. 
// O valor é impresso novamente. A saída será A.

/* (f) */
p3 = p3 + 4;
printf("(f) %c \n", *p3);
// (f) O ponteiro p3 é movido para o quarto caractere novamente e o valor é impresso. A saída será r.

/* (g) */
p3--;
printf("(g) %c \n", *p3);
// (g) O ponteiro p3 é decrementado, apontando para o terceiro caractere da string, que é 'o'. 
// O valor é impresso. A saída será o.

/* <h> */
vetor[0] = 31;
vetor[1] = 45;
vetor[2] = 27;
p4 = vetor;
idade = *p4;
printf("(h) %d \n", idade);
// (h) O array vetor é inicializado com três valores, e p4 é configurado para apontar para o 
// primeiro elemento do array. O valor idade é definido como o valor apontado por p4, que é 31. A saída será 31.

/* (i) */
p5 = p4 + 1;
idade = *p5;
printf("(i) %d \n", idade);
// (i) p5 é configurado para apontar para o segundo elemento do array, e o valor idade é definido 
// como o valor apontado por p5, que é 45. A saída será 45.

/* (j) */
p4 = p5 + 1;
idade = *p4;
printf("(j) %d \n", idade);
// (j) p4 é movido para apontar para o terceiro elemento do array, e o valor idade é definido como o 
// valor apontado por p4, que é 27. A saída será 27.

/* (l) */
p4 = p4 - 2;
idade = *p4;
printf("(l) %d \n", idade);
// (l) p4 é movido de volta para apontar para o primeiro elemento do array, e o valor idade é definido como 31 novamente.
// A saída será 31.

/* (m) */
p5 = &vetor[2] - 1;
printf("(m) %d \n", *p5);
// (m) p5 é configurado para apontar para o primeiro elemento do array (vetor[2] - 1), 
// e o valor é impresso. A saída será 45.

/* (n) */
p5++;
printf("(n) %d \n", *p5);
// (n) p5 é incrementado para apontar para o segundo elemento do array, e o valor é impresso. 
// A saída será 27.

return(0);
}