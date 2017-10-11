// Implemente un programa que, dado el nombre de una persona, imprima las iniciales de la personas, como se muestra abajo.

// $ ./iniciales_facil
// Regulus Arcturus Black
// RAB
#include<cs50.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

void print_initials(string full_name);

int main(void) {
    printf("Escribe tu nombre completo: ");
    string full_name = get_string();
    print_initials(full_name);
}

void print_initials(string full_name) {
    for(int i = 0, n = strlen(full_name); i < n; i++ ) {
        if(isupper(full_name[i])) {
            printf("%c", full_name[i]);
        }
    }
    printf("\n");
}
