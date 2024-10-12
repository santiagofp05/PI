#include <stdio.h>
#include <assert.h>

double productoEsc(double vec1[], double vec2[], int dim);

int main(void) {

    double v1[] = {0.0, 1.0, 2.2, 3.5, 4.5};

    double v2[] = {0.0, -1.0, 5.0, -3.0, 3.0};

    double res[] = {0, -1.0, 10.0, -0.5, 13.0};

    assert(productoEsc(v1, v2, 0)==0.0);


    for(int i=0; i<5; i++)
        assert(productoEsc(v1, v2, i+1)==res[i]);


    printf ("OK!\n");
    return 0;
}
double productoEsc(double vec1[],double vec2[], int dim) {
    if (dim <= 0) {
        return 0;
    }
    return productoEsc(1+vec1,1+vec2,dim-1) + (vec1[0] * vec2[0]);
}