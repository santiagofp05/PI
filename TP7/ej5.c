#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_ALUMNOS 40
#define MAX_LARGO 25
typedef char TAlumnos[MAX_ALUMNOS][MAX_LARGO];
typedef char TCurso[MAX_LARGO];

void
separaCursos( TAlumnos alumnos, TCurso cursos, TAlumnos cursoG, TAlumnos cursoH){
    int g=0,h=0;
    for (int i = 0;cursos[i]; i++){
        if (cursos[i]=='G'){
            strcpy(cursoG[g],alumnos[i]);
            g++;
        }
        else if (cursos[i]=='H'){
            strcpy(cursoH[h],alumnos[i]);
            h++;
        }
    }
    cursoG[g][0]=0;
    cursoH[h][0]=0;
}
int main(void) {
    TAlumnos alumnos={"Juan", "Pedro", "Martin", ""}, cursoG, cursoH;
    TCurso curso={'H', 'G', 'H', 0};
    separaCursos(alumnos, curso, cursoG, cursoH);
    assert(!strcmp(cursoG[0], alumnos[1]));
    assert(!strcmp(cursoH[0], alumnos[0]));
    assert(!strcmp(cursoH[1], alumnos[2]));
    assert(!strcmp(cursoG[1], alumnos[3]) && !strcmp(cursoH[2], alumnos[3]));   // Terminan con ""

    alumnos[0][0]=0;
    curso[0]=0;
    separaCursos(alumnos, curso, cursoG, cursoH);
    assert(!strcmp(cursoG[0], alumnos[0]) && !strcmp(cursoH[0], alumnos[0]));

    puts("OK!");
    return 0;
}
