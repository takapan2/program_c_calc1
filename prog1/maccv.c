#include<stdio.h>
#include<math.h>

// void ansPrint(double U[],double V[],double u[],double v[],int ntmax,){
//     for()
// }

int main(void){
    int n,nmax=5000;
    int nt,ntmax=800;
    int nx,nxmax=30;
    int ny,nymax=30;

    double tmax=2.0;
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
            }else{
                u[nx][ny]=0.0;
                U[nx][ny]=0.0;
                v[nx][ny]=0.0;
                V[nx][ny]=0.0;
                p[nx][ny]=0.0;
                P[nx][ny]=0.0;
            }
        }
    }
    //初期条件与え終わり

    for(nt=1;nt<ntmax;nt++){
        //Pを求める。
        for(n=0;n<nmax;n++){
            for(ny=0;ny<nymax;ny++){
                for(nx=0;nx<nxmax;nx++){
                    if(ny==0&&nx==0){
                        // double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        // double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        // double p3=(p[nx+1][ny]+p[nx][ny]-(u[nx+2][ny]-2.0*u[nx+1][ny])/(Re*dx))/dx/dx+(p[nx][ny+1]+p[nx][ny]-(v[nx][ny+2]-2.0*u[nx][ny+1])/(Re*dx))/dy/dy;
                        // double p4=(u[nx][ny+1]+u[nx+1][ny+1]-u[nx][ny+1]-u[nx+1][ny+1])*(v[nx+1][ny]+v[nx+1][ny+1]+v[nx][ny]+v[nx][ny+1])/(2.0*dx*dy);
                        // p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }else if(ny==0&&nx==nxmax-1){
                        // double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        // double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        double p3=(p[nx][ny]+p[nx-1][ny]-(u[nx-2][ny]-2.0*u[nx-1][ny])/(Re*dx))/dx/dx+(p[nx][ny+1]+p[nx][ny]-(v[nx][ny+2]-2.0*u[nx][ny+1])/(Re*dx))/dy/dy;
                        // double p4=(u[nx][ny+1]+u[nx+1][ny+1]-u[nx][ny+1]-u[nx+1][ny+1])*(-v[nx][ny]-v[nx][ny+1]-v[nx-1][ny]-v[nx-1][ny+1])/(2.0*dx*dy);
                        // p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }else if(ny==nymax-1&&nx==0){
                        // double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        // double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        double p3=(p[nx+1][ny]+p[nx][ny]-(u[nx+2][ny]-2.0*u[nx+1][ny])/(Re*dx))/dx/dx+(p[nx][ny]+p[nx][ny-1]-(v[nx][ny-2]-2.0*u[nx][ny-1])/(Re*dx))/dy/dy;
                        // double p4=(u[nx][ny+1]+u[nx+1][ny-1]-u[nx][ny-1]-u[nx+1][ny-1])*(v[nx+1][ny]-v[nx+1][ny]+v[nx][ny]-v[nx][ny])/(2.0*dx*dy);
                        // p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }else if(ny==nymax-1&&nx==nxmax-1){
                        // double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        // double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        double p3=(p[nx][ny]+p[nx-1][ny]-(u[nx-2][ny]-2.0*u[nx-1][ny])/(Re*dx))/dx/dx+(p[nx][ny]+p[nx][ny-1]-(v[nx][ny-2]-2.0*u[nx][ny-1])/(Re*dx))/dy/dy;
                        // double p4=(u[nx][ny+1]+u[nx+1][ny-1]-u[nx][ny-1]-u[nx+1][ny-1])*(-v[nx][ny]+v[nx][ny]-v[nx-1][ny]+v[nx-1][ny])/(2.0*dx*dy);
                        // p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }else if(ny==0){
                        double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        double p3=(p[nx+1][ny]+p[nx-1][ny])/dx/dx+(p[nx][ny+1]+p[nx][ny]-(v[nx][ny+2]-2.0*u[nx][ny+1])/(Re*dx))/dy/dy;
                        double p4=(u[nx][ny+1]+u[nx+1][ny+1]-u[nx][ny+1]-u[nx+1][ny+1])*(v[nx+1][ny]+v[nx+1][ny+1]-v[nx-1][ny]-v[nx-1][ny+1])/(2.0*dx*dy);
                        p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }else if(ny==nymax-1){
                        double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        double p3=(p[nx+1][ny]+p[nx-1][ny])/dx/dx+(p[nx][ny]+p[nx][ny-1]-(v[nx][ny-2]-2.0*u[nx][ny-1])/(Re*dx))/dy/dy;
                        double p4=(u[nx][ny+1]+u[nx+1][ny-1]-u[nx][ny-1]-u[nx+1][ny-1])*(v[nx+1][ny]-v[nx+1][ny]-v[nx-1][ny]+v[nx-1][ny])/(2.0*dx*dy);
                        p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }else if(nx==0){
                        double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        double p3=(p[nx+1][ny]+p[nx][ny]-(u[nx+2][ny]-2.0*u[nx+1][ny])/(Re*dx))/dx/dx+(p[nx][ny+1]+p[nx][ny-1])/dy/dy;
                        double p4=(u[nx][ny+1]+u[nx+1][ny+1]-u[nx][ny-1]-u[nx+1][ny-1])*(v[nx+1][ny]+v[nx+1][ny+1]+v[nx][ny]+v[nx][ny+1])/(2.0*dx*dy);
                        p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }else if(nx==nxmax-1){
                        double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        double p3=(p[nx][ny]+p[nx-1][ny]-(u[nx-2][ny]-2.0*u[nx-1][ny])/(Re*dx))/dx/dx+(p[nx][ny+1]+p[nx][ny-1])/dy/dy;
                        double p4=(u[nx][ny+1]+u[nx+1][ny+1]-u[nx][ny-1]-u[nx+1][ny-1])*(-v[nx][ny]-v[nx][ny+1]-v[nx-1][ny]-v[nx-1][ny+1])/(2.0*dx*dy);
                        p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }else{
                        double p1=(u[nx+1][ny]-u[nx][ny])/dx;
                        double p2=(v[nx][ny+1]-v[nx][ny])/dy;
                        double p3=(p[nx+1][ny]+p[nx-1][ny])/dx/dx+(p[nx][ny+1]+p[nx][ny-1])/dy/dy;
                        double p4=(u[nx][ny+1]+u[nx+1][ny+1]-u[nx][ny-1]-u[nx+1][ny-1])*(v[nx+1][ny]+v[nx+1][ny+1]-v[nx-1][ny]-v[nx-1][ny+1])/(2.0*dx*dy);
                        p[nx][ny]=((p1+p2)/dt-p3+p1*p1+p2*p2+p4)/(-2.0*(1.0/dx/dx+1.0/dy/dy));
                    }
                }
            }
        }
        // for(ny=0;ny<nymax;ny++){
        //     for(nx=0;nx<nxmax;nx++){
        //         x=nx*dx;
        //         y=ny*dy;
        //         printf("%lf   %lf   %lf\n",x,y,p[nx][ny]);
        //     }
        // }
        //Pを求めて入力完了

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
        for(ny=0;ny<nymax;ny++){
            for(nx=0;nx<nxmax;nx++){
                u[nx][ny]=U[nx][ny];
                v[nx][ny]=V[nx][ny];
            }
        }

        // ansPrint(U,V,u,v);
        // for(ny=0;ny<nymax;ny++){
        //     for(nx=0;nx<nxmax;nx++){
        //         u[nx][ny]=U[nx][ny];
        //         v[nx][ny]=V[nx][ny];
        //         t=dt*nt;
        //         x=dx*nx;
        //         y=dy*ny;
        //         printf("%lf     %lf     %lf     %lf     %lf\n",t,x,y,U[nx][ny],V[nx][ny]);
        //     }
        // }

        // for(ny=0;ny<nymax;ny++){
        //     for(nx=0;nx<nxmax;nx++){
        //         u[nx][ny]=U[nx][ny];
        //         v[nx][ny]=V[nx][ny];
        //         t=dt*nt;
        //         x=dx*nx;
        //         y=dy*ny;
        //         double fai=0.0;
        //         int i;
        //         for(i=0;i<nx;i++){
        //             fai+=dy*(u[nx][i+1]+u[nx][i])/2.0;
        //         }
        //         printf("%lf     %lf     %lf\n",x,y,fai);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
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
}