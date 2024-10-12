#include <stdio.h>
#include <assert.h>

int ackermann(int num1,int num2);

int main(void) {

    for(int i=0; i < 100; i++)
        assert(ackermann(0, i)==i+1);

    assert(ackermann(3,0)==5);
    assert(ackermann(3,2)==29);

    puts("Wait for it...");

    assert(ackermann(4,1)==65533);

    puts("Legendary!");
    return 0;
}

int ackermann(int num1,int num2) {
    if(num1 == 0) {
        return num2+1;
    }
    if(num2 == 0) {
        return ackermann(num1-1,1);
    }
    return ackermann(num1-1,ackermann(num1,num2-1));
}
