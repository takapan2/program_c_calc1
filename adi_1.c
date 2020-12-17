#include<stdio.h>
#include<math.h>

void thomas(double a[],double b[], double c[], double d[], int Tj, int Tk){
    int i;
    double g[Tk+1],s[Tk+1];
    g[Tj]=b[Tj];
    s[Tj]=d[Tj];

    // printf("%lf     %lf\n",g[Tj],s[Tj]);
    for(i=Tj+1;i<=Tk;i++){
        g[i]=b[i]-a[i]*c[i-1]/g[i-1];
        s[i]=d[i]-a[i]*s[i-1]/g[i-1];
        // printf("%lf     %lf\n",g[i],s[i]);
    }
    d[Tk]=s[Tk]/g[Tk];
    for(i=Tk-1;i>=Tj+1;i--){
        d[i]=(s[i]-c[i]*d[i+1])/g[i];
    }
    return;
}

int main(void){
    int j,nx=20;
    int k,ny=20;
    int n,nt=200;

    double x,xmax=1.0,dx=xmax/nx;
    double y,ymax=1.0,dy=ymax/ny;
    double t,tmax=1000.0,dt=tmax/nt;

    double r1=dt/dx/dx,r2=dt/dy/dy;

    double U[nx+1][ny+1][nt+1];
    double UU[nx+1][ny+1][nt+1];

    // 初期条件の代入

    for(n=0;n<=nt;n++){
        for(k=0;k<=ny;k++){
            for(j=0;j<=nx;j++){
                x=j*dx;
                y=k*dy;
                t=n*dt;
                U[j][k][n]=0.0;
                UU[j][k][n]=0.0;
            }
        }
    }

    for(n=0;n<=nt;n++){
        for(k=0;k<=ny;k++){
            for(j=0;j<=nx;j++){
                x=j*dx;
                y=k*dy;
                t=n*dt;
                if(j==nx ||k==ny){
                    U[j][k][n]=0.0;
                    UU[j][k][n]=0.0;
                }else if(j==0){
                    U[j][k][n]=0.50;
                    UU[j][k][n]=0.50;
                }else if(k==0){
                    U[j][k][n]=1.0;
                    UU[j][k][n]=1.0;
                }
            }
        }

        // UUについて求めていく
        for(k=1;k<=ny-1;k++){
            double a[nx+1],b[nx+1],c[nx+1],d[nx+1];
            for(j=0;j<=nx;j++){
                a[j]=-1.0;
                b[j]=2.0*(1.0+1.0/r1);
                c[j]=-1.0;
                d[j]=r2/r1*U[j][k-1][n]+2.0*(1.0/dt-r2/r1)*U[j][k][n]+r2/r1*U[j][k+1][n];
                // printf("%lf     %lf     %lf      %lf\n",a[j],b[j],c[j],d[j]);
            }
            thomas(a,b,c,d,0,nx);
            for(j=1;j<=nx-1;j++){
                UU[j][k][n]=d[j];
                // printf("%lf\n",d[j]);
            }
        }
        // Uについて求めていく
        for(j=1;j<=nx-1;j++){
            double a[ny+1],b[ny+1],c[ny+1],d[ny+1];
            for(k=0;k<=ny;k++){
                a[j]=-1.0;
                b[j]=2.0*(1.0+1.0/r1);
                c[j]=-1.0;
                d[j]=r1/r2*UU[j-1][k][n]+2.0*(1.0/dt-r1/r2)*UU[j][k][n]+r1/r2*UU[j][k+1][n];
            }
            thomas(a,b,c,d,0,ny);
            for(k=1;k<=ny-1;k++){
                U[j][k][n+1]=d[k];
            }
        }

        if(n%25==0){
            for(j=0;j<=nx;j++){
                for(k=0;k<=ny;k++){
                    x=j*dx;
                    y=k*dy;
                    t=n*dt;
                    printf("%lf     %lf     %lf     %lf\n",t,x,y,U[j][k][n]);
                }
                printf("\n");
            }
            printf("\n\n");
        }
    }


    return 0;



}