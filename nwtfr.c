#include <stdio.h>
#include <math.h>

void avalp (double x, double y, double *px, double *py,
      int n, double u[], double v[]) {
    //inicialitzar variables necessaries
    int i;
    double znx,zny,zauxx,zauxy;

    znx=1;
    zny=0;

    //operar per aconseguir els valors per a px y py
    for(i=0;i<(n);i++){
        zauxx=znx;
        zauxy=zny;
        znx=(zauxx*(x-u[i]))-(zauxy*(y-v[i]));
        zny=((zauxy*(x-u[i])+zauxx*(y-v[i])));
    }

    //valors a px y py
    *px=znx;
    *py=zny;
}

void avaldp (double x, double y, double *dpx, double *dpy,
      int n, double u[], double v[]) {
    //declarar variables
    int i,j;
    double znx,zny,zndx,zndy,zauxx,zauxy;

    //assignar valor inicial a les variables
    zndx=0;zndy=0;

    //bucle gran pel sumatori de cada tros
    for(i=0;i<(n);i++) {
        znx=1;zny=0;
        //bucle interior per la derivació de cada tros
        for (j = 0; j <(n); j++) {

            if (i != j) {
                zauxx = znx;
                zauxy = zny;
                znx = (zauxx * (x - u[j])) - (zauxy * (y - v[j]));
                zny = (zauxy * (x - u[j]) + (zauxx * (y - v[j])));
            }
        }

        zndx+=znx;
        zndy+=zny;
    }

    //valors a dpx i dpy
    *dpx=zndx;
    *dpy=zndy;
}

int cnvnwt (double x, double y, double tolcnv, int maxit,
      int n, double u[], double v[]) {
    //declaració de variables
    int i,j;
    double px, py, dpx, dpy,dist, xaux, yaux;

    //bucle for per aplicar la formula de newton
    for(i=0;i<maxit;i++){

        xaux=x;
        yaux=y;

        //càlcul de p(z) i p'(z)
        avalp(x, y, &px, &py, n, u, v);
        avaldp(x, y, &dpx, &dpy, n, u, v);

        //formula de newton separant part real i imaginaria
        x=(xaux-(((px*dpx)+(py*dpy))/((dpx*dpx)+(dpy*dpy))));
        y=(yaux-(((py*dpx)-(px*dpy))/((dpx*dpx)+(dpy*dpy))));

        //bucle per veure si es més petit que la tolerancia
        for(j=0;j<n;j++){
            dist=sqrt(((x-u[j])*(x-u[j]))+((y-v[j])*(y-v[j])));
            //printf("Distancia: %lf\n",dist);
            if(dist<tolcnv){
                return j;
            }
        }
    }

    /*si i ha arribat al valor de maxit significa que no s'ha fet el return anterior
     * y per tant no s'ha trobat resultat*/
    return -1;
}

