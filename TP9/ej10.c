#include <stdio.h>
#include <assert.h>
#include <iso646.h>
#include <string.h>

void invierte(char *origen, char * destino);

int main(void) {

    char s[20] = {0};

    invierte("1234567890", s);
    assert(strcmp(s, "0987654321")==0);

    memset(s, 0, 20);
    invierte("", s);
    assert(strcmp(s, "")==0);

    memset(s, 0, 20);
    invierte("a", s);
    assert(strcmp(s, "a")==0);

    memset(s, 0, 20);
    invierte("ab", s);
    assert(strcmp(s, "ba")==0);

    memset(s, 0, 20);
    invierte("abc", s);
    assert(strcmp(s, "cba")==0);

    printf ("OK!\n");
    return 0;
}

void invierte(char *origen, char * destino) {
    if(origen[0] == 0) {
        return;
    }
    destino[strlen(origen)-1] = origen[0];
    return invierte(origen+1, destino) ;
}