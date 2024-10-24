#include <stdio.h>
#include <assert.h>

int balance(const char *texto);


int main(void) {

    assert(balance("")==0);
    assert(balance("((()))")==0);
    assert(balance(")(")==0);
    assert(balance("()()")==0);
    assert(balance(")))(((")==0);
    assert(balance("))) ((( ))( ()() ()()(")==0);

    assert(balance(")")!=0);
    assert(balance("(")!=0);
    assert(balance(")()")!=0);
    assert(balance(" ) ")!=0);
    assert(balance("))))))))))))))))))))))))))))))))))))))))))))))))))))))")!=0);
    assert(balance("))))))))))))))))))))))))))))))))))))))))))))))))))))))((((((((((((")!=0);

    printf ("OK!\n");
    return 0;
}
int balance(const char *texto) {
    if(texto[0] == '(') {
        return balance(texto+1)+1;
    }
    if(texto[0] == ')') {
        return balance(texto+1)-1;
    }
    if(texto[0] == 0) {
        return 0;
    }
    return balance(texto+1);
}
