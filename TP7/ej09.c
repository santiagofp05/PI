#include <stdio.h>
#include <stdlib.h>
#include "../Biblioteca/getnum.h"
#include "../Biblioteca/random.h"
#define cantBolillas 90
typedef unsigned int TipoLinea[5];
typedef TipoLinea TipoCarton [3];
#define jugadores 10
typedef TipoCarton TipoCartones[jugadores];


void GenerarCartones(TipoCartones cartones, unsigned int *copiabolillero);
void GenerarCarton(TipoCarton carton, unsigned int *copiabolillero);
int Jugar(unsigned int *bolillero, TipoCartones cartones);
int SacarBolilla(unsigned int *bolillero ,unsigned int *bolillasrestantes);
int ControlarCarton(TipoCarton carton, unsigned int bolillasacada);
void ImprimirCarton(TipoCarton carton);
int BuscarBolilla(TipoCarton carton, unsigned int bolillasacada);
int ControlarLineas(unsigned int *linea);

int main(void) {
    int ganador;
    TipoCartones jugadoresCartones;
    randomize();
    unsigned int bolillero[cantBolillas];

    for (int i = 0; i < cantBolillas; i++) {
        bolillero[i] = i + 1;
    }
    GenerarCartones(jugadoresCartones, bolillero);
    ganador = Jugar(bolillero, jugadoresCartones);

    printf("El ganador es el jugador %d\n", ganador);
}
void GenerarCartones(TipoCartones cartones, unsigned int *copiabolillero) {
    for (int i = 0; i < jugadores; i++) {
        GenerarCarton(cartones[i], copiabolillero);
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

int Jugar(unsigned int *bolillero, TipoCartones cartones) {
    int bolillasacada, ganador = 0;
    int filacompleta[jugadores] = {0};
    int primerganadordelinea = 0;
    int *bolillasrestantes;
    int bolitas = 90;
    bolillasrestantes = &bolitas;

    for (int i = 0; i < cantBolillas && ganador == 0; i++) {
        bolillasacada = SacarBolilla(bolillero, bolillasrestantes);

        for (int j = 0; j < jugadores; j++) {
            filacompleta[j] = ControlarCarton(cartones[j], bolillasacada);
            if (filacompleta[j] == 3) {
                ganador = j + 1;  // Jugador `j` ganó.
            }
        }
        printf("Estado de los cartones:\n");
        for (int j = 0; j < jugadores; j++) {
            printf("Carton Jugador %d:\n", j + 1);
            ImprimirCarton(cartones[j]);
        }
        if (primerganadordelinea == 0) {
            for (int j = 0; j < jugadores; j++) {
                if (filacompleta[j] > 0) {
                    printf("El primer jugador en completar una línea fue el jugador %d\n", j + 1);
                    primerganadordelinea = 1;
                    break;
                }
            }
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
