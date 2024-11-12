#include "stdio.h"

typedef struct vectorCDT * vectorADT;
typedef int elemType;
typedef int (*cmp) (elemType, elemType);
/*Crea un nuevo vector dinámico de elementos genéricos
**Inicialmente el vector está vacío
**Cada elemento a insertar será det ipoelemType
*/
vectorADT newVector(cmp);


/*Libera todos los recursos reservados por el TAD*/
void freeVector(vectorADT);


/*Almacena los elementos de elems a partir de la posición index, donde elems es un vector de dim elementos.
**En caso de ser necesario agranda elvector.
**El resto de los elementos del vector no se modifican y permanecen en la misma posición.
**Si se recibe NULL o no se pudo insertar retorna cero.
**Si alguna posición está ocupada, la deja como estaba.
**Retorna cuántos elementos pudo almacenar.
**Ejemplo:
** Si v tieneo cupadas las posiciones 1, 3 y 6
** Se invoca con index = 2, dim = 5
** El vector actual quedará con los mismos elementos en las posiciones 1, 3 y 6
** Pero además v[2] = elems[0], v[4]  =elems[2] , v[5] = elems[3]
** y  lafunción retorna 3
*/
int put(vectorADT, elemType *, size_t , size_t);


/* Retorna el índice en el cual está insertado el elemento , o -1 si no lo encuentra*/
int getIdx(vectorADT,elemType);


/* Elimina el elemento en la posición index. Si index está fuera del vector no hace nada*/
void deleteElement(vectorADT , size_t);


/*Retorna cuántos elementos hay insertados en el vector*/
int elementCount(vectorADT);
