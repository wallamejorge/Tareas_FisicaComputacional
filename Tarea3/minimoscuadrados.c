/*
Tarea #3 Fisica Computacional
Nombre:Jorge Luis Mayorga
Codigo:20111082
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>

//-----------------------------------------------------//
// Declaracion de funciones auxiliares                 //
//-----------------------------------------------------//

int count_row(FILE *in),filename_verified(char *nombrearchivo);
float *generate_vectors(char *nombre_archivo_datos,int n_filas);
float *generate_G(float *G,float *yt,int n_filas);
float *transpose(float *M,int n_filas);
float *multiply(float *A,float *B,int n_filas);
float *inverse(float *M);
float *inverse3x3(float *M);
float *generate_d(float *yt,int n_filas);
float *Dmultiply(float *Gt,float *d,int n_filas);
float *Mmultiply(float *A,float *B,int n_filas);
void impresion(float *m);

//-----------------------------------------------------//
// Funcion MAIN                                        //
//-----------------------------------------------------//

int main(int argc, char **argv)
{
  FILE *in;
  int n_columnas=2,n_filas,datos,i=0,j=0,n=0,pos;
  char nombre_archivo_datos[256];       
  float*G=NULL;
  float*d=NULL;
  float*t=NULL;
  float*y=NULL;
  float*Gt=NULL;
  float*Gt_G=NULL;
  float*InvGt_G=NULL;
  float*Gt_d=NULL;
  float*m=NULL;
  float*yt=NULL;
  float*InvGt_G3x3=NULL;
        
  strcpy(nombre_archivo_datos,argv[1]);//Copio el nombre del .txt en la cadena
  printf("\n|------------------------------------------------|\n"); 
  printf("\n El nombre del archivo es : %s \n",nombre_archivo_datos);//Imprimo Nombre del archivo

  filename_verified(nombre_archivo_datos);//Verifica si existe archivi.txt
  in = fopen(nombre_archivo_datos,"r");//Abre archivo
  n_filas=count_row(in);//Contar filas

  fclose(in);//Cerrar archivo
  printf("\n EL numero de filas es :%d \n",n_filas);//Imprimo el numero de filas
  printf("\n|------------------------------------------------|\n"); 
  yt=generate_vectors(nombre_archivo_datos,n_filas);
  d=generate_d(yt,n_filas);
  G=generate_G(G,yt,n_filas);
  Gt=transpose(G,n_filas);
  Gt_G=multiply(Gt,G,n_filas);
  InvGt_G=inverse(Gt_G);
  Gt_d=Dmultiply(Gt,d,n_filas);
  m=Mmultiply(InvGt_G,Gt_d,n_filas);
  impresion(m);
  
  
  
//-----------------------------------------------------//
// Modulo de pruebas                                   //
//-----------------------------------------------------//

//Mod.1:Prueba de yt
/*
  for(i=0;i<(n_filas);i++){
  printf("t[%d]=%f t[%d]=%f \n",i,yt[2*i+1],i,yt[2*i]);
  }
   
 return 0;
}
*/

//Mod.2:Prueba de d
/*
  for(i=0;i<(n_filas);i++){
  printf("d[%d]=%f \n",i,d[i]);
  }
*/

//Mod.3:Prueba de G
/*
  for(i=0;i<(n_filas);i++){
   for(j=0;j<3;j++){
    printf("G[%d,%d]=%f ",i,j,G[3*i+j]);
  }
  printf("\n");
  }
*/

//Mod.4:Prueba de Transpose
/*
   for(j=0;j<3*n_filas;j++){
    printf("Gt[%d]=%f \n",j,Gt[j]);
  }
*/

//Mod.5:Prueba de Multiplicacion de matriz
/*
  for(i=0;i<(3);i++){
   for(j=0;j<3;j++){
    printf("Gt_G[%d,%d]=%f ",i,j,Gt_G[3*i+j]);
  }
  printf("Cambio de fila\n");
  }
*/

//Mod.6:Prueba de Inversion
/*
  for(i=0;i<(3);i++){
   for(j=0;j<3;j++){
    printf("Inv(Gt_G)[%d,%d]=%f ",i,j,InvGt_G[3*i+j]);
  }
  printf("Cambio de fila\n");
  }
*/

