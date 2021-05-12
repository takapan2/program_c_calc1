#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int f(int x){
    if(x<=1){
        return 0;
    }else if(x%2==0){
        int y=x+1;
        return f(y)+x;
    }else{
        int y=x-3;
        return f(y)-x;
    }
}


int main(void){
    int a=f(10);
    printf("%d",a);
    return 0;
}