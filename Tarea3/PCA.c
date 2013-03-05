/*
Tarea #3 PCA Fisica Computacional
Nombre:Jorge Luis Mayorga
Codigo:20111082
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

//-----------------------------------------------------//
// Declaracion de funciones auxiliares                 //
//-----------------------------------------------------//

int count_row(FILE *in),filename_verified(char *nombrearchivo);
float *generate_vectorsX(char *nombre_archivo_datos,int n_filas);
float *generate_vectorX1(float *X,int n_filas);
float *generate_vectorX2(float *X,int n_filas);
float *generate_vectorX3(float *X,int n_filas);
float  expected_value(float *X,int n_filas);
float *Covariance_Matrix_generate(float *X1,float *X2,float *X3,float uX1,float uX2,float uX3,int M);
float *generate_eigenvectors(float *Sigma,int n_filas);
//-----------------------------------------------------//
// Funcion MAIN                                        //
//-----------------------------------------------------//

int main(int argc, char **argv)
{
  FILE *in;
  int n_columnas=2,n_filas,datos,i=0,j=0,n=0,pos=0,M=0;
  char nombre_archivo_datos[256]; 
  float *X=NULL,*X1=NULL,*X2=NULL,*X3=NULL,*sigma=NULL,*Eigenvectors=NULL;
  float uX1=0.0,uX2=0.0,uX3=0.0;     
        
  strcpy(nombre_archivo_datos,argv[1]);//Copio el nombre del .txt en la cadena
  printf("\n|------------------------------------------------|\n"); 
  printf("\n El nombre del archivo es : %s \n",nombre_archivo_datos);//Imprimo Nombre del archivo

  filename_verified(nombre_archivo_datos);//Verifica si existe archivi.txt
  in = fopen(nombre_archivo_datos,"r");//Abre archivo
  n_filas=count_row(in);//Contar filas
  M=n_filas;

  fclose(in);//Cerrar archivo
  printf("\n EL numero de filas es :%d \n",n_filas);//Imprimo el numero de filas
  printf("\n|------------------------------------------------|\n"); 
  
  X=generate_vectorsX(nombre_archivo_datos,n_filas);
  
  X1=generate_vectorX1(X,n_filas);  
  X2=generate_vectorX2(X,n_filas);  
  X3=generate_vectorX3(X,n_filas);
  
  uX1=expected_value(X1,n_filas);
  uX2=expected_value(X2,n_filas);
  uX3=expected_value(X3,n_filas);
  
  sigma=Covariance_Matrix_generate(X1,X2,X3,uX1,uX2,uX3,M); 
  Eigenvectors=generate_eigenvectors(sigma,n_filas);

  
//-----------------------------------------------------//
// Modulo de pruebas                                   //
//-----------------------------------------------------//

//Mod.1:Prueba de X1
/*
for(i=0;i<n_filas;i++){
printf("X1[%d]=%f \n",i,X1[i]);
}
*/
//Mod.2:Prueba de X2
/*
for(i=0;i<n_filas;i++){
printf("X2[%d]=%f \n",i,X2[i]);
}
*/
//Mod.3:Prueba de X3
/*
for(i=0;i<n_filas;i++){
printf("X3[%d]=%f \n",i,X3[i]);
}
*/
//Mod.4:Valores esperados(Promedios)
/*
printf("uX1=%f \n",uX1);
printf("uX2=%f \n",uX2);
printf("uX3=%f \n",uX3);
*/
//Mod.5:Prueba de Sigma