//Mod.7:Prueba Multiplicacion GT por d
/*
  for(i=0;i<(3);i++){
    printf("Gt_d[%d]=%f \n",i,Gt_d[i]);
  }
*/
//Mod.8:Prueba m

  for(i=0;i<(3);i++){
    printf("m[%d]=%f \n",i,m[i]);
  }


 return 0;
}


//Funcion0:Filename_verified//
int filename_verified(char *nombrearchivo){
  FILE *in;
  if(!(in=fopen(nombrearchivo, "r"))){
    fprintf(stderr, "Problemas abriendo el archivo %s\n", nombrearchivo);
  }
  return 0;
}

//Funcion1:Count_row//
int count_row(FILE *in){
  int i=0;
  char caracteres[100];
  while (feof(in) == 0){
    fgets(caracteres,100,in);
    i=i+1;
  }
  return i-1;
}

//Funcion2:Generate_vectors//
float *generate_vectors(char *nombre_archivo_datos,int n_filas){
  int i=0;  
  int salida=1;
  FILE *in;
  float *yt;
  
  if(!(yt = malloc(sizeof(float)*n_filas*2))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }

  in = fopen(nombre_archivo_datos,"r");
  for(i=0;i<n_filas;i++){
    fscanf(in,"%f %f",&(yt[i*2]),&(yt[i*2 +1]));
  }
  fclose(in);
  return yt;
}

//Funcion3:Generate_d//
float *generate_d(float *yt,int n_filas){
 float *d=NULL;
 int i;
 if(!(d = malloc(sizeof(float)*n_filas*3))){
    fprintf(stderr, "Problem with memory allocation");
   }
 for(i=0;i<2*n_filas;i++){ 
   d[i]=yt[2*i+1];
  }
return d;
}

//Funcion4:Generate_G//
float *generate_G(float *G,float *yt,int n_filas){
  int salida=1,n_param=3,i=0,j=0,n=0;
  float *t=NULL;
 
 if(!(t = malloc(sizeof(float)*n_filas))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }
  
  if(!(G = malloc(sizeof(float)*n_filas*n_param))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }
  
  for(i=0;i<(n_filas);i++){  
    t[i]=yt[2*i];
     }
     
  for(i=0;i<(n_filas);i++){
  n=3*i;
    for(j=0;j<(n_param);j++){
     if(j==0){
      G[n+j]=1;
      }
     if(j==1){
      G[n+j]=t[i];
      }
      if(j==2){
      G[n+j]=t[i]*t[i];
      }
    }
  }
return G;
}

//Funcion5:transpose//
float *transpose(float *M,int n_filas){
 int i, j;
 float *Salida;

 if(!(Salida = malloc(sizeof(float)*n_filas*3))){
    fprintf(stderr, "Problem with memory allocation");
  }
 gsl_matrix * trans = gsl_matrix_alloc (3,n_filas);
 gsl_matrix * original = gsl_matrix_alloc (n_filas,3);
 
 for(i=0;i<(n_filas);i++){
  for(j=0;j<(3);j++){
   gsl_matrix_set(original, i, j, M[3*i+j]);
  } 
 }
 
 for(i=0;i<(n_filas);i++){
   Salida[i]=gsl_matrix_get(original,i,0);
  } 
 for(i=0;i<(n_filas);i++){
   Salida[i+n_filas]=gsl_matrix_get(original,i,1);
  } 
for(i=0;i<(n_filas);i++){
   Salida[i+2*n_filas]=gsl_matrix_get(original,i,2);
  } 
 return Salida;
}

