// #include<stdio.h>
// #include<math.h>

// int main(void){
//     int n,nmax=5000;
//     int nt,ntmax=10;
//     int nx,nxmax=100;
//     int ny,nymax=100;

//     int k=0;// kはスイッチ

//     double tmax=10.0;
//     double xmax=1.0;
//     double ymax=1.0;

//     double x,dx=xmax/nxmax;
//     double y,dy=ymax/nymax;
//     double t,dt=tmax/ntmax;

//     double e1=0.000010,e2=0.000010;

//     double w[ntmax+1][nxmax+1][nymax+1],W[ntmax+1][nxmax+1][nymax+1];
//     double f[ntmax+1][nxmax+1][nymax+1],F[ntmax+1][nxmax+1][nymax+1];

//     double u=1.0;
//     double Re=5.0;

//     for(nt=0;nt<ntmax+1;nt++){
//         for(nx=0;nx<nxmax+1;nx++){
//             for(ny=0;ny<nymax+1;ny++){
//                 w[nt][nx][ny]=0.0;
//                 f[nt][nx][ny]=0.0;
//             }
//         }
//     }


//     for(nt=0;nt<ntmax+1;nt++){
//         int k1=0,k2=0;
//         // ωの初期条件代入
//         for(nx=0;nx<nxmax+1;nx++){
//             for(ny=0;ny<nymax+1;ny++){
//                 if(nx==0){
//                     w[nt][nx][ny]=-2.0*f[nt][nx+1][ny]/dx/dx;
//                 }else if(nx==nxmax){
//                     w[nt][nx][ny]=-2.0*f[nt][nx-1][ny]/dx/dx;
//                 }else if(ny==0){
//                     w[nt][nx][ny]=-2.0*f[nt][nx][ny+1]/dy/dy;
//                 }else if(ny==nymax){
//                     w[nt][nx][ny]=-2.0*(f[nt][nx][ny-1]+dy)/dy/dy;
//                 }
//             }
//         }

//         for(n=0;n<nmax;n++){
//             for(nx=0;nx<nxmax+1;nx++){
//                 for(ny=0;ny<nymax+1;ny++){
//                     F[nt][nx][ny]=f[nt][nx][ny];
//                     if(nx==0||nx==nxmax||ny==0){
//                         f[nt][nx][ny]=0.0;
//                     }else if(ny==nymax){
//                         f[nt][nx][ny]=0.0;
//                     }else{
//                         f[nt][nx][ny]=(f[nt][nx+1][ny]+f[nt][nx][ny+1]+f[nt][nx-1][ny]+f[nt][nx][ny-1])/4.0+dx*dx*w[nt][nx][ny]/4.0;
//                         if(fabs(F[nt][nx][ny]-f[nt][nx][ny])<e2){
//                             k2=1;
//                         }
//                     }
//                 }
//             }
//         }

//         for(nx=1;nx<nxmax;nx++){
//             for(ny=1;ny<nymax;ny++){
//                 double w1,w2,w3;
//                 w1=(f[nt][nx][ny+1]-f[nt][nx][ny-1])*(w[nt][nx+1][ny]-w[nt][nx-1][ny])/4.0;
//                 w2=(f[nt][nx+1][ny]-f[nt][nx-1][ny])*(w[nt][nx][ny+1]-w[nt][nx][ny-1])/4.0;
//                 w3=(w[nt][nx+1][ny]+w[nt][nx-1][ny]+w[nt][nx][ny+1]+w[nt][nx][ny-1]-4.0*w[nt][nx][ny])/Re;
//                 w[nt+1][nx][ny]=w[nt][nx][ny]+dt*(w2-w1+w3)/dx/dx;
//             }
//         }
//     }

//     for(nt=0;nt<ntmax+1;nt++){
//         for(ny=0;ny<nxmax+1;ny++){
//             for(nx=0;nx<nymax+1;nx++){
//                 x=nx*dx;
//                 y=ny*dy;
//                 t=nt*dt;
//                 printf("%lf   %lf   %lf   %lf\n",t,x,y,f[nt][nx][ny]);
//             }
//             printf("\n");
//         }
//         printf("\n");
//     }

