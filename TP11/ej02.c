#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../Biblioteca/getnum.h"

#define EPSILON 0.000000001
#define BLOQUE 10


struct rango {
    float min;
    float max;
};

typedef struct  {
    double *raices;
    int cantraices;
}raices ;

typedef struct {
    char *name;
    double (*pFun)(double);
} functionType;



raices Raices (struct rango UserRango, double (*funcion)(double));
void imprimeraices(raices UserRaices);

int
main(void) {
    functionType v[] = {{"seno",sin},{"coseno",cos},{"raíz",sqrt},{"exp",exp},{"log10",log10}};
    for(int i=1; i < 6 ; i++) {
        printf("%d_%s\n", i , v[i-1].name);
    }
    int opcion;
    do {
        opcion = getint("Seleccione una opcion: ");
    } while (opcion < 1 || opcion > 5);
    struct rango userIntervalo;
    do {
        userIntervalo.min = getfloat("Ingrese el minimo: ");
        userIntervalo.max = getfloat("Ingrese el maximo: ");
        if(userIntervalo.min > userIntervalo.max) {
            printf("El intervalo no es valido\n");
        }
    } while (userIntervalo.min >= userIntervalo.max);
    raices userRaices;
    userRaices = Raices(userIntervalo,v[opcion-1].pFun);
    imprimeraices(userRaices);
    free(userRaices.raices);
    return 0;
}

raices Raices (struct rango UserRango, double (*funcion)(double)) {
    double avanzo = (UserRango.max - UserRango.min) / 100000;
    raices soluciones;
    soluciones.cantraices = 0;
    soluciones.raices = NULL;
    double i = UserRango.min;
    while (i <= UserRango.max) {
        if(funcion(i) == 0 || fabs(funcion(i)) < EPSILON ||  (funcion(i) > 0 && funcion(i+avanzo) < 0) || (funcion(i) < 0 && funcion(i+avanzo) > 0)) {
            if(soluciones.cantraices % BLOQUE == 0) {
                soluciones.raices = realloc(soluciones.raices, (soluciones.cantraices + BLOQUE)*sizeof(double));
            }
            soluciones.raices[soluciones.cantraices++] = i;
        }
        i += avanzo;
    }
    soluciones.raices = realloc(soluciones.raices,(soluciones.cantraices)*sizeof(double));
    return soluciones;
}
void imprimeraices(raices userRaices) {
    if (userRaices.cantraices == 0) {
        printf("No se encontraron raíces en el intervalo dado.\n");
    } else {
        printf("Las raíces son: ");
        for (int i = 0; i < userRaices.cantraices; i++) {
            printf("%f ", userRaices.raices[i]);
        }
        printf("\n"); // Nueva línea al final
    }
}
