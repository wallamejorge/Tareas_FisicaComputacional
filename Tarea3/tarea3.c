/*
Tarea #3 Fisica Computacional
Nombre:Jorge Luis Mayorga	
Codigo:20111082
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//-----------------------------------------------------//
// Declaracion de funciones auxiliares                 //
//-----------------------------------------------------//
int count_row(FILE *in),filename_verified(char *nombrearchivo);
int generate_vectors(char *nombre_archivo_datos,float *y,float *t,int n_filas);
int generate_G(float *G,float *t,int n_filas); 
//-----------------------------------------------------//

int main(int argc, char **argv)
{
//Declaracion de variables//
FILE *in;
int n_columnas=2,n_filas,datos,i;
char nombre_archivo_datos[256];
float *G,*m,*d,*t,*y;

strcpy(nombre_archivo_datos,argv[1]);
printf("El nombre del archivo es : %s \n\n",nombre_archivo_datos);

filename_verified(nombre_archivo_datos);

in = fopen(nombre_archivo_datos,"r"); 
n_filas=count_row(in);
fclose(in);
printf("EL numero de filas es :%d \n\n",n_filas);

int vectores_ok=generate_vectors(nombre_archivo_datos,y,t,n_filas);
int G_ok=generate_G(G,t,n_filas);




 
return 0;
}




// FUNCION 0:VERIFICAR SI SE PUEDE ABRIR ARHCIVO //
filename_verified(char *nombrearchivo){
FILE *in;
if(!(in=fopen(nombrearchivo, "r"))){
fprintf(stderr, "Problemas abriendo el archivo  %s\n", nombrearchivo);}
return 0;
}
// FUNCION 1:CONTAR LINEAS //
count_row(FILE *in)
{int i=0;
char caracteres[100];
while (feof(in) == 0)
{fgets(caracteres,100,in);i=i+1;}
return i-1;
}
// FUNCION 2:GENERADOR VECTORES //
generate_vectors(char *nombre_archivo_datos,float *y,float *t,int n_filas){
int i=0;
int salida=0;
FILE *in;
if(!(y = malloc(sizeof(float)*n_filas))){
fprintf(stderr, "Problem with memory allocation");salida=1;}
if(!(t = malloc(sizeof(float)*n_filas))){
fprintf(stderr, "Problem with memory allocation");salida=1;}
in = fopen(nombre_archivo_datos,"r"); 
for(i=0;i<n_filas;i++){
fscanf(in,"%f %f",&y[i],&t[i]);
printf("%f %f\n",y[i],t[i]);}
fclose(in);
salida=0;
return salida;}
// FUNCION 3:GENERADOR DE MATRIZ m //
generate_G(float *G,float *t,int n_filas){
int salida=0,n_param=3,i,j,fila_m_llena=0;
float t1=0.0,t2=0.0,t3=0.0;
for(i=0;i<(n_filas);i++){
for(j=0;j<(n_param);j++){

// ACA TENGO UN ERROR!!!!!!!!!!!!1
&G[i+j]=i+j;
// ACA ACABA EL ERROR
}}
return salida;
}























