#include <stdio.h>
#include <assert.h>
#include "../Biblioteca/list.h"


tList listUnion  (const tList list1, const tList list2);


int main(void) {

    int v[] = {1, 4, 5, 6, 7, 8};
    int w[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int x[] = {2, 3, 9};

    tList l1 = fromArray(v, 6);
    tList l2 = fromArray(w, 9);
    tList l3 = listUnion(l1, l2);
    assert(checkElems(l3, w, 9));
    freeList(l3);

    l3 = listUnion(l2, l1);
    assert(checkElems(l3, w, 9));
    freeList(l3);

    l3 = listUnion(l2, l2);
    assert(checkElems(l3, w, 9));
    freeList(l3);

    l3 = listUnion(l2, NULL);
    assert(checkElems(l3, w, 9));
    freeList(l3);

    l3 = listUnion(NULL, l2);
    assert(checkElems(l3, w, 9));
    freeList(l3);
    freeList(l1);
    freeList(l2);
  
    l1 = fromArray(v, 6);
    l2 = fromArray(x, 3);
    l3 = listUnion(l1, l2);
    freeList(l1);
    freeList(l2);
    assert(checkElems(l3, w, 9));
    freeList(l3);


    printf ("OK!\n");
    return 0;
}

tList listUnion  (const tList list1, const tList list2) {
    if(list1 == NULL && list2 == NULL) {
        return NULL;
    }
    tList aux = malloc(sizeof(tNode));
    if(list2 == NULL) {
        aux->head = list1->head;
        aux->tail = listUnion(list1->tail,list2);
    }
    else if(list1 == NULL) {
        aux->head = list2->head;
        aux->tail = listUnion(list1,list2->tail);
    }
    else if(list1->head > list2->head) {
        aux->head = list2->head;
        aux->tail = listUnion(list1,list2->tail);
    }
    else if(list2->head > list1->head) {
        aux->head = list1->head;
        aux->tail = listUnion(list1->tail,list2);
    }
    else {
        aux->head = list2->head;
        aux->tail = listUnion(list1->tail,list2->tail);
    }
    return aux;
