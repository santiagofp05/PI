#include "ej11ADT.h"

#include <stdlib.h>

struct elems {
    elemType num;
    char estaOcupado;
};

typedef struct elems tElems;

struct vectorCDT {
    tElems *nums;
    int dim;
    int elemOcupados;
    int (*cmp)(elemType, elemType);
};

vectorADT newVector(cmp fun) {
    vectorADT vec = malloc(sizeof(struct vectorCDT));
    vec->dim = 0;
    vec->cmp = fun;
    vec->nums = NULL;
    vec->elemOcupados = 0;
    return vec;
}
void freeVector(vectorADT vec) {
    if(vec != NULL) {
        free(vec->nums);
        free(vec);
    }
}

static int getIdxRec(struct elems *nums, elemType num, size_t dim, cmp fun) {
    for (int i = 0; i < dim; i++) {
        if(nums[i].estaOcupado == 1) {
            if(fun(nums[i].num,num) == 0) {
                return i;
            }
        }
    }
    return -1;
}

int getIdx(vectorADT vec,elemType num) {
    return getIdxRec(vec->nums,num,vec->dim, vec->cmp);
}

int elementCount(vectorADT vec) {
    return vec->elemOcupados;
}

void deleteElement(vectorADT vec, size_t idx) {
    if(idx >= vec->dim) {
        return;
    }
    if(vec->nums[idx].estaOcupado == 1) {
        vec->nums[idx].estaOcupado = 0;
        vec->elemOcupados--;
    }
}

int putRec(struct elems *nums, elemType * inservec, size_t inicio, size_t dimvec, cmp fun) {
    int contador = 0;
    for(int i = inicio , j = 0; j < dimvec; i++, j++) {
        if(nums[i].estaOcupado == 0) {
            nums[i].num = inservec[j];
            nums[i].estaOcupado = 1;
            contador++;
        }
    }
    return contador;
}

int put(vectorADT vec, elemType * insertvec, size_t dimvec, size_t inicio) {
    if(dimvec >= vec->dim || inicio >= vec->dim) {
        vec->nums = realloc(vec->nums,sizeof(tElems) * (dimvec + inicio));
        for(int i = vec->dim ; i < dimvec + inicio; i++) {
            vec->nums[i].estaOcupado = 0;
        }
    }
    int c = putRec(vec->nums,insertvec, inicio, dimvec,vec->cmp);
    vec->elemOcupados += c;
    vec->dim = dimvec + inicio;
    return c;
}
