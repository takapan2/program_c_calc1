#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// #include "thomas.h"

void thomas(double a[],double b[], double c[], double d[], int j, int k){
    int i;
    double g[k+1],s[k+1];

    for(i=j+1;i<=k;i++){
        g[i]=b[i]-a[i]*c[i-1]/g[i-1];
        s[i]=d[i]-a[i]*s[i-1]/g[i-1];
    }
    d[k]=s[k]/g[k];
    for(i=k-1;i>=j+1;i--){
        d[i]=(s[i]-c[i]*d[i+1])/g[i];
        // printf("%lf\n",d[i]);
    }
    return;
}

int main(void){
    int N;
    int i;
    // printf("Type here N=");
    // scanf("%d",&N);

    N=1000;

    double a[N+1],b[N+1],c[N+1],d[N+1];
    double h=1.0/N;
    for(i=2;i<=N;i++){
        a[i]=1;
        b[i]=h*h-2;
        c[i]=1;
        d[i]=-i*h*h*h;
    }

    thomas(a,b,c,d,2,N);

    for(i=2;i<=N;i++){
        double u,x;
        x=i*h;
        u=sin(x)/sin(1.0)-x;
        printf("%lf     %lf     %lf\n",x,u,d[i]);
    }
    return 0;
}
