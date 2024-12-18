#include <stddef.h>
typedef struct museumTicketCDT * museumTicketADT;
/* Nota: Como no se indica el año para el que se lo utilizará se asume bisiesto
*/
museumTicketADT newMuseumTicket(void);
/* Retorna cantidad actual de tickets registrados para visitar el museo ese día
* Retorna 0 si dayOfYear es igual a 0 o mayor a 366
* Retorna 0 si ya se había registrado ticket para ese visitor y ese #dayOfYear
*/
int addTicket(museumTicketADT museumTicketADT, size_t dayOfYear, const char *visitor);
/* Retorna cantidad de tickets registrados para visitar el museo el día
* #dayOfYear del año
* Retorna -1 si #dayOfYear es igual a 0 o mayor a 366
*/
int dayTickets(const museumTicketADT museumTicketADT, size_t dayOfYear);
/* Retorna la cantidad total de tickets registrados para visitar el museo
*/
int yearTickets(const museumTicketADT museumTicketADT);
/*Funciones de iteración para poder consultar,
* para un día #dayOfYear del año, los nombres de los visitantes de los tickets registrados para visitar el museo ese día en orden alfabético por nombre de visitante.
* IMPORTANTE: Permitir utilizar estas funciones para distintos días del año
* EN SIMULTANEO (ver ejemplo en programa de prueba)
* Abortar si cualquiera de las funciones es invocada con #dayOfYear inválido
*/
void toBeginByDay(museumTicketADT museumTicketADT, size_t dayOfYear);

size_t hasNextByDay(museumTicketADT museumTicketADT, size_t dayOfYear);

char * nextByDay(museumTicketADT museumTicketADT, size_t dayOfYear);
/*Libera los recursos utilizados para administrar las ventas de tickets para
* visitar un museo en un año determinado
*/
void freeMuseumTicket(museumTicketADT museumTicketADT);