//Funcion6:Multiplicar G por Gt//
float *multiply(float *A,float *B,int n_filas){
 int i,j,l,pos,k;
 float *c=NULL;
 float temp,k1=0,k2=0,k3=0,k4=0,k5=0,k6=0,k7=0,k8=0,k9=0;
 
 if(!(c = malloc(sizeof(float)*3*3))){
    fprintf(stderr, "Problem with memory allocation");
  }
    
  for(i=0;i<n_filas;i++){
    temp=k1;
    k1=A[0*n_filas+i]*B[3*i];
    k1=temp+k1;
 }
 temp=0;
  for(i=0;i<n_filas;i++){
    temp=k2;
    k2=A[1*n_filas+i]*B[3*i];
    k2=temp+k2;
 }
 for(i=0;i<n_filas;i++){
    temp=k3;
    k3=A[2*n_filas+i]*B[3*i];
    k3=temp+k3;
 } 
  for(i=0;i<n_filas;i++){
    temp=k4;
    k4=A[0*n_filas+i]*B[3*i+1];
    k4=temp+k4;
 }
  for(i=0;i<n_filas;i++){
    temp=k5;
    k5=A[1*n_filas+i]*B[3*i+1];
    k5=temp+k5;
 }
 for(i=0;i<n_filas;i++){
    temp=k6;
    k6=A[2*n_filas+i]*B[3*i+1];
    k6=temp+k6;
 }
   for(i=0;i<n_filas;i++){
    temp=k7;
    k7=A[0*n_filas+i]*B[3*i+2];
    k7=temp+k7;
 }
  for(i=0;i<n_filas;i++){
    temp=k8;
    k8=A[1*n_filas+i]*B[3*i+2];
    k8=temp+k8;
 }
 for(i=0;i<n_filas;i++){
    temp=k9;
    k9=A[2*n_filas+i]*B[3*i+2];
    k9=temp+k9;
 }
 

c[0]=k1;
c[1]=k2;
c[2]=k3;
c[3]=k4;
c[4]=k5;
c[5]=k6;
c[6]=k7;
c[7]=k8;
c[8]=k9;

return c;
}

//Funcion6:Invierte matriz 3x3//
float *inverse(float *M){
 float *invM=NULL;
 if(!(invM = malloc(sizeof(float)*3*3))){
    fprintf(stderr, "Problem with memory allocation");
   }
 int n=3,i,j,k;
 int s;

 gsl_matrix * m = gsl_matrix_alloc (n, n);
 gsl_matrix * inverse = gsl_matrix_alloc (n, n);
 gsl_permutation * perm = gsl_permutation_alloc (n);
 
 for(i=0;i<3;i++){
   for(j=0;j<3;j++){
   gsl_matrix_set(m,i,j,M[3*i+j]);
   }
  }


 gsl_linalg_LU_decomp (m, perm, &s);

	// Invert the matrix m
 gsl_linalg_LU_invert (m, perm, inverse);

  for(i=0;i<3;i++){
   for(j=0;j<3;j++){
   invM[3*i+j]=gsl_matrix_get(inverse,i,j);
   }
  }
 return invM;
}
float *Dmultiply(float *A,float *B,int n_filas){
 int i,j,l,pos;
 float *salida=NULL;
 float *c=NULL;
 float temp,k1=0,k2=0,k3=0;
 if(!(c = malloc(sizeof(float)*1*3))){
    fprintf(stderr, "Problem with memory allocation");
  }

  for(i=0;i<n_filas;i++){
    temp=k1;
    k1=A[0*n_filas+i]*B[i];
    k1=temp+k1;
 }
  for(i=0;i<n_filas;i++){
    temp=k2;
    k2=A[1*n_filas+i]*B[i];
    k2=temp+k2;
 }
 for(i=0;i<n_filas;i++){
    temp=k3;
    k3=A[2*n_filas+i]*B[i];
    k3=temp+k3;
 }

c[0]=k1;
c[1]=k2;
c[2]=k3;
 
 return c;
}
float *Mmultiply(float *A,float *B,int n_filas){
  int i,j,l,pos;
 float *salida=NULL;
 float *c=NULL;
 float temp,k1=0,k2=0,k3=0;
 
 if(!(c = malloc(sizeof(float)*1*3))){
    fprintf(stderr, "Problem with memory allocation");
  }

  for(i=0;i<3;i++){
    temp=k1;
    k1=A[0*3+i]*B[i];
    k1=temp+k1;
 }
  for(i=0;i<3;i++){
    temp=k2;
    k2=A[1*3+i]*B[i];
    k2=temp+k2;
 }
 for(i=0;i<3;i++){
    temp=k3;
    k3=A[2*3+i]*B[i];
    k3=temp+k3;
 }

c[0]=k1;
c[1]=k2;
c[2]=k3;
 return c;
}
void impresion(float *m){
 FILE *fileout;
 fileout=fopen("parametros_movimiento.dat","w");
 fprintf(fileout,"%f %f %f",m[0],m[1],m[2]);
}