//     return 0;
// }

#include<stdio.h>
#include<math.h>

int main(void){
    int n,nmax=5000;
    int nt,ntmax=20;
    int nx,nxmax=100;
    int ny,nymax=100;

    int k=0;// kはスイッチ

    double tmax=1.0;
    double xmax=1.0;
    double ymax=1.0;

    double x,dx=xmax/nxmax;
    double y,dy=ymax/nymax;
    double t,dt=tmax/ntmax;

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


    for(nt=0;nt<ntmax+1;nt++){
        int k1=0,k2=0;
        // ωの初期条件代入
        // for(nx=0;nx<nxmax+1;nx++){
        //     for(ny=0;ny<nymax+1;ny++){
        //         if(nx==0){
        //             w[nx][ny]=-2.0*f[nx+1][ny]/dx/dx;
        //         }else if(nx==nxmax){
        //             w[nx][ny]=-2.0*f[nx-1][ny]/dx/dx;
        //         }else if(ny==0){
        //             w[nx][ny]=-2.0*f[nx][ny+1]/dy/dy;
        //         }else if(ny==nymax){
        //             w[nx][ny]=-2.0*(f[nx][ny-1]+dy)/dy/dy;
        //         }
        //     }
        // }

        for(n=0;n<nmax;n++){
            for(nx=0;nx<nxmax+1;nx++){
                for(ny=0;ny<nymax+1;ny++){
                    F[nx][ny]=f[nx][ny];
                    // 追加した分
                    if(nx==0){
                        w[nx][ny]=-2.0*f[nx+1][ny]/dx/dx;
                    }else if(nx==nxmax){
                        w[nx][ny]=-2.0*f[nx-1][ny]/dx/dx;
                    }else if(ny==0){
                        w[nx][ny]=-2.0*f[nx][ny+1]/dy/dy;
                    }else if(ny==nymax){
                        w[nx][ny]=-2.0*(f[nx][ny-1]+dy)/dy/dy;
                    }
                    // 追加した分
                    if(nx==0||nx==nxmax||ny==0||ny==nymax){
                        f[nx][ny]=0.0;
                    }else{
                        f[nx][ny]=(f[nx+1][ny]+f[nx][ny+1]+f[nx-1][ny]+f[nx][ny-1])/4.0+dx*dx*w[nx][ny]/4.0;
                        if(fabs(F[nx][ny]-f[nx][ny])<e2){
                            k2=1;
                        }
                    }
                }
            }
        }

        for(nx=1;nx<nxmax;nx++){
            for(ny=1;ny<nymax;ny++){
                double w1,w2,w3;
                w1=(f[nx][ny+1]-f[nx][ny-1])*(w[nx+1][ny]-w[nx-1][ny])/4.0;
                w2=(f[nx+1][ny]-f[nx-1][ny])*(w[nx][ny+1]-w[nx][ny-1])/4.0;
                w3=(w[nx+1][ny]+w[nx-1][ny]+w[nx][ny+1]+w[nx][ny-1]-4.0*w[nx][ny])/Re;
                W[nx][ny]=w[nx][ny]+dt*(w2-w1+w3)/dx/dx;
            }
        }

        for(nx=1;nx<nxmax;nx++){
            for(ny=1;ny<nymax;ny++){
                w[nx][ny]=W[nx][ny];
            }
        }

        // if(nt==2){
        //     for(ny=0;ny<nxmax+1;ny++){
        //         for(nx=0;nx<nymax+1;nx++){
        //             x=nx*dx;
        //             y=ny*dy;
        //             t=nt*dt;
        //             printf("%lf   %lf   %lf\n",x,y,f[nx][ny]);
        //         }
        //     printf("\n");
        //     }
        // }

        // for(ny=0;ny<nxmax+1;ny++){
        //     for(nx=0;nx<nymax+1;nx++){
        //         x=nx*dx;
        //         y=ny*dy;
        //         t=nt*dt;
        //         printf("%lf   %lf   %lf   %lf\n",t,x,y,f[nx][ny]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }

    return 0;
}