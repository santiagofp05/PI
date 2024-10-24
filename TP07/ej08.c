#include <stdio.h>
#include <stdlib.h>
#include "../Biblioteca/getnum.h"
#include "../Biblioteca/random.h"
#define cantBolillas 90
typedef unsigned int TipoLinea[5];
typedef TipoLinea TipoCarton [3];


void GenerarCarton(TipoCarton carton, unsigned int *copiabolillero);
int Jugar(unsigned int *bolillero, TipoCarton jugador1, TipoCarton jugador2);
int SacarBolilla(unsigned int *bolillero ,unsigned int *bolillasrestantes);
int ControlarCarton(TipoCarton carton, unsigned int bolillasacada);
void ImprimirCarton(TipoCarton carton);
int BuscarBolilla(TipoCarton carton, unsigned int bolillasacada);
int ControlarLineas(unsigned int *linea);

int
main(void) {
    int ganador;
    TipoCarton jugador1;
    TipoCarton jugador2;
    randomize();
    unsigned int bolillero[(cantBolillas)];
    for(int i = 0; i < cantBolillas; i++) {
        bolillero[i] = i+1;
    }
    GenerarCarton(jugador1, bolillero);
    GenerarCarton(jugador2, bolillero);
    ganador = Jugar(bolillero, jugador1, jugador2);
    if (ganador == 1) {
        printf("El ganador es el jugador 1");
    }
    else {
        printf("El ganador es el jugador 2");
    }
}
void GenerarCarton(unsigned int carton[3][5], unsigned int *copiabolillero) {
    unsigned int aux, lugar;
    for(int i=0; i < cantBolillas; i++) {
        aux = copiabolillero[i];
        lugar = randInt(0,cantBolillas-1);
        copiabolillero[i] = copiabolillero[lugar];
        copiabolillero[lugar] = aux;
    }
    for(int i = 0; i < 3 ; i++) {
        for(int j=0; j < 5 ; j++) {
            carton[i][j] = copiabolillero[i*5+j];
        }
    }
}

int Jugar(unsigned int *bolillero, TipoCarton jugador1, TipoCarton jugador2) {
    int aux,lugar;
    int bolillasacada, ganador=0;
    int filacompletaj1=0, filacompletaj2=0, primerganadordelinea=0;
    int *bolillasrestantes;
    int bolitas = 90;
    bolillasrestantes = &bolitas;
    for(int i=0; i < cantBolillas; i++) {
        aux = bolillero[i];
        lugar = randInt(0,cantBolillas-1);
        bolillero[i] = bolillero[lugar];
        bolillero[lugar] = aux;
    }
    for(int i=0; i<cantBolillas && ganador == 0; i++) {
        bolillasacada = SacarBolilla (bolillero, bolillasrestantes);
        filacompletaj1 = ControlarCarton(jugador1,bolillasacada);
        filacompletaj2 = ControlarCarton(jugador2,bolillasacada);
        if (filacompletaj1 == 3) {
            ganador = 1;
        }
        else if (filacompletaj2 == 3) {
            ganador = 2;
        }
        printf("Carton Jugador 1: \n");
        ImprimirCarton(jugador1);
        printf("Carton Jugador 2: \n");
        ImprimirCarton(jugador2);
        if (primerganadordelinea == 0 && filacompletaj1 > filacompletaj2) {
            printf("El primer jugador en completar una linea fue el jugador 1\n");
            primerganadordelinea = 1;
        }
        else if (primerganadordelinea == 0 && filacompletaj1 < filacompletaj2 ) {
            printf("El primer jugador en completar una linea fue el jugador 2\n");
            primerganadordelinea = 1;
        }
    }
    return ganador;
}

int SacarBolilla(unsigned int *bolillero ,unsigned int *bolillasrestantes) {
    unsigned int aux;
    aux = bolillero[(*bolillasrestantes-1)];
    *bolillasrestantes -= 1;
    return aux;
}
void ImprimirCarton(TipoCarton carton) {
    for(int i=0; i < 3; i++) {
        for(int j=0; j<5; j++) {
            if (carton[i][j] != 0) {
                printf("%d ",carton[i][j]);
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    putchar('\n');
}
int ControlarCarton(TipoCarton carton, unsigned int bolillasacada) {
    int aux, aux1, filacompleta=0;
    aux = BuscarBolilla(carton, bolillasacada);
    if (aux == 1) {
        for(int i=0; i < 3; i++) {
            aux1 = ControlarLineas(carton[i]);
            filacompleta+=aux1;
        }
    }
    return filacompleta;
}
int BuscarBolilla(TipoCarton carton, unsigned int bolillasacada) {
    int encontre = 0;
    for (int i=0; i<3 && encontre == 0; i++) {
        for(int j=0; j<5 && encontre == 0; j++) {
            if (carton[i][j] == bolillasacada) {
                encontre = 1;
                carton[i][j] = 0;
            }
        }
    }
    return encontre;
}
int ControlarLineas(unsigned int *linea) {
    for(int j=0; j<5; j++) {
        if (linea[j] != 0) {
            return 0;
        }
    }
    return 1;
}
