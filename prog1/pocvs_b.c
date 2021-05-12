#include<stdio.h>
#include<math.h>

int main(void){
    int n,nmax=5000;
    int nx,nxmax=100;
    int ny,nymax=100;

    int k=0;// kはスイッチ

    double xmax=1.0;
    double ymax=1.0;
    double dammy=0.0;

    double x,dx=xmax/nxmax;
    double y,dy=ymax/nymax;

    double e1=0.000010,e2=0.000010;

    double w[nxmax+1][nymax+1],W[nxmax+1][nymax+1];
    double f[nxmax+1][nymax+1],F[nxmax+1][nymax+1];

    double u=1.0;
    double Re=500.0;

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
                }else if(nx==nxmax){
                    w[nx][ny]=-2.0*f[nx-1][ny]/dx/dx;
                }else if(ny==0){
                    w[nx][ny]=-2.0*f[nx][ny+1]/dy/dy;
                }else if(ny==nymax){
                    w[nx][ny]=-2.0*(f[nx][ny-1]+dy)/dy/dy;
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
                if(nx==0||nx==nxmax||ny==0){
                    f[nx][ny]=0.0;
                }else if(ny==nymax){
                    f[nx][ny]=0.0;
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

    double Bx[nxmax+1][nymax+1];
    double By[nxmax+1][nymax+1];

    for(ny=0;ny<nxmax+1;ny++){
        for(nx=0;nx<nymax+1;nx++){
            if(nx!=0&&ny!=0&&nx!=nxmax&&ny!=nymax){
                if(nx%5==0&&ny%5==0){
                    double ax,ay;

                    ax=(fabs(f[nx-1][ny]-f[nx][ny])+fabs(f[nx+1][ny]-f[nx][ny]))/2.0;
                    ay=(fabs(f[nx][ny-1]-f[nx][ny])+fabs(f[nx][ny+1]-f[nx][ny]))/2.0;

                    By[nx][ny]=ax*pow((ax*ax+ay*ay),-0.50)/50.0;
                    Bx[nx][ny]=ay*pow((ax*ax+ay*ay),-0.50)/50.0;

                    // By[nx][ny]=ax*10;
                    // Bx[nx][ny]=ay*10;

                    if(f[nx][ny+1]-f[nx][ny]<0){
                        Bx[nx][ny]=-Bx[nx][ny];
                    }
                    if(f[nx-1][ny]-f[nx][ny]<0){
                        By[nx][ny]=-By[nx][ny];
                    }
                }
            }
        }
    }

    for(ny=0;ny<nxmax+1;ny++){
        for(nx=0;nx<nymax+1;nx++){
            if(nx!=0&&ny!=0){
                if(nx%5==0||ny%5==0){
                    x=nx*dx;
                    y=ny*dy;
                    printf("%lf   %lf   %lf   %lf   %lf   %lf\n",x,y,dammy,Bx[nx][ny],By[nx][ny],dammy);
                }
            }
        }
        if(nx!=0&&ny!=0){
            if(nx%5==0||ny%5==0){
                printf("\n");
            }
        }
    }


    return 0;
}