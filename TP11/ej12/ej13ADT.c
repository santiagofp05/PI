#include "ej13ADT.h"

//Me falta hacer una funcion para no repetir codigo

struct rankingCDT {
    compare fun;
    size_t cantElems;
    elemType *positions;
};

static void swapElems(elemType * elem1, elemType * elem2) {
    elemType aux = *elem1;
    *elem1 = *elem2;
    *elem2 = aux;
}

rankingADT newRanking(elemType elems[], size_t dim, compare cmp) {
    rankingADT newRanking = malloc(sizeof(struct rankingCDT));
    newRanking->fun = cmp;
    newRanking->cantElems = dim;
    if(dim != 0) {
        newRanking->positions = malloc(sizeof(elemType) * dim );
        for (int i = 0; i < dim; i++) {
            newRanking->positions[i] = elems[i];
        }
    }
    else
        newRanking->positions = NULL; //me habia olvidado de inicializarlo en NULL
    return newRanking;
}

void addRanking(rankingADT ranking, elemType elem) {
    for (int i = 0; i < ranking->cantElems; i++) {
        int c = ranking->fun(ranking->positions[i],elem);
        if(c == 0 && i == 0) {
            return; 
        }
        if(c == 0) {
            swapElems(&ranking->positions[i-1],&ranking->positions[i]);
            return;
        }
    }
    ranking->positions = realloc(ranking->positions,sizeof(elemType) * (ranking->cantElems + 1));
    ranking->cantElems++;
    ranking->positions[ranking->cantElems-1] = elem; //me habia olvidado de poner el -1 entonces accedia a zona de memoria invalida
}

size_t size(const rankingADT ranking) {
    return ranking->cantElems;
}

int getByRanking(rankingADT ranking, size_t n, elemType * elem) { //se me chispoteo a que posicion tenia que acceder
    if(n > ranking->cantElems || n < 1) { //me olvide de poner el caso que n < 1
        return 0;
    }
    *elem = ranking->positions[n-1];
    if(n != 1) { //me olvide de tener en cuenta el caso que n == 1
        swapElems(&ranking->positions[n-1],&ranking->positions[n-2]);
    }
    return 1;
}

elemType * getTopRanking(const rankingADT ranking, size_t * top) {
    if(ranking->cantElems == 0) {
        *top = 0;
        return NULL;
    }
    elemType * toReturn;
    if(*top >= ranking->cantElems) {
        toReturn = malloc(sizeof(elemType) * ranking->cantElems);
    }
    else
        toReturn = malloc(sizeof(elemType) * *top);
    int i;
    for (i = 0; i < ranking->cantElems && i < * top ; i++) {
        toReturn[i] = ranking->positions[i];
    }
    *top = i;
    return toReturn;
}
int contains(rankingADT ranking, elemType elem) {
    int c;
    for(int i=0; i < ranking->cantElems; i++) {
        c = ranking->fun(ranking->positions[i],elem);
        if(c == 0 && i!= 0) { //me habia faltado ver que pasa cuando i == 0
            swapElems(&ranking->positions[i],&ranking->positions[i-1]);
            return 1;
        }
        if(c == 0) { //le agregue esto
            return 1;
        }
    }
    return 0;
}

void downByRanking(rankingADT ranking, size_t n) {
    swapElems(&ranking->positions[n-1],&ranking->positions[n]);
}
void freeRanking(rankingADT ranking) { //aca tambien liberaba positions que esta mal
    free(ranking);
}
int position(const rankingADT ranking, elemType elem) {
    int c;
    for(int i=0; i < ranking->cantElems; i++) {
        c = ranking->fun(ranking->positions[i],elem);
        if(c == 0) {
            return i+1;;
        }
    }
    return 0;
}
