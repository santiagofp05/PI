#include <stdio.h>
#include <assert.h>

#define MAX 10

void reemplazo(int matriz[][MAX], int dim, int fil, int col);
void cambio(int matriz[][MAX], int dim, int fil, int col,int * direccion);

int main(void) {

    int m[5][MAX] = { {1,0,1,0,1},
                      {0,1,1,1,1},
                      {1,0,0,1,0},
                      {1,1,1,0,1},
                      {0,0,0,0,0}};
    reemplazo(m, 5, 1, 2);
    int m2[5][MAX] = { {1,1,1,1,1},
                      {0,1,0,1,1},
                      {1,1,0,0,0},
                      {0,1,1,0,0},
                      {0,0,0,0,0}};
    for(int i=0; i < 5; i++)
        for(int j=0; j<5; j++)
            assert(m[i][j]==m2[i][j]);
    reemplazo(m, 5, 1, 2);
    reemplazo(m, 5, 1, 2);
    for(int i=0; i < 5; i++)
        for(int j=0; j<5; j++)
            assert(m[i][j]==m2[i][j]);

    printf ("OK!\n");
    return 0;
}

void reemplazo(int matriz[][MAX], int dim, int fil, int col) {
    matriz[fil][col] = (matriz[fil][col] == 0) ? 1 : 0;
    int direcciones[4][2] = {{1,1}, {-1,-1},{-1,1},{1,-1}};
    for(int i=0; i < 4 ; i++) {
        cambio(matriz,dim,fil+direcciones[i][0],col+direcciones[i][1],direcciones[i]);
    }
}
void cambio(int matriz[][MAX], int dim, int fil, int col,int direccion[2]) {
    if(fil < 0 || col < 0 || fil >= dim || col >= dim) {
        return;
    }
    matriz[fil][col] = (matriz[fil][col] == 0) ? 1 : 0;
    cambio(matriz,dim,fil+direccion[0],col+direccion[1],direccion);
}