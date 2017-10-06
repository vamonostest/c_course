//Implemente el cifrado de Cesar, como se muestra abajo.

//$ ./cifrado_cesar 13
//mensaje inicial:  HELLO
//mensaje cifrado: URYYB
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void cifrar(string mensaje, int c);
void imprimir_caracter(char ch, int c);
int main(int argc, string argv[]) {
    if(argc == 2) {
        int c = atoi(argv[1]);
        printf("mensaje inicial: ");
        string mensaje_inicial = get_string();
        cifrar(mensaje_inicial, c);
    }
}

void cifrar(string mensaje, int c) {
    printf("mensaje cifrado: ");
    for(int i = 0, n = strlen(mensaje); i < n; i++ ) {
        imprimir_caracter(mensaje[i], c);
    }
    printf("\n");
}

void imprimir_caracter(char ch, int c) {
    if(isalpha(ch) && isupper(ch)) {
        printf("%c", (((ch - 65) + c) % 26) + 65 );

    }
    else if(isalpha(ch) && islower(ch)) {
        printf("%c", (((ch - 97) + c) % 26) + 97 );
    }
    else {
        printf("%c", ch);
    }
}
