#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Biblioteca/random.h"
#define DIM 15

int Jugar(char *palabra); //devuelve 1 si adivino y 0 si no
void leerCaracter(char *palabra, char *palabrausuario, int *intentos, int *gano);
void leerCaracterBack(char *palabra, char *palabrausuario, char c, int *intentos, int *gano);
void controlar(char *palabra, char *palabrausuario, char letra, int *intentos);

int
main(void) {
    int aux, longitud;
    randomize();
    char *Palabras[]= {"murcielago", "carretera", "computadora", "bicicleta", "revolucion", "bicicleta", "marinero", "astronauta", "ventilador", "cangrejo", "invernadero", "palangana", "electricidad", "ferrocarril", "dinosaurio"};
    aux = randInt(0, DIM-1);
    longitud = strlen(Palabras[aux]);
    printf("Debes adivinar una palabra de %d letras y tiene 7 intentos\n", longitud);
    if (Jugar(Palabras[aux]) == 1) {
        printf("Adivinaste la palabra!!\n");
    }
    else {
        printf("Lo siento, la palabra era: ");
        printf("%s", Palabras[aux]);
    }
}

int Jugar(char *palabra) {
    char *palabrauser;
    int longitudpalabra;
    int intentos = 7, gano = 0; //1 intento la cabeza, 1 el cuerpo, 2 las manos, 2 las piernas, 1 la cuerda
    longitudpalabra = strlen(palabra);
    palabrauser = malloc((longitudpalabra+1) * sizeof(char));
    for(int i=0; i<longitudpalabra; i++) {
        palabrauser[i] = '_'; //Pongo _ en la palabra que va ingresando el usuario
    }
    palabrauser[longitudpalabra]='\0';
    while(intentos > 0 && gano == 0) {
        leerCaracter(palabra, palabrauser, &intentos, &gano); //mientras que no haya ganadado o quedado sin intentos se ejecuta este while
    }
    return gano; //el while va a terminar porque gano o pq se quedo sin intentos entonces devuelvo gano

}
void leerCaracter(char *palabra, char *palabrausuario, int *intentos, int *gano) {
    char c;
    do {
        *gano = 1;
        printf("Ingrese una letra: ");

        while ((c = getchar()) != '\n' && *intentos > 0) {
            if(toupper(c) < 'A' || toupper(c) > 'Z') { // Verifica que sea una letra
                printf("El caracter ingresado no es una letra\n");
            } else {
                leerCaracterBack(palabra, palabrausuario, c, intentos, gano);
            }
        }
    } while (*intentos > 0 && *gano == 0);
}
void leerCaracterBack(char *palabra, char *palabrausuario, char c, int *intentos, int *gano) {
    controlar(palabra, palabrausuario, c, intentos); // Controla si la letra pertenece a la palabra

    for (int i = 0; palabrausuario[i] != '\0' && *gano == 1; i++) {
        if (palabrausuario[i] == '_') {
            *gano = 0; // Si hay un guión bajo, aún no ha ganado
        }
    }
}

void controlar(char *palabra, char *palabrausuario, char letra, int *intentos) {
    int coincide=0;
    for (int i = 0; palabra[i] != '\0' ; ++i) {
        if (palabra[i] == letra) {
            palabrausuario[i] = letra;
            coincide++;
        }
    }
    if (coincide>0) {
        printf("La letra %c aparece %d veces y queda asi: ",letra, coincide);
        for (int i=0; palabrausuario[i] != 0; i++) {
            printf("%c", palabrausuario[i]);
        }
        printf("\n");
        return;
    }
    *intentos=*intentos-1;
    printf("La letra no aparece y le quedan %d intentos\n", *intentos);
}

