#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#include "../Biblioteca/getnum.h"
#include "../Biblioteca/random.h"

void GenerAleatorio(unsigned int *v, int dim);
int elegirNivel();
void leerNumero(unsigned int *v1, int dim);
int coincideNumero(const unsigned int *v,const unsigned int *v1, int dim);
int cantidadBien(const unsigned int *v,const unsigned int *v1, int dim);
int cantidadRegular(const unsigned int *v,const unsigned int *v1, int dim);


int
main(void) {
    int cantdigit;
    do {
        cantdigit = getint("Ingrese la cantidad de digitos entre 1 y 9 que tiene el numero que quiere adivinar: ");
        if ( cantdigit < 1 || cantdigit > 9) {
            printf("El numero ingresado no es correcto\n");
        }
    } while ( cantdigit < 1 || cantdigit > 9);

    unsigned int *v = NULL;
    unsigned int *v1 = NULL;

    v = malloc(cantdigit * sizeof(int));
    v1 = malloc(cantdigit * sizeof(int));

    int intentos;
    int cantbien=0, cantregular=0;
    randomize();
    GenerAleatorio(v, cantdigit);
    printf("Debe adivinar un número de %d digitos\n", cantdigit);
    intentos = elegirNivel();
    for(int i=0; i < intentos; i++) {
        leerNumero(v1, cantdigit);
        if(coincideNumero(v,v1,cantdigit) == 0) {
            printf("Adivinaste el numero!!");
            return 0;
        }
        {
            cantbien = cantidadBien(v, v1, cantdigit);
            cantregular = cantidadRegular(v, v1, cantdigit);
            printf("%d bien, %d regular \n", cantbien , cantregular - cantbien );
        }
    }
    printf("Lo siento perdiste, el numero era: ");
    for (int i = 0 ; i < cantdigit ; i++) {
         printf("%d", v[i]);
    }
    free(v);
    free(v1);

}

void GenerAleatorio(unsigned int *v, int dim) {
    int numeros[9] = {1,2,3,4,5,6,7,8,9};
    int aux, numrandom;
    for(int i = 0; i < 9 ; i++) {
        aux = numeros[i];
        numrandom = randInt(0,8);
        numeros[i] = numeros[numrandom];
        numeros[numrandom] = aux;
    }
    for (int i = 0; i < dim ; i++) {
        v[(i)] = numeros[i];
    }
}
int elegirNivel() {
    int nivel;
    nivel = getint("Ingrese la cantidad de intentos que desea tener: ");
    return  nivel;
}
void leerNumero(unsigned int *v1, int dim) {
    int num, numvalido, digit;
    do {
        numvalido = 0;
        int vec[10] = {0};
        printf("Igrese un numero de %d digitos distintos: ", dim);
        num = getint("");
            if (num < pow(10, dim-1) || num > pow(10, dim)-1) {
                numvalido = 1;
                printf("El numero ingresado no tiene la cantidad de cifras solicitadas\n");
            }
            else {
            for(int i=dim-1; i >= 0 && numvalido == 0; i--) {
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

int coincideNumero(const unsigned int *v,const unsigned int *v1, int dim) {
    int soniguales=0;
    for(int i = 0; i < dim ; i++) {
        if (v[i] != v1[i]) {
            soniguales = 1;
        }
    }
    return soniguales;
}

int cantidadBien(const unsigned int *v,const unsigned int *v1, int dim){
    int cantbien=0;
    for(int i=0 ; i < dim ; i++) {
        if (v[i] == v1[i]) {
            cantbien++;
        }
    }
    return cantbien;
}
int cantidadRegular(const unsigned int *v,const unsigned int *v1, int dim) {
    int cantregular=0;
    for (int i=0; i < dim ; i++) {
        for (int j=0; j < dim ; j++) {
            if (v[i] == v1[j]) {
                cantregular++;
            }
        }
    }
    return cantregular;
}
