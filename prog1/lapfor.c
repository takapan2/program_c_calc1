#include<stdio.h>
#include<math.h>


int main(void){
    int N=100, M=N, n, nmax=5000, j, k;
    double e=0.00001, E;
    double u,U[M+1][N+1],xmin=0.0,ymin=0.0,xmax=1.0,ymax=1.0,x,y;
    double dx=(xmax-xmin)/(M),dy=(ymax-ymin)/(N),r=dy/dx;

    //初期条件//
    for(j=1;j<=M;j++){
        for(k=1;k<=N;k++){
            if(k==1){
                U[j][k]=1.0;
            }else if(j==1){
                U[j][k]=0.5;
            }else{
                U[j][k]=0.0;
            }
        }
    }

    for(n=1;n<=nmax && E<=e;n++){
        for(j=2;j<=M-1;j++){
            for(k=2;k<=N-1;k++){
                u=1/(2*(r*r+1))*(r*r*(U[j-1][k]+U[j+1][k])+U[j][k-1]+U[j][k+1]);
                E=fabs(U[j][k]-u);
                U[j][k]=u;
            }
        }
    }

    // for(k=1;k<=N;k++){
    //     for(j=1;j<=M;j++){
    //         x=xmin+j*dx;
    //         y=ymin+k*dy;
    //         printf("%lf     %lf     %lf\n",x,y,U[j][k]);
    //     }
    //     printf("\n");
    // }

    return 0;

}