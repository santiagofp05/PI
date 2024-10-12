#include <stdio.h>
#include <string.h>
#include <assert.h>

char * strrchrRec(const char *s, char c);
char * ultvez(const char *s, char c, int longitud);

int
main(void) {
    const char * s = "vamos a buscar";

    for ( int i=0; s[i]; i++) {
        assert(strrchr(s, s[i]) == strrchrRec(s, s[i]));
    }

    assert(NULL == strrchrRec(s, 'x'));

    // También tiene que dar NULL para el valor 0
    assert(NULL == strrchrRec(s, '\0'));

    puts("OK!");
}
//char * strrchrRec(const char *s, char c){
//    int longitud = strlen(s);
//    return ultvez(s,c,longitud-1);
//}
// char * ultvez(const char *s, char c, int longitud) {
//     if(longitud < 0) {
//         return NULL;
//     }
//     if(s[longitud] == c) {
//         return (char *)(s+longitud);
//     }
//     if(s[longitud] != c) {
//         return ultvez(s,c,longitud-1);
//     }
// }
char * strrchrRec(const char *s, char c) {
    if (*s == '\0') {
        return NULL;  // Caso base: llegamos al final sin encontrar el carácter
    }
    // Llamada recursiva moviéndonos hacia el final de la cadena
    char *result = strrchrRec(s + 1, c);
    if (result != NULL) {
        return result;  // Si lo encontramos en una llamada recursiva posterior, retornamos ese resultado
    }
    // Verificamos el carácter actual
    if (*s == c) {
        return (char *) s;
    }
    return NULL;  // Si no lo encontramos, devolvemos NULL
}
