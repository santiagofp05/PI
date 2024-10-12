#include <stdio.h>
#include <string.h>
#include "../Biblioteca/random.h"
#define cartas 52
#define valores 13 // 13 valores posibles en un mazo (1 a 13)
#define cartasextraidas 5

struct carta {
    int numero;
    char *palo;
};
struct Jugador {
    int caso;
    int valor;
};
struct mazo {
    struct carta mazo[cartas];
};

void mezclarmazo(struct mazo *miMazo);
int configuraciones(struct mazo *miMazo, int *cartasjugadas);
void imprimeresultado(struct mazo *miMazo ,int *cartasjugadas);
int verificoconfiguraciones (int aparicionesuser[valores+1],int aparicionescompu[valores+1]);
int cualgano(int caso, int configuracionComputadora, int valor, int valorcompu);

int
main(void) {
    int puntoscompu = 0 , puntosjugador = 0 ;
    char *palos[]={"Corazon","trebol","Diamante","espadas"};
    struct mazo miMazo;
    int j=0,caso=0;
    int cartasjugadas = 0;
    for(int i=0; i<cartas; i++) {
        miMazo.mazo[i].numero = (i % valores) + 1;
        miMazo.mazo[i].palo = palos[j];
        if ((i + 1) % valores == 0) {
            j++;
        }
    }
    randomize();
    mezclarmazo(&miMazo);
    int i=0;
    char jugar;
    printf("¿Deseas jugar? (s/n): ");
    scanf(" %c", &jugar);
    while (i < cartas/10 && (jugar == 's' || jugar == 'S')) {
        imprimeresultado(&miMazo, &cartasjugadas);
        caso = configuraciones(&miMazo, &cartasjugadas);
        if(caso == 1) {
            puntosjugador++;
            printf("Esta ronda gana el usuario\n");
        }
        else if (caso == 2) {
            puntoscompu++;
            printf("Esta ronda gana la compu\n");
        }
        else {
            puntosjugador++;
            puntoscompu++;
            printf("Empate\n");
        }
        i++;
        printf("¿Deseas seguir jugando? (s/n): ");
        scanf(" %c", &jugar);
    }
    puntosjugador > puntoscompu ? printf("El usuario es el ganador con %d puntos",puntosjugador) : puntosjugador < puntoscompu ? printf("La compu es ganador con %d puntos",puntoscompu) : printf("Hubo empate");
    return 0;

}
void mezclarmazo(struct mazo *miMazo) {
    int lugar;
    struct carta cartaaux;
    for(int i = 0; i < cartas; i++) {
        cartaaux = miMazo->mazo[i];
        lugar = randInt(0,cartas-1);
        miMazo->mazo[i] = miMazo->mazo[lugar];
        miMazo->mazo[lugar] = cartaaux;
    }
}
int configuraciones(struct mazo *miMazo, int *cartasjugadas) {
    int i;
    int aparicionesuser[valores+1] = {0};
    int aparicionescompu[valores+1] = {0};
    for (i = 0; i < cartasextraidas; i++) {
        aparicionesuser[miMazo->mazo[i+*cartasjugadas].numero]++;
    }
    for(; i < (cartasextraidas*2); i++) {
        aparicionescompu[miMazo->mazo[i+*cartasjugadas].numero]++;
    }
    *cartasjugadas+=cartasextraidas*2;
    return verificoconfiguraciones(aparicionesuser,aparicionescompu);
}
void imprimeresultado(struct mazo *miMazo, int *cartasjugadas) {
    printf("Las cartas que le salieron al usuario son:\n");
    for (int i = 0; i < cartasextraidas; i++) {
        printf("%d de %s\n", miMazo->mazo[i + *cartasjugadas].numero, miMazo->mazo[i + *cartasjugadas].palo);
    }

    printf("Las cartas que le salieron a la compu son:\n");
    for (int i = cartasextraidas; i < cartasextraidas*2; i++) {
        printf("%d de %s\n", miMazo->mazo[i + *cartasjugadas].numero, miMazo->mazo[i + *cartasjugadas].palo);
    }
}
int verificoconfiguraciones(int *aparicionesuser, int *aparicionescompu) {
    struct Jugador jugador1 = {0, 0};
    struct Jugador jugador2 = {0, 0};

    for (int i = 1; i <= valores; i++) {
        // Evaluar jugador 1 (usuario)
        if (aparicionesuser[i] >= 2) {
            if (aparicionesuser[i] > jugador1.caso) {
                jugador1.caso = aparicionesuser[i];
                jugador1.valor = i;
            } else if (aparicionesuser[i] == jugador1.caso && i > jugador1.valor) {
                jugador1.valor = i;  // Actualizar el valor si el caso es igual y el número es mayor
            }
        }

        // Evaluar jugador 2 (computadora)
        if (aparicionescompu[i] >= 2) {
            if (aparicionescompu[i] > jugador2.caso) {
                jugador2.caso = aparicionescompu[i];
                jugador2.valor = i;
            } else if (aparicionescompu[i] == jugador2.caso && i > jugador2.valor) {
                jugador2.valor = i;  // Actualizar el valor si el caso es igual y el número es mayor
            }
        }
    }
    return cualgano(jugador1.caso, jugador2.caso, jugador1.valor, jugador2.valor);
}
int cualgano(int configuracionUsuario, int configuracionComputadora, int valor, int valorcompu) {
    if (configuracionUsuario > configuracionComputadora) {
        return 1; // Ganó el usuario
    }
    if (configuracionUsuario < configuracionComputadora) {
        return 2; // Ganó la computadora
    }
    return (valor > valorcompu) ? 1 : (valor < valorcompu) ? 2 : 0; // Empate
}