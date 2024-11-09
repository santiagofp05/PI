#include "museumADT.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANT_DIAS 366
#define invalidDayOfYear(x) ((x) == 0 || (x) > 366)

typedef struct person {
    char * nombre;
    struct person * nextperson;
} tPerson;


typedef struct dia {
    tPerson * first;
    int cantpersons;
    tPerson * actualperson;
}tDia;

struct museumTicketCDT {
    tDia dias[CANT_DIAS];
    int ticketsyear;
};


museumTicketADT newMuseumTicket(void) {
    return calloc(1,sizeof(struct museumTicketCDT));
}

static tPerson * addTicketRec(tPerson * l,const char *visitor, char *yavisito) {
    int cmp;

    if(l == NULL || (cmp = strcmp(l->nombre,visitor)) > 0) {
        tPerson *newPerson = malloc(sizeof(tPerson));
        newPerson->nombre = visitor;
        newPerson->nextperson = l;
        return newPerson;
    }
    if(cmp == 0) {
        *yavisito = 1;
        return l;
    }
    l->nextperson = addTicketRec(l->nextperson,visitor,yavisito);
    return l;
}

int addTicket(museumTicketADT museumTicketADT, size_t dayOfYear, const char *visitor) {
    char yavisito = 0;
    if(invalidDayOfYear(dayOfYear)) {
        return 0;
    }
    museumTicketADT->dias[dayOfYear-1].first = addTicketRec(museumTicketADT->dias[dayOfYear-1].first,visitor,&yavisito);
    if(yavisito == 1) {
        return 0;
    }
    museumTicketADT->ticketsyear++;
    return museumTicketADT->dias[dayOfYear-1].cantpersons+=1;
}

int dayTickets(const museumTicketADT museumTicketADT, size_t dayOfYear) {
    if(invalidDayOfYear(dayOfYear)) {
        return 0;
    }
    return museumTicketADT->dias[dayOfYear-1].cantpersons;
}

int yearTickets(const museumTicketADT museumTicketADT) {
    return museumTicketADT->ticketsyear;
}

void toBeginByDay(museumTicketADT museumTicketADT, size_t dayOfYear) {
    assert(invalidDayOfYear(dayOfYear)==0);
    museumTicketADT->dias[dayOfYear-1].actualperson = museumTicketADT->dias[dayOfYear-1].first;
}

size_t hasNextByDay(museumTicketADT museumTicketADT, size_t dayOfYear) {
    return (museumTicketADT->dias[dayOfYear-1].actualperson != NULL);
}

char * nextByDayRec(tDia l) {
    char * nombre = l.actualperson->nombre;
    return nombre;
}

char * nextByDay(museumTicketADT museumTicketADT, size_t dayOfYear) {
    char *nombre = nextByDayRec(museumTicketADT->dias[dayOfYear-1]);
    museumTicketADT->dias[dayOfYear-1].actualperson = museumTicketADT->dias[dayOfYear-1].actualperson->nextperson;
    return nombre;
}

void freePersonPerDay(tPerson *persona) {
    if(persona == NULL) {
        return;
    }
    freePersonPerDay(persona->nextperson);
    free(persona);
}


void freeMuseumTicket(museumTicketADT museumTicketADT) {
    for(int i=0; i < 366; i++) {
        freePersonPerDay(museumTicketADT->dias[i].first);
    }
    free(museumTicketADT);
}
