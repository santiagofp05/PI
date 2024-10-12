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
    for(; diccionario[i][0] != '\0'; i++) { //recorro el diccionario buscando palabra a palabra
        int fila = 0, columna = 0;
        int direccionquebusco=0; //la paso como parametro para luego no volver a buscar una palabra donde ya la busque y darle el valor a la estructura
        do {
            solaux = pasopalabra(diccionario[i], sopa, &fila , &columna, &direccionquebusco); //guardo la estructura en solaux
            if(solaux != NULL) { //si es distinto de NULL significa que encontre la palabra
                if (w % 10 == 0) {
                    solucion = realloc(solucion, sizeof(posicion) * (w + BLOQUE)); //esto tampoco lo entiendo
                }
                solucion[w] = *solaux;
                w++;
            free(solaux);
            }
        } while (solaux != NULL); //esto es para que si se encontró la palabra que la siga buscando por si aparece otra vez
    }
    solucion[w].palabra = NULL; 
    return solucion;
}
posicion * pasopalabra(char *diccionario, char sopa[][COLS], int * fila, int * columna, int * direccionquebusco) {
    posicion * resultado = malloc(sizeof(posicion)); //esto tampoco lo entiendo
    int direcciones[8][2] = { {1,0},{-1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};
    for (int i = *direccionquebusco; i < 8; i++) { //recorro las 8 direcciones y ademas i = direccionquebusco por si una palabra aparece mas de 1 vez para no volver a buscar donde ya se que no esta
        *direccionquebusco = i; //guardo la direccion que estoy buscando para luego guardarlo en la estructura
        resultado = buscopalabra(diccionario,sopa,direcciones[i], fila , columna);
        if (resultado != NULL) { // si resultado es != de NULL significa que encontro la palabra
            resultado->direccion = *direccionquebusco; //guardo en la estructura la direccion y ya me quedan las 4 variables cubiertas
            return resultado; //devuelvo la estructura
        }
    }
    *direccionquebusco = 0;
    return resultado; //esto seria como devolver NULL porque si encuentro la palabra la devuelvo antes
}
posicion * buscopalabra(char *diccionario, char sopa[][COLS], int *direccion, int * fila, int * columna) {
    int x,y;
    posicion * aparece = NULL; //esto no lo entiendo
    int w=0;
    for(int i = *fila; i<FILS; i++) {
        for (int j = *columna ; j < COLS; j++) { //recorro la matriz buscando si la primera letra de la palabra coincide con la que hay en la posicion de la matriz
            if (sopa[i][j] == diccionario[w]) {
                y=i; //guardo el valor de las filas en y para luego si encuentro la palabra no perder el lugar donde estaba la primera letra
                x=j; // guardo el valor de las columnas en x para luego si encuentro la palabra no perder el lugar donde estaba la primera letra
                w=0; //asigno 0 a la w para ir recorriendo la palabra
                while (diccionario[w] != 0 && y >= 0 && y < FILS && x >= 0 && x < COLS && sopa[y][x] == diccionario[w]) { //me fijo que no me haya salido de la matriz y por ultimo que coincidan las letras
                    if(diccionario[w+1] == 0) { //si la siguiente letra es el 0 es que ya encontro toda la palabra
                        aparece = malloc(sizeof(posicion)); //esto lo entiendo maso menos
                        aparece->columna=j;
                        aparece->fila=i;
                        aparece->palabra = malloc(strlen(diccionario)+1); //le doy a palabra espacio suficiente para copiar la palabra
                        strcpy(aparece->palabra,diccionario); //copio la palabra en la estructura que voy a devolver
                        *fila = i; //le doy a *fila el valor de i para que cuando vuelva a recorrer la matriz no recorra nuevamente lugares que ya recorrió
                        *columna = j+1; //le doy a *columna el valor de j+1 para que cuando vuelva a buscar arranque por la siguiente letra a la anterior
                        return aparece; //devuelvo la estrctura con el valor de la fila y columan donde aparece la palabra y que palabra es o sea solo me queda pendiente en que direccion aparece
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
    *columna = 0; //les vuelvo a poner el valor de 0 para que cuando vuelva a buscar por otra direccion arranque desde el principio de la matriz
    return NULL; //si encontre la palabra la devolvi antes
}

