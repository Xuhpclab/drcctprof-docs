#include <stdio.h>
static int exe_num = 0;
void moo() {
    for(int i = 0; i < 100; i++){
        exe_num ++;
    }
    return;     
}
void foo() {
    for(int i = 0; i < 10000; i++){
        moo();
    }
}
int main(){
    foo();
    for(int i = 0; i < 20000; i++){
        moo();
    }
    return 0;  
}