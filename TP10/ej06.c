#include <stdio.h>
#include <assert.h>
#include "../Biblioteca/list.h"

/**
** En esta versiรณn dejamos el primer elemento de una secuencia de repetidos
** Puede ser void porque el head de la lista no cambia
*/
void deleteDupl (tList list);


int main(void) {

    // Secuencias sin repetir, cantidad par e impar de repetidos
    // Probar repetidos en el medio, al principio y al final
    // En realidad no hace falta que esten ordenados, deberia funcionar igual
    int v[] = {1, 2, 3, 3, 4, 4, 4, 5, 6, 6, 7, 7, 7, 7, 7, 8};
    int w[] = {1, 2, 3, 4, 5, 6,  7, 8};

    tList l1 = fromArray(v, 16);
    deleteDupl(l1);
    assert(checkElems(l1, w, 8));
    freeList(l1);

    l1 = fromArray(v, 1);
    deleteDupl(l1);
    assert(checkElems(l1, w, 1));
    freeList(l1);

    l1 = fromArray(v, 2);
    deleteDupl(l1);
    assert(checkElems(l1, w, 2));
    freeList(l1);

    l1 = fromArray(v, 4);
    deleteDupl(l1);
    assert(checkElems(l1, w, 3));
    freeList(l1);


    l1 = fromArray(v+2, 5);
    deleteDupl(l1);
    assert(checkElems(l1, w+2, 2));
    freeList(l1);


    printf ("OK!\n");
    return 0;
}

void deleteDupl (tList list){
    if(list->tail == NULL) {
        return;
    }
    tList aux=list->tail;
    if(list->head == aux->head) {
        list->tail = aux->tail;
        deleteDupl(list);
    }
    else
        deleteDupl(list->tail);
}
