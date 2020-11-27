#include<stdio.h>
#include<math.h>

void thomas(double a[],double b[], double c[], double d[], int j, int k){
    int i;
    double g[k+1],s[k+1];
    g[j]=b[j];
    s[j]=d[j];

    // printf("%lf     %lf\n",g[j],s[j]);
    for(i=j+1;i<=k;i++){
        g[i]=b[i]-a[i]*c[i-1]/g[i-1];
        s[i]=d[i]-a[i]*s[i-1]/g[i-1];
        // printf("%lf     %lf\n",g[i],s[i]);
    }
    d[k]=s[k]/g[k];
    for(i=k-1;i>=j+1;i--){
        d[i]=(s[i]-c[i]*d[i+1])/g[i];
    }
    return;
}


int main(void){
    int i,N=40;
    int j,M=40;

    double dx=0.025,x;
    double dt=0.00050,t;
    double k=1.0,r=k*dt/dx/dx;

    double U[N+1][M+1];
    double a[N+1],b[N+1],c[N+1],d[N+1];
    //初期条件を与える。

    for(j=0;j<=M;j++){
        for(i=0;i<=N;i++){
            x=i*dx;
            if(i==0 || i==N){
                U[i][j]=0.0;
            }else if(j==0){
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

    for(i=1;i<=N;i++){
        a[i]=-r;
        b[i]=1+2*r;
        c[i]=-r;
        d[i]=U[i][0];

    }

    for(j=1;j<=M;j++){
        thomas(a,b,c,d,0,N);
        for(i=1;i<=N-1;i++){
            U[i][j]=d[i];
        }
    }

    for(j=0;j<=M;j++){
        for(i=0;i<=N;i++){
            x=i*dx;
            t=j*dt;
            printf("%lf     %lf     %lf\n",x,t,U[i][j]);
        }
        printf("\n");
    }
    return 0;
}