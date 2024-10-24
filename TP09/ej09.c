#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EPSILON 0.01

double raizNR(double valorAnterior, int iter, double x);

int main(void){

    assert(fabs(raizNR(4, 3, 8)-2.833) <= EPSILON);
    assert(raizNR(0, 0, 0) <= EPSILON);
    assert(raizNR(0, 0, 4) <= EPSILON);
    assert(fabs(raizNR(1.0, 10, 4.0) - 2.0) <= 0.0001); // Aproximación de √4
    assert(fabs(raizNR(2.0, 10, 9.0) - 3.0) <= 0.0001); // Aproximación de √9
    assert(fabs(raizNR(3.0, 10, 16.0) - 4.0) <= 0.0001); // Aproximación de √16
    assert(fabs(raizNR(4.0, 10, 25.0) - 5.0) <= 0.0001); // Aproximación de √25
    assert(fabs(raizNR(1.0, 10, 2.0) - 1.414213562) <= 0.0001); // Aproximación de √2
    assert(fabs(raizNR(3.0, 10, 10.0) - 3.162277660) <= 0.0001); // Aproximación de √10

    printf("OK!\n");
}

double raizNR(double valorAnterior, int iter, double x) {
    if( valorAnterior == 0) {
        return 0;
    }
    if (iter == 0) {
        return (valorAnterior+x/valorAnterior)/2;
    }
    return raizNR((valorAnterior+x/valorAnterior)/2, iter-1, x);
}
