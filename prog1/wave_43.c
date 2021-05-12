#include<stdio.h>
#include<math.h>

double f(double x){
    double ans;
    if(x<=0.5){
        ans=x;
    }else{
        ans=1.0-x;
    }
    return ans;
}

int main(void){
    int tnmax=200,xnmax=20;
    double tmax=10.0,xmax=1.0;
    double dt=tmax/(double)tnmax;
    double dx=xmax/(double)xnmax;
    double c=1.0;

    double r=c*dt/dx;
    double U[tnmax+1][xnmax+1];
    double UU[tnmax+1][xnmax+1];

    int tn,xn;
    
    double x,t;

    // printf("%lf",c*dt/dx);//値のチェック

    //初期条件の代入
    for(xn=0;xn<=xnmax;xn++){
        x=xn*dx;
        t=tn*dt;
        U[0][xn]=0.0;
        UU[0][xn]=f(dx);
    }

    for(tn=1;tn<=tnmax;tn++){
        x=xn*dx;
        t=tn*dt;
        
    }

}