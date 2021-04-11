#include <stdio.h>
static int exe_num = 0;
void sub_fun() {
    for(int i = 0; i < 100; i++){
        exe_num ++;
    }
    return;     
}
void fun() {
    for(int i = 0; i < 10000; i++){
        sub_fun();
    }
}
int main(){
    fun();
    for(int i = 0; i < 20000; i++){
        sub_fun();
    }
    return 0;  
}