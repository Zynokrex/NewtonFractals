#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "nwtfr.h"

int main (int argc, char *argv[]) {

    /*xmn i xmx defineixen la x del rectangle R
     *ymn i ymx defineixen la y del rectangle R
     *tolcnv defineix la tolerancia del cnvnwt*/

   double xmn, xmx, ymn, ymx, tolcnv;

   /*nx defineix el nombre de punts horitzontals
    *ny defineix el nombre de punts verticals
    *maxit defineix el nombre maxim d'interacions de cnvnwt
    *narr defineix el nombre d'arrels*/

   int nx, ny, maxit, narr;

/* Línia de comandes
   int narr double xmn double xmx int nx double ymn double ymx int ny double tolcnv int maxit
 */
   if (argc<10
         || sscanf(argv[1], "%d", &narr)!=1
         || sscanf(argv[2], "%lf", &xmn)!=1
         || sscanf(argv[3], "%lf", &xmx)!=1
         || sscanf(argv[4], "%d", &nx)!=1
         || sscanf(argv[5], "%lf", &ymn)!=1
         || sscanf(argv[6], "%lf", &ymx)!=1
         || sscanf(argv[7], "%d", &ny)!=1
         || sscanf(argv[8], "%lf", &tolcnv)!=1
         || sscanf(argv[9], "%d", &maxit)!=1
      ) {
       fprintf(stderr, "%s narr xmn xmx nx ymn ymx ny tolcnv maxit\n", argv[0]);
       return -1;
   }

   /*u conté la part real de l'arrel i v la part imaginaria
    *R, G, B contenen els colors en RGB(R=RED, G=GREEN, B=BLUE)
    * index es el index de l'arel a la que tendeix*/

   int R[narr],G[narr],B[narr],i,j,index;
   double u[narr], v[narr], x, y, Ax, Ay;
   /*Entrada de les arrels i els valors R, G i B*/

   for(i=0;i<narr;i++){
       scanf("%lf %lf %d %d %d",&u[i],&v[i],&R[i],&G[i],&B[i]);
   }

   /*generació de punts + cnvnwt + pas a arxiu
    *pas a arxiu: print de PuntCreat + RGB de l'arrel a la que s'acosta
    *si cnvnwt fa return de -1, el punt és blanc (RGB= 255 255 255)
    *si cnvnwt retorna l'index, es fa el print amb els colors de la conca
    * d'atracció corresponent*/
   Ax=((xmx-xmn)/nx);
   Ay=((ymx-ymn)/ny);
   for(i=0;i<=nx;i++){
       x=xmn+(i*Ax);
       for(j=0;j<=ny;j++){
           y=ymn+(j*Ay);
           index=cnvnwt(x,y,tolcnv,maxit,narr,u,v);
           if(index!=-1){
               //es multiplica per 255 pq RGB cada part va de 0 fins 255
               printf("%lf %lf %d %d %d\n",x,y,R[index]*255,G[index]*255,B[index]*255);

           }
           else{
               printf("%lf %lf %d %d %d\n",x,y,255,255,255);
           }
       }
   }
   return 0;
}
