#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define COLS 7
#define FILS 6
#define BLOQUE 10

typedef enum {DER=0, IZQ, ABA, ARR, I_AR, I_AB, D_AR, D_AB} Tdireccion;

typedef struct posicion {
    char * palabra;
    size_t fila;
    size_t columna;
    Tdireccion direccion;
} posicion;


posicion * resolverSopa(char *diccionario[], char sopa[][COLS]);
posicion * pasopalabra(char *diccionario, char sopa[][COLS], int * fila, int * columna, int * direccionquebusco);
posicion * buscopalabra(char *diccionario, char sopa[][COLS], int *direccion, int * fila, int * columna);


int main(void) {
    char * diccionario[] = {"ARRE", "CANCION", "CAPA", "ERROR", "ORCO", "PERRO", "PERTINAZ", "REA", "RIO", ""};

    char sopa[FILS][COLS] =
       {{'X','X','X','O','X','X','X'},
        {'A','P','A','C','Y','Y','O'},
        {'Z','E','Z','R','Z','C','X'},
        {'E','R','R','O','R','X','X'},
        {'X','R','I','O','I','E','X'},
        {'X','O','X','X','O','X','X'}};

    struct posicion * res = resolverSopa(diccionario, sopa);
    // La cantidad de palabras encontradas debe ser 9
    int expected = 9;
    int count = 0;
    while ( res[count].palabra != NULL)
        printf("%s\n", res[count++].palabra);
    assert(count == expected);

    assert(strcmp(res[0].palabra,"ARRE")==0);
    assert(res[0].fila==1);
    assert(res[0].columna==2);
    assert(res[0].direccion==D_AB);

    assert(strcmp(res[3].palabra,"ORCO")==0);
    assert(res[3].fila==3);
    assert(res[3].columna==3);
    printf("%d\n", res[3].direccion);
    assert(res[3].direccion==ARR);

    assert(strcmp(res[4].palabra,"ORCO")==0);
    assert(res[4].fila==4);
    assert(res[4].columna==3);
    assert(res[4].direccion==D_AR);

    assert(strcmp(res[6].palabra,"REA")==0);
    assert(res[6].fila==3);
    assert(res[6].columna==2);
    assert(res[6].direccion==I_AR);
    free(res);
    puts("OK primera parte");

    char * diccionario2[] = {""};
    res = resolverSopa(diccionario2, sopa);
    // La cantidad de palabras encontradas debe ser 0
    expected = 0;
    count = 0;
    while ( res[count].palabra != NULL)
        printf("%s\n", res[count++].palabra);
    assert(count == expected);
    free(res);
    puts("OK sin palabras encontradas");
    return 0;
}


posicion * resolverSopa(char *diccionario[], char sopa[][COLS]) {
    posicion * solucion = malloc(sizeof(posicion)*BLOQUE); //esto no lo entiendo
    posicion * solaux;
    int i = 0;
    int w=0;
    for(; diccionario[i][0] != '\0'; i++) {
        int fila = 0, columna = 0;
        int direccionquebusco=0;
        do {
            solaux = pasopalabra(diccionario[i], sopa, &fila , &columna, &direccionquebusco);
            if(solaux != NULL) {
                if (w % 10 == 0) {
                    solucion = realloc(solucion, sizeof(posicion) * (w + BLOQUE)); //esto tampoco lo entiendo
                }
                solucion[w] = *solaux;
                w++;
            free(solaux);
            }
        } while (solaux != NULL);
    }
    solucion[w].palabra = NULL;
    return solucion;
}
posicion * pasopalabra(char *diccionario, char sopa[][COLS], int * fila, int * columna, int * direccionquebusco) {
    posicion * resultado = malloc(sizeof(posicion));
    int direcciones[8][2] = { {1,0},{-1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};
    for (int i = *direccionquebusco; i < 8; i++) {
        *direccionquebusco = i;
        resultado = buscopalabra(diccionario,sopa,direcciones[i], fila , columna);
        if (resultado != NULL) {
            resultado->direccion = *direccionquebusco;
            return resultado;
        }
    }
    *direccionquebusco = 0;
    return resultado;
}
posicion * buscopalabra(char *diccionario, char sopa[][COLS], int *direccion, int * fila, int * columna) {
    int x,y;
    posicion * aparece = NULL;
    int w=0;
    for(int i = *fila; i<FILS; i++) {
        for (int j = *columna ; j < COLS; j++) {
            if (sopa[i][j] == diccionario[w]) {
                y=i;
                x=j;
                w=0;
                while (diccionario[w] != 0 && y >= 0 && y < FILS && x >= 0 && x < COLS && sopa[y][x] == diccionario[w]) {
                    if(diccionario[w+1] == 0) {
                        aparece = malloc(sizeof(posicion));
                        aparece->columna=j;
                        aparece->fila=i;
                        aparece->palabra = malloc(strlen(diccionario)+1);
                        strcpy(aparece->palabra,diccionario);
                        *fila = i;
                        *columna = j+1;
                        return aparece;
                    }
                        x+=direccion[0];
                        y+=direccion[1];
                        w++;
                }
                w=0;
            }
        }
    }
    *fila = 0;
    *columna = 0;
    return NULL;
}

