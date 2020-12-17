#include<stdio.h>
#include<math.h>

// void output(){
// }

int main(void){
    int i,xn=40;
    int j,tn=100;

    double xmax=1.0,tmax=0.050,x,t;

    double dx=xmax/xn,dt=tmax/tn,dr=(dt/(dx*dx)),k=1.0;

    double U[xn+2][tn+2];

    for(j=1;j<=tn+1;j++){
        for(i=1;i<=xn+1;i++){
            x=dx*(i-1);
            t=dt*(j-1);
            if(i==1 || i==xn+1){
                U[i][j]=0.0;
            }else if(j==1){
                if(x>=0 && x<=0.5){
                    U[i][j]=x;
                }else{
                    U[i][j]=1.0-x;
                }
            }else{
                U[i][j]=0.0;
            }
        }
    }

    for(j=2;j<=tn+1;j++){
        for(i=2;i<=xn;i++){
            U[i][j]=dr*U[i-1][j-1]+(1-2*dr)*U[i][j-1]+dr*U[i+1][j-1];
        }
    }

    for(j=1;j<=tn+1;j++){
        for(i=1;i<=xn+1;i++){
            x=dx*(i-1);
            t=dt*(j-1);
            printf("%lf     %lf     %lf\n",x,t,U[i][j]);
        }
        printf("\n");
    }
    return 0;

}