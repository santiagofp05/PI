#include <math.h>
#include <stdio.h>

#include "../Biblioteca/getnum.h"
#include "../Biblioteca/random.h"
#define cantdirecciones 4


struct caminoaleatorio {
    int tiempo;
    int radio;
    double relacion;
};
struct punto {
    int x;
    int y;
};

void avanzaaleatorio(struct punto *posicion, int direcciones[]);
int
main(void) {
    struct caminoaleatorio miCamino;
    struct punto posicion;
    int sumadecuadrados = 0;
    int direcciones[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
    int direccion;
    randomize();
    posicion.x = 0;
    posicion.y = 0;
    do {
        miCamino.radio = getint("Ingrese el radio que quiera que tenga el circulo: ");
    }while (miCamino.radio <= 0);
    int radiocuadrado = pow(miCamino.radio,2);
    for (miCamino.tiempo = 0; sumadecuadrados <= radiocuadrado; miCamino.tiempo++) {
        sumadecuadrados = pow(posicion.x,2) + pow(posicion.y,2);
        direccion = randInt(0,cantdirecciones-1);
        avanzaaleatorio(&posicion,direcciones[direccion]);
    }
    miCamino.relacion = ((double) miCamino.radio)/miCamino.tiempo;
    printf("La particula tardó %d segundos en salir del circulo de radio %d y la relacion de radio sobre tiempo es %f",miCamino.tiempo, miCamino.radio, miCamino.relacion);
}
void avanzaaleatorio(struct punto *posicion, int direcciones[]) {
    posicion->x += direcciones[0];
    posicion->y += direcciones[1];
}

