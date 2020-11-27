#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double t,double u){
    return 1.0/2.0*(1.0+t)*u*u;
}

int main(void){
    int N=1000, i;
    double t=0.0,u=1.0,tmax=2.0;
    double h=(tmax-t)/N,U;

    for(i=0;i<N;i++){
        t=h*i;
        U=4/(4-2*t-t*t);
        printf("%lf     %lf     %lf\n",t,U,u);

        double s1,s2,s3,s4,s5;

        s1=f(t,u);
        s2=f(t+h/2.0,u+s1*h/2.0);
        s3=f(t+h/2.0,u+s2*h/2.0);
        s4=f(t+h,u+s3*h);
        s5=s1+2*s2+2*s3+s4;

        u=U+h*s5/6;
    }
    return 0;
}