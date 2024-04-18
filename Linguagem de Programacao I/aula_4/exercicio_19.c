#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char string[51];
    printf("Digite uma string (limite de 50 caracteres): ");
    fgets(string, sizeof(string), stdin);

    int letras[26] = {0};
    int cont = 0;

    for (int i = 0; string[i] != '\0'; i++) {
        char c = tolower(string[i]);

        if (isalpha(c)) {
            if (letras[c - 'a']++ == 1) {
                cont++;
            }
        }
    }

    printf("Quantidade de letras repetidas: %d\n", cont);

    return 0;
}