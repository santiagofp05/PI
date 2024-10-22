#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../Biblioteca/list.h"


typedef struct nodeBrief * tListBrief;
typedef struct nodeBrief {
    int elem;
    size_t count;
    struct nodeBrief * tail;
} tNodeBrief;
tListBrief comprimeList(const tList list);

// Auxiliar para que pase el test con sanitizer
void freeListBrief(tListBrief lb) {
    if ( lb == NULL)
        return;
    freeListBrief(lb->tail);
    free(lb);
}

int main(void) {

    int v[] = {1,1,2,3,3,3,3,3,10,100,100,998};
    tList list = fromArray(v, sizeof(v)/sizeof(v[0]));
    tListBrief bf = comprimeList(list);

    tListBrief aux = bf;
    assert(aux->elem ==1 && aux->count == 2);

    aux = aux->tail;
    assert(aux->elem ==2 && aux->count == 1);

    aux = aux->tail;
    assert(aux->elem ==3 && aux->count == 5);

    aux = aux->tail;
    assert(aux->elem ==10 && aux->count == 1);

    aux = aux->tail;
    assert(aux->elem ==100 && aux->count == 2);

    aux = aux->tail;
    assert(aux->elem ==998 && aux->count == 1);

    aux = aux->tail;
    assert(aux == NULL);

    freeList(list);
    freeListBrief(bf);
  
    printf ("OK!\n");
    return 0;
}

tListBrief comprimeList(const tList list) {
    if(list == NULL) {
        return NULL;
    }
    tListBrief toReturn = comprimeList(list->tail);
    if (toReturn == NULL || toReturn->elem != list->head) {
        tListBrief aux1 = malloc(sizeof(tNodeBrief));
        aux1->elem = list->head;
        aux1->count = 1;
        aux1->tail = toReturn;
        return aux1;
    }
        toReturn->count++;
        return toReturn;
}
