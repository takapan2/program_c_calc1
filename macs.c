#include<stdio.h>
#include<math.h>

int main(void){
    int n,nmax=5000;
    int nt,ntmax=400;
    int nx,nxmax=20;
    int ny,nymax=20;

    double tmax=0.50;
    double xmax=1.0;
    double ymax=1.0;

    double t,dt=tmax/ntmax;
    double x,dx=xmax/nxmax;
    double y,dy=ymax/nymax;

    double e=0.000010;
    double Re=40;

    double p[nxmax][nymax],P[nxmax][nymax];
    double u[nxmax+1][nymax],U[nxmax+1][nymax];
    double v[nxmax][nymax+1],V[nxmax][nymax+1];

    double psai[nxmax][nymax];

    //u,vの初期条件を与えていく
    for(nx=0;nx<nxmax+1;nx++){
        for(ny=0;ny<nymax+1;ny++){
            if(ny==nymax){
                v[nx][ny]=0.0;
                V[nx][ny]=0.0;
            }else if(nx==nxmax){
                u[nx][ny]=0.0;
                U[nx][ny]=0.0;
            }else if(ny==nymax-1){
                u[nx][ny]=1.0;
                U[nx][ny]=1.0;
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

    for(nt=1;nt<ntmax;nt++){
        //Uを求めていく
        for(ny=1;ny<nymax-1;ny++){
            for(nx=1;nx<nxmax;nx++){
                double U1=u[nx][ny]*(u[nx+1][ny]-u[nx-1][ny])/(2.0*dx)+(v[nx][ny]+v[nx][ny+1]+v[nx-1][ny]+v[nx-1][ny+1])*(u[nx][ny+1]-u[nx][ny-1])/(8.0*dy);
                double U2=-(p[nx][ny]-p[nx-1][ny])/dx+((u[nx+1][ny]-2.0*u[nx][ny]+u[nx-1][ny])/dx/dx+(u[nx][ny+1]-2.0*u[nx][ny]+u[nx][ny-1])/dy/dy)/Re;
                U[nx][ny]=u[nx][ny]+dt*(-U1+U2);
            }
        }
        //Vを求めていく
        for(ny=1;ny<nymax;ny++){
            for(nx=1;nx<nxmax-1;nx++){
                double V1=(u[nx][ny-1]+u[nx+1][ny-1]+u[nx][ny]+u[nx+1][ny])*(v[nx+1][ny]-v[nx-1][ny])/(8.0*dx)+v[nx][ny]*(v[nx][ny+1]-v[nx][ny-1])/(2.0*dy);
                double V2=-(p[nx][ny]-p[nx][ny-1])/dy+((v[nx+1][ny]-2.0*v[nx][ny]+v[nx-1][ny])/dx/dx+(v[nx][ny+1]-2.0*v[nx][ny]+v[nx][ny-1])/dy/dy)/Re;
                V[nx][ny]=v[nx][ny]+dt*(-V1+V2);
            }
        }
        //U,Vを求めた。
        for(n=0;n<nmax;n++){
            for(n=1;n<nmax-1;n++){
                for(ny=1;ny<nymax-1;ny++){
                    for(nx=0;nx<nxmax;nx++){
                        double psai1=(psai[nx+1][ny]+psai[nx-1][ny])/dx/dx+(psai[nx][ny+1]+psai[nx][ny-1])/dy/dy;
                        double psai2=(u[nx+1][ny]-u[nx][ny])/dx+(v[nx][ny+1]-v[nx][ny])/dy;
                        psai[nx][ny]=(-psai1+psai2)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }
                }
            }
        }

        for(ny=0;ny<nymax;ny++){
            for(nx=0;nx<nxmax;nx++){
                u[nx][ny]=U[nx][ny]+(U[nx+1][ny]-U[nx][ny])/dx;
                v[nx][ny]=V[nx][ny]+(V[nx][ny+1]-V[nx][ny])/dy;
                p[nx][ny]=p[nx][ny]-psai[nx][ny]/dt;
            }
        }
    }
    double fai=0.0;
    int i;
    for(ny=0;ny<nymax;ny++){
        for(nx=0;nx<nxmax+1;nx++){
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