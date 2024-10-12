#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../Biblioteca/getnum.h"
#define FUNCION(x) ((x) * (x) - 4)
#define EPSILON 0.0000000000001
#define BLOQUE 10

struct intervalos {
    double min;
    double max;
    int subintervalo;
};

struct raices {
    double *raices;
    int dim;
};

struct raices busquedaraices(struct intervalos userIntervalo);
void imprimeraices(struct raices userRaices);

int
main(void) {
    struct intervalos userIntervalo;
    struct raices userRaices;
    do {
        userIntervalo.min = getfloat("Ingrese el minimo intervalo: ");
        userIntervalo.max = getfloat("Ingrese el maximo intervalo: ");
        if(userIntervalo.min > userIntervalo.max) {
            printf("El intervalo no es valido\n");
        }
    } while (userIntervalo.min >= userIntervalo.max);
    userRaices = busquedaraices(userIntervalo);
    imprimeraices(userRaices);
    free(userRaices.raices);
    return 0;
}

struct raices busquedaraices(struct intervalos userIntervalo) {
    struct raices userRaices;
    double evaluacion;
    userRaices.raices = NULL;
    userRaices.dim = 0;
    userIntervalo.subintervalo = 100000;
    evaluacion = (userIntervalo.max - userIntervalo.min)/userIntervalo.subintervalo;
    double i = userIntervalo.min;
    while(i <= userIntervalo.max) {
        if (fabs(FUNCION(i)) < EPSILON || (FUNCION(i) < 0 && i != userIntervalo.max && FUNCION(i + evaluacion) > 0) || (FUNCION(i) > 0 && i != userIntervalo.max && FUNCION(i + evaluacion) < 0)) {
            if (userRaices.dim % BLOQUE == 0) {
                userRaices.raices = realloc(userRaices.raices,(userRaices.dim + BLOQUE)*sizeof(double));
            }
            userRaices.raices[userRaices.dim++] = i;
        }
        i += evaluacion;
    }
    userRaices.raices = realloc(userRaices.raices,(userRaices.dim)*sizeof(double));
    return userRaices;
}

void imprimeraices(struct raices userRaices) {
    if (userRaices.dim == 0) {
        printf("No se encontraron raíces en el intervalo dado.\n");
    } else {
        printf("Las raíces son: ");
        for (int i = 0; i < userRaices.dim; i++) {
            printf("%f ", userRaices.raices[i]);
        }
        printf("\n"); // Nueva línea al final
    }
}