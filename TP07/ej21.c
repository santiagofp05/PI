#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK 10
typedef char *TAlumnos[];

char ** aprobados(TAlumnos alumnos, int notas[]);
void liberaAprobados(char **alumAprob);

int main(void){

    TAlumnos alumnos = {"Juan", "Pedro", "Martin", ""};
    int notas[] = {1, 4, 10, 2, 10, 11};

    char ** apr = aprobados(alumnos, notas);
    if(apr == NULL){
        puts("No hay suficiente memoria!");
        return 1;
    }
    assert(!strcmp(alumnos[1], apr[0]) && !strcmp(alumnos[2], apr[1]) && !strcmp(alumnos[3], apr[2]));

    liberaAprobados(apr);

    puts("OK");
    return 0;
}

char ** aprobados(TAlumnos alumnos, int notas[]) {
    int cantAprob = 0;
    char **alumAprob=NULL;
    for (int i = 0; alumnos[i][0] != '\0'; i++) {
        if (notas[i] >= 4){
            if (cantAprob % BLOCK == 0){
                alumAprob = realloc(alumAprob, (cantAprob + BLOCK) * sizeof(char *));
            }
            alumAprob[cantAprob] = malloc(strlen(alumnos[i]) + 1);
            strcpy(alumAprob[cantAprob++], alumnos[i]);
        }
    }
    alumAprob = realloc(alumAprob, (cantAprob+1) * sizeof(char *));
    alumAprob[cantAprob] = "";
    return alumAprob;
}
void liberaAprobados(char **alumAprob) {
    for (int i = 0; alumAprob[i][0] != '\0'; i++) {
        free(alumAprob[i]); // Libera cada string individual
    }
    free(alumAprob); // Libera el arreglo de punteros
}
