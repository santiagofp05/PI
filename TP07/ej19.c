#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *
copiaPrefijo(const char * s, unsigned int n);


int main(void){

    char * corto = "Corto";
    char * largo = "La Constitucion de la Nacion Argentina, que rige actualmente a la RepÃƒÂºblica Argentina, fue aprobada por una asamblea constituyente integrada por representantes de trece provincias, hecha en la ciudad de Santa Fe en el anio 1853. Los diferentes textos de esta Constitucion han sido reformados varias veces, siendo la ultima llevada a cabo en 1994, y han sido dejados sin efecto o modificados por autoridades de facto en nueve oportunidades.El proposito de la Constitucion de 1853 fue poner fin al ciclo de las guerras civiles y sentar las bases de la Organizacion Nacional, objetivos que tardaron unas decadas mas en cumplirse. Antes de esta aprobacion hubo varios intentos (en 1819 y 1826) que fueron rechazados por diversos motivos.El texto constitucional consta de un preambulo y dos partes normativas: ";

    char * aux;
    aux = copiaPrefijo(largo, 0);
    assert(!strcmp("", aux));
    free(aux);

    aux = copiaPrefijo(corto, 120);
    assert(!strcmp("Corto", aux));
    free(aux);

    aux = copiaPrefijo(largo, 2);
    assert(!strcmp("La", aux));
    free(aux);

    aux = copiaPrefijo(corto, 0);
    assert(!strcmp("", aux));
    free(aux);

    puts("OK!");
    return 0;
}

char * copiaPrefijo(const char * s, unsigned int n) {
    char * aux;
    int longituds = strlen(s);
    if ( longituds < n) {
        aux = malloc((longituds+1)*sizeof(char));
        return strcpy(aux, s);
    }
    aux = malloc((n+1) * sizeof(char));
    int i;
    for(i = 0; i < n; i++) {
        aux[i] = s[i];
    }
    aux[i] = '\0';
    return aux;
}