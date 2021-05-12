#include<stdio.h>
#include<math.h>

void sub(double a[]){
    int i;
    double u;
    for(i=0;i<=10;i++){
        u=sin(a[i]);
        printf("%lf¥n",u);
    }
}

int main(void){
    printf("テストだよ");
    int i;
    double age[10];
    for(i=0;i<=10;i++){
        age[i]=2.0*4.0*atan(1.0)/10.0;
        printf("%lf¥n",age[i]);
    }
    sub(age);
    return 0;
}

