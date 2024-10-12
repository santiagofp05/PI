#include <stdio.h>
#include <math.h>


#include "../Biblioteca/getnum.h"
#include "../Biblioteca/random.h"
#define X 4

void GenerAleatorio(unsigned int v[X]);
int elegirNivel();
void leerNumero(unsigned int v1[X]);
int coincideNumero(const unsigned int v[X],const unsigned int v1[X]);
int cantidadBien(const unsigned int v[X],const unsigned int v1[X]);
int cantidadRegular(const unsigned int v[X],const unsigned int v1[X]);


int
main(void) {
    unsigned int v[X];
    unsigned int v1[X];
    int intentos;
    int cantbien=0, cantregular=0;
    randomize();
    GenerAleatorio(v);
    printf("Debe adivinar un número de %d digitos\n", X);
    intentos = elegirNivel();
    for(int i=0; i < intentos; i++) {
        leerNumero(v1);
        if(coincideNumero(v,v1) == 0) {
            printf("Adivinaste el numero!!");
            return 0;
        }
    cantbien = cantidadBien(v, v1);
    cantregular = cantidadRegular(v, v1);
    printf("%d bien, %d regular \n", cantbien , cantregular - cantbien );

    }
    printf("Lo siento perdiste, el numero era: ");
    for (int i = 0 ; i < X ; i++) {
         printf("%d", v[i]);
    }
}

void GenerAleatorio(unsigned int v[X]) {
    int numeros[9] = {1,2,3,4,5,6,7,8,9};
    int aux, numrandom;
    for(int i = 0; i < 9 ; i++) {
        aux = numeros[i];
        numrandom = randInt(0,8);
        numeros[i] = numeros[numrandom];
        numeros[numrandom] = aux;
    }
    for (int i = 0; i < X ; i++) {
        v[i] = numeros[i];
    }
}
int elegirNivel() {
    int nivel;
    nivel = getint("Ingrese la cantidad de intentos que desea tener: ");
    return  nivel;
}
void leerNumero(unsigned int v1[X]) {
    int num, numvalido, digit;
    do {
        numvalido = 0;
        int vec[10] = {0};
        printf("Igrese un numero de %d digitos distintos: ", X);
        num = getint("");
            if (num < pow(10, X-1) || num > pow(10, X)-1) {
                numvalido = 1;
                printf("El numero ingresado no tiene la cantidad de cifras solicitadas\n");
            }
            else {
            for(int i=X-1; i >= 0 && numvalido == 0; i--) {
                digit = num % 10;
                num /= 10; // Reducir num eliminando el último dígito
                if (vec[digit] == 0) {
                    vec[digit]++;
                    v1[i] = digit;
                } else {
                    printf("El numero ingresado tiene digitos repetidos\n");
                    numvalido = 1;
                }
            }
        }
    } while (numvalido == 1);
}

int coincideNumero(const unsigned int v[X],const unsigned int v1[X]) {
    int soniguales=0;
    for(int i = 0; i < X ; i++) {
        if (v[i] != v1[i]) {
            soniguales = 1;
        }
    }
    return soniguales;
}

int cantidadBien(const unsigned int v[X],const unsigned int v1[X]) {
    int cantbien=0;
    for(int i=0 ; i < X ; i++) {
        if (v[i] == v1[i]) {
            cantbien++;
        }
    }
    return cantbien;
}
int cantidadRegular(const unsigned int v[X],const unsigned int v1[X]) {
    int cantregular=0;
    for (int i=0; i < X ; i++) {
        for (int j=0; j < X ; j++) {
            if (v[i] == v1[j]) {
                cantregular++;
            }
        }
    }
    return cantregular;
}
