# -----------------------------------------------------------------------------#
# Tarea #4 Fisica Computacional                                                #
# Nombre:Jorge Luis Mayorga                                                    #
# Codigo:20111082                                                              #
# -----------------------------------------------------------------------------#

#Importar librerias 
import sys,codecs,math
import numpy as np
import os
from numpy import mean,cov,double,cumsum,dot,array,rank
from pylab import plot,subplot,axis,stem,show,figure
from numpy import linalg as LA

def fittFile(namefile):
 text=namefile.replace('\n','') 
 data=np.loadtxt(text,comments='#')
 t=data[:,0]
 x=data[:,1]
 y=data[:,2]
 mx=np.polyfit(t,x,1)
 my=np.polyfit(t,y,2)
 vx0=mx[0]
 x0=mx[1]
 gtemp=my[0]
 g=(-2)*gtemp
 vy0=my[1]
 y0=my[2]
 retorno=[x0,vx0,y0,vy0,g]
 return retorno

def write_file_fittParam(FittparamOut, namefile, paramFit):
 mensaje=namefile+' '+str(paramFit[0])+' '+str(paramFit[1])+' '+str(paramFit[2])+' '+str(paramFit[3])+' '+str(paramFit[4])+' '+"\n"
 FittparamOut.write(mensaje)

def PCA(A):
 sigma=cov(A)
 eigenvalues, eigenvectors =LA.eig(sigma)
 return eigenvectors
 
def PCA(A):
 sigma=cov(A)
 eigenvalues, eigenvectors =LA.eig(sigma)
 return eigenvectors

#MODULO.0:Leer los nombres de los archivos en la lista :list_names
names_files=open('nombres_archivos_hw4_data.txt','r')
list_names=names_files.readlines()
names_files.close()


#MODULO.1:Fiting de los parametros de cada archivo de los 1800
paramFit = []

for i in range(3):
 paramFit.append([])
 for j in range(len(list_names)):
  paramFit[i].append(None)
  
for j in range(len(list_names)):
 paramFitemp=fittFile(list_names[j])
 paramFit[0][j]=paramFitemp[1]#Velocidad en x
 paramFit[1][j]=paramFitemp[3]#Velocidad en y
 paramFit[2][j]=paramFitemp[4]#Gravedad g

#MODULO.2:PCA para comprobar que la g no varia segun vs
eigenvectorsPCA=PCA(paramFit)

#MODULO.3:Generar lista con el valor promedio de los 6 exp de g para cada theta



