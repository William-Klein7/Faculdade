#include <stdio.h>
int main()
// Uma lanchonete possui o seguinte cardápio:

// Código                  Produto                Valor (R$)
// 1                       Refrigerante              2,50
// 2                       Bolo                      3,50
// 3                       Torrada                   4,50
// 4                       Picadinho                 10,00
// 5                       Agua mineral              2,00
// Faça um programa que controle a venda destes produtos.
// Um cliente deve ser capaz de comprar quantos produtos ele desejar.
// O programa deve solicitar o código do produto e quantidade.
// A compra deve ser finalizada quando for digitado o valor 99.
// Nesse momento deve ser mostrado o valor total que o cliente deve pagar.
// Simule a situação onde um cliente compra 2 refrigerantes + 1 picadinho + 1 bolo
// (total a pagar = R$ 18,50).

// **** Para esse exercício você deve OBRIGATÓRIAMENTE  usar o comando switch

{
    int num;
    float soma = 0;
    printf("escolha de produto:\nCodigo     Produto    Valor (R$)\n  1      Refrigerante   2,50 \n  2      Bolo           3,50\n  3      Torrada        4,50\n  4      Picadinho      10,00 \n  5      Agua mineral   2,00\n");
    do
    {
        printf("digite o codigo do produto ou 99 para finaliza: ");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
            soma += 2.50;
            break;

        case 2:
            soma += 3.50;
            break;

        case 3:
            soma += 4.50;
            break;

        case 4:
            soma += 10.00;
            break;

        case 5:
            soma += 2.00;
            break;
        }

    } while (num != 99);

    printf("\nTotal a pagar: R$%.2f", soma);

    return 0;
}