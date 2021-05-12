#include<stdio.h>
#include<math.h>

int main(void){
    int n,nmax=5000;
    int nt,ntmax=200;
    int nx,nxmax=20;
    int ny,nymax=20;//格子数の設定

    double tmax=3.0;
    double xmax=1.0;
    double ymax=1.0;

    double t,dt=(double)tmax/((double)ntmax);
    double x,dx=(double)xmax/((double)nxmax);
    double y,dy=(double)ymax/((double)nymax);

    double e=0.000010;
    double Re=40;

    double DX=1.0/(1.0*nxmax);
    double DY=1.0/(1.0*nymax);

    double p[nxmax][nymax],P[nxmax][nymax];
    double u[nxmax+1][nymax],U[nxmax+1][nymax];
    double v[nxmax][nymax+1],V[nxmax][nymax+1];

    double psai[nxmax][nymax];

    double A1=0.50*DY*DY/(DX*DX+DY*DY);
    double A2=0.50*DX*DX/(DX*DX+DY*DY);
    double A3=0.50*DY*DY/(1.0+DY*DY/(DX*DX));

    // for(ny=0;ny<nymax+1;ny++){
    //     for(nx=0;nx<nxmax+1;nx++){
    //         u[nx][ny]=0.0;
    //         v[nx][ny]=0.0;
    //         p[nx][ny]=0.0;
    //         psai[nx][ny]=0.0;
    //     }
    // }

    for(nx=0;nx<nxmax+1;nx++){
        for(ny=0;ny<nymax+1;ny++){
            if(ny==nymax){
                v[nx][ny]=0.0;
                V[nx][ny]=0.0;
            }else if(nx==nxmax){
                u[nx][ny]=0.0;
                U[nx][ny]=0.0;
            }else if(ny==nymax-1){
                u[nx][ny]=0.0;
                U[nx][ny]=0.0;
                v[nx][ny]=0.0;
                V[nx][ny]=0.0;
                p[nx][ny]=0.0;
                P[nx][ny]=0.0;
                psai[nxmax][nymax]=0.0;
            }else{
                u[nx][ny]=0.0;
                U[nx][ny]=0.0;
                v[nx][ny]=0.0;
                V[nx][ny]=0.0;
                p[nx][ny]=0.0;
                P[nx][ny]=0.0;
                psai[nxmax][nymax]=0.0;
            }
        }
    }


    for(nt=0;nt<=ntmax+1;nt++){
        for(nx=0;nx<nxmax;nx++){
            u[nx][nymax-2]=1.0;
            v[nx][nymax-1]=v[nx][nymax-3];
            v[nx][nymax-2]=0.0;
            v[nx][0]=v[nx][2];
            v[nx][1]=0.0;
            u[nx][0]=-u[nx][1];
        }
        for(ny=0;ny<nymax;ny++){
            u[nxmax-1][ny]=u[nxmax-3][ny];
            u[nxmax-2][ny]=0.0;
            v[nxmax-2][ny]=-v[nxmax-3][ny];
            u[0][ny]=u[2][ny];
            u[1][ny]=0.0;
            v[0][ny]=-v[1][ny];
        }
        for(ny=1;ny<=nymax-2;ny++){
            for(nx=2;nx<=nxmax-3;nx++){
                double U1=u[nx][ny]*(u[nx+1][ny]-u[nx-1][ny])/(2.0*dx)+(v[nx][ny]+v[nx][ny+1]+v[nx-1][ny]+v[nx-1][ny+1])*(u[nx][ny+1]-u[nx][ny-1])/(8.0*dy);
                double U2=-(p[nx][ny]-p[nx-1][ny])/dx+((u[nx+1][ny]-2.0*u[nx][ny]+u[nx-1][ny])/dx/dx+(u[nx][ny+1]-2.0*u[nx][ny]+u[nx][ny-1])/dy/dy)/Re;
                U[nx][ny]=u[nx][ny]+dt*(-U1+U2);
            }
        }
        //Vを求めていく
        for(ny=2;ny<=nymax-3;ny++){
            for(nx=1;nx<=nxmax-2;nx++){
                double V1=(u[nx][ny-1]+u[nx+1][ny-1]+u[nx][ny]+u[nx+1][ny])*(v[nx+1][ny]-v[nx-1][ny])/(8.0*dx)+v[nx][ny]*(v[nx][ny+1]-v[nx][ny-1])/(2.0*dy);
                double V2=-(p[nx][ny]-p[nx][ny-1])/dy+((v[nx+1][ny]-2.0*v[nx][ny]+v[nx-1][ny])/dx/dx+(v[nx][ny+1]-2.0*v[nx][ny]+v[nx][ny-1])/dy/dy)/Re;
                V[nx][ny]=v[nx][ny]+dt*(-V1+V2);
                // printf("%d     %lf    %lf\n",nt,U[nx][ny],V[nx][ny]);
            }
        }
        for(n=0;n<nmax;n++){
            for(ny=0;ny<nymax;ny++){
                for(nx=0;nx<nxmax;nx++){
                    if(nx==0){
                        psai[nx][ny]=psai[nx+1][ny];
                    }else if(nx==nxmax-1){
                        psai[nx][ny]=psai[nx-1][ny];
                    }else if(ny==0){
                        psai[nx][ny]=psai[nx][ny+1];
                    }else if(ny==nymax-1){
                        psai[nx][ny]=psai[nx][ny-1];
                    }else{
                        double psai1=(psai[nx+1][ny]+psai[nx-1][ny])*A1+(psai[nx][ny+1]+psai[nx][ny-1])*A2;
                        double psai2=((U[nx+1][ny]-U[nx][ny])/dx+(V[nx][ny+1]-V[nx][ny])/dy)*A3;
                        psai[nx][ny]=psai1+psai2;
                    }
                    // if(n==nmax-1){
                    //     printf("%d          %lf\n",nt,psai[nx][ny]);
                    // }
                }
            }
        }
        for(ny=1;ny<=nymax-2;ny++){
            for(nx=2;nx<=nxmax-3;nx++){
                u[nx][ny]=U[nx][ny]+(psai[nx+1][ny]-psai[nx][ny])*0.50/dx;
                // p[nx][ny]=p[nx][ny]-psai[nx][ny]/dt;
                // printf("%d     %lf    %lf     %lf\n",nt,u[nx][ny],v[nx][ny],p[nx][ny]);
            }
        }
        for(ny=2;ny<=nymax-2;ny++){
            for(nx=1;nx<=nxmax-2;nx++){
                v[nx][ny]=V[nx][ny]+(psai[nx][ny+1]-psai[nx][ny])*0.50/dy;
                // p[nx][ny]=p[nx][ny]-psai[nx][ny]/dt;
                // printf("%d     %lf    %lf     %lf\n",nt,u[nx][ny],v[nx][ny],p[nx][ny]);
            }
        }
        for(ny=1;ny<=nymax-2;ny++){
            for(nx=1;nx<=nxmax-2;nx++){
                p[nx][ny]=p[nx][ny]-psai[nx][ny]/dt;
            }
        }
    }

    double fai=0.0;
    int i;
    for(ny=0;ny<nymax-2;ny++){
        for(nx=0;nx<nxmax-1;nx++){
            fai=0.0;
            t=dt*nt;
            x=dx*nx+dx/2.0;
            y=dy*ny+dy/2.0;
            for(i=0;i<ny-1;i++){
                fai+=dy*(u[nx][i+1]+u[nx][i])/2.0;
            }
            // printf("%lf     %lf     0.000000     %lf     %lf      0.000000\n",x,y,U[nx][ny],V[nx][ny]);
            printf("%lf     %lf     %lf\n",x,y,fai);
        }
    }

    return 0;
}