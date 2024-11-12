#include "ej12ADT.h"


typedef struct relacion tRelacion;
typedef struct personas tPersona;


struct relacion{
    char *persona;
    tRelacion *nextRelacion;
};


struct persona {
    char *nombre;
    tRelacion relaciones;
    tPersona *nextPersona;
};

struct socialCDT {
    tPersona *personas;
};