for(i=0;i<3;i++){
for(j=0;j<3;j++){
printf("Sigma[%d,%d]=%f      ",i,j,sigma[3*i+j]);
}
printf("\n");
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
float *generate_vectorsX(char *nombre_archivo_datos,int n_filas){
  FILE *in;
  int i=0;  
  int salida=1;
  float *X=NULL;
  
  if(!(X = malloc(sizeof(float)*n_filas*3))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }

  in = fopen(nombre_archivo_datos,"r");
  for(i=0;i<n_filas;i++){
    fscanf(in,"%f %f %f",&(X[i*3]),&(X[i*3+1]),&(X[i*3+2]));
  }
  fclose(in);
  return X;
}
//Funcion3:Generate_vectorX1//
float *generate_vectorX1(float *X,int n_filas){ 
  int i=0;  
  int salida=1;
  float *X1=NULL; 
  if(!(X1 = malloc(sizeof(float)*n_filas*3))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }
  for(i=0;i<n_filas;i++){
  X1[i]=X[3*i];
  }
return X1;
}
//Funcion4:Generate_vectorX2//
float *generate_vectorX2(float *X,int n_filas){ 
  int i=0;  
  int salida=1;
  float *X2=NULL; 
  if(!(X2 = malloc(sizeof(float)*n_filas*3))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }
  for(i=0;i<n_filas;i++){
  X2[i]=X[3*i+1];
  }
return X2;
}
//Funcion5:Generate_vectorX3//
float *generate_vectorX3(float *X,int n_filas){ 
  int i=0;  
  int salida=1;
  float *X3=NULL; 
  if(!(X3 = malloc(sizeof(float)*n_filas*3))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }
  for(i=0;i<n_filas;i++){
  X3[i]=X[3*i+2];
  }
return X3;
}
//Funcion6:Expected Value//
float  expected_value(float *X,int n_filas){
  int i=0,temp=0;
  float u=0;
  for(i=0;i<n_filas;i++){
    temp=u;
    u=X[i];
    u=temp+u;
  }
u=u/n_filas;
return u;
}
//Funcion7:Covariance_Matrix//
float *Covariance_Matrix_generate(float *X1,float *X2,float *X3,float uX1,float uX2,float uX3,int M){
  int i=0,temp=0,k=0;  
  int salida=1;
  float *sigma=NULL;
  float sigma_00,sigma_01,sigma_02,sigma_10,sigma_11,sigma_12,sigma_20,sigma_21,sigma_22; 
  if(!(sigma = malloc(sizeof(float)*M*3))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }
  
  //Para Sigma_00
  for(k=0;k<M;k++){
    temp=sigma_00;
    sigma_00=(X1[k]-uX1)*(X1[k]-uX1);
    sigma_00=temp+sigma_00;
  }
   //Para Sigma_01
  for(k=0;k<M;k++){
    temp=sigma_01;
    sigma_01=(X1[k]-uX1)*(X2[k]-uX2);
    sigma_01=temp+sigma_01;
  }
  //Para Sigma_02
  for(k=0;k<M;k++){
    temp=sigma_02;
    sigma_02=(X1[k]-uX1)*(X3[k]-uX3);
    sigma_02=temp+sigma_02;
  }
  //Para Sigma_10
  for(k=0;k<M;k++){
    temp=sigma_10;
    sigma_10=(X2[k]-uX2)*(X1[k]-uX1);
    sigma_10=temp+sigma_10;
  }
   //Para Sigma_11
  for(k=0;k<M;k++){
    temp=sigma_11;
    sigma_11=(X2[k]-uX2)*(X2[k]-uX2);
    sigma_11=temp+sigma_11;
  }
  //Para Sigma_12
  for(k=0;k<M;k++){
    temp=sigma_12;
    sigma_12=(X2[k]-uX2)*(X3[k]-uX3);
    sigma_12=temp+sigma_12;
  }
  //Para Sigma_20
  for(k=0;k<M;k++){
    temp=sigma_20;
    sigma_20=(X3[k]-uX3)*(X1[k]-uX1);
    sigma_20=temp+sigma_20;
  }
   //Para Sigma_21
  for(k=0;k<M;k++){
    temp=sigma_21;
    sigma_21=(X3[k]-uX3)*(X2[k]-uX2);
    sigma_21=temp+sigma_21;
  }
  //Para Sigma_22
  for(k=0;k<M;k++){
    temp=sigma_12;
    sigma_22=(X3[k]-uX3)*(X3[k]-uX3);
    sigma_22=temp+sigma_22;
  }




sigma[0]=sigma_00/(M-1);
sigma[1]=sigma_01/(M-1);
sigma[2]=sigma_02/(M-1);
sigma[3]=sigma_10/(M-1);
sigma[4]=sigma_11/(M-1);
sigma[5]=sigma_12/(M-1);
sigma[6]=sigma_20/(M-1);
sigma[7]=sigma_21/(M-1);
sigma[8]=sigma_22/(M-1);

return sigma;
}

float *generate_eigenvectors(float *Sigma,int n_filas){

int i=0;
double *data=NULL;
int salida=0;
if(!(data = malloc(sizeof(float)*3*3))){
    fprintf(stderr, "Problem with memory allocation");
    salida=0;
  }

  return Sigma;
}
