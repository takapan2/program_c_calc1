#include<stdio.h>
#include<math.h>

int main(void){
    int n,nmax=5000;
    int nx,nxmax=100;
    int ny,nymax=100;

    int k=0;// kはスイッチ

    double xmax=1.0;
    double ymax=1.0;

    double x,dx=xmax/nxmax;
    double y,dy=ymax/nymax;

    double e1=0.000010,e2=0.000010;

    double w[nxmax+1][nymax+1],W[nxmax+1][nymax+1];
    double f[nxmax+1][nymax+1],F[nxmax+1][nymax+1];

    double u=1.0;
    double Re=5.0;

    for(nx=0;nx<nxmax+1;nx++){
        for(ny=0;ny<nymax+1;ny++){
            w[nx][ny]=0.0;
            f[nx][ny]=0.0;
        }
    }

    for(n=0;n<nmax;n++){
        int k1=0,k2=0;
        // ωの初期条件代入
        for(nx=0;nx<nxmax+1;nx++){
            for(ny=0;ny<nymax+1;ny++){
                if(nx==0){
                    w[nx][ny]=-2.0*f[nx+1][ny]/dx/dx;
                }else if(nx==nxmax+1){
                    w[nx][ny]=-2.0*f[nx-1][ny]/dx/dx;
                }else if(ny==nymax+1){
                    w[nx][ny]=-2.0*f[nx][ny-1]/dy/dy;
                }else if(ny==0){
                    w[nx][ny]=-2.0*(f[nx][ny+1]-dy)/dy/dy;
                }
            }
        }

        for(nx=1;nx<nxmax;nx++){
            for(ny=1;ny<nymax;ny++){
                W[nx][ny]=w[nx][ny];
                w[nx][ny]=(w[nx+1][ny]+w[nx][ny+1]+w[nx-1][ny]+w[nx][ny-1])/4.0-Re*((f[nx][ny+1]-f[nx][ny-1])*(w[nx+1][ny]-w[nx-1][ny])-(f[nx+1][ny]-f[nx-1][ny])*(w[nx][ny+1]-w[nx][ny-1]))/16.0;
                if(fabs(W[nx][ny]-w[nx][ny])<e1){
                    k1=1;
                }
            }
        }

        for(nx=0;nx<nxmax+1;nx++){
            for(ny=0;ny<nymax+1;ny++){
                F[nx][ny]=f[nx][ny];
                if(nx==0||nx==nxmax+1||ny==0){
                    f[nx][ny]=0.0;
                }else if(ny==nymax+1){
                    f[nx][ny]=u;
                }else{
                    f[nx][ny]=(f[nx+1][ny]+f[nx][ny+1]+f[nx-1][ny]+f[nx][ny-1])/4.0+dx*dx*w[nx][ny]/4.0;
                    if(fabs(F[nx][ny]-f[nx][ny])<e2){
                        k2=1;
                    }
                }
            }
        }

        if(k1==1&&k2==1){
            k++;
        }
    }

    for(nx=0;nx<nxmax+1;nx++){
        for(ny=0;ny<nymax+1;ny++){
            x=nx*dx;
            y=ny*dy;
            printf("%lf   %lf   %lf\n",x,y,f[nx][ny]);
        }
        printf("\n");
    }

    return 0;
}