#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

int suma(int numero);

int main(void) {

    assert(suma(0)==0);
    assert(suma(1)==1);
    assert(suma(12)==3);
    assert(suma(100000)==1);
    assert(suma(123456)==21);
    assert(suma(-123456)==21);
    assert(suma(999999)==54);

    puts("OK!");
    return 0;
}

int suma(int numero) {
    if (numero < 0) {
        numero = abs(numero);  // Convertir a positivo solo una vez
    }
    if(numero == 0) {
        return 0;
    }
    return suma(numero/10) + numero % 10;
}
