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
import matplotlib.pyplot as plt

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
intentos1=list_names[0:300]
intentos2=list_names[300:600]
intentos3=list_names[600:900]
intentos4=list_names[900:1200]
intentos5=list_names[1200:1500]
intentos6=list_names[1500:1800]

thetas_experimento_1=[]
thetas_experimento_2=[]
thetas_experimento_3=[]
thetas_experimento_4=[]
thetas_experimento_5=[]
thetas_experimento_6=[]

gmedia=[]

for i in range(300):

 temp1=intentos1[i].replace('experimentID_0_theta_','')
 temp1=temp1.replace('.dat','')
 thetas_experimento_1.append(temp1)
 fiit_exp1_i=fittFile(intentos1[i])
 gmedia_exp1=fiit_exp1_i[4]
 
 temp2=intentos2[i].replace('experimentID_1_theta_','')
 temp2=temp2.replace('.dat','')
 thetas_experimento_2.append(temp2)
 fiit_exp2_i=fittFile(intentos2[i])
 gmedia_exp2=fiit_exp2_i[4]
 
 temp3=intentos3[i].replace('experimentID_2_theta_','')
 temp3=temp3.replace('.dat','')
 thetas_experimento_3.append(temp3)
 fiit_exp3_i=fittFile(intentos3[i])
 gmedia_exp3=fiit_exp3_i[4]
 
 temp4=intentos4[i].replace('experimentID_3_theta_','')
 temp4=temp4.replace('.dat','')
 thetas_experimento_4.append(temp4)
 fiit_exp4_i=fittFile(intentos4[i])
 gmedia_exp4=fiit_exp4_i[4]
 
 temp5=intentos5[i].replace('experimentID_4_theta_','')
 temp5=temp5.replace('.dat','')
 thetas_experimento_5.append(temp5)
 fiit_exp5_i=fittFile(intentos5[i])
 gmedia_exp5=fiit_exp5_i[4]
 
 temp6=intentos6[i].replace('experimentID_5_theta_','')
 temp6=temp6.replace('.dat','')
 thetas_experimento_6.append(temp6)
 fiit_exp6_i=fittFile(intentos6[i])
 gmedia_exp6=fiit_exp6_i[4]
 
 gmedia.append((gmedia_exp1+gmedia_exp2+gmedia_exp3+gmedia_exp4+gmedia_exp5+gmedia_exp6)/6)
#MODULO.4:Graficar theta=x gmedia(1 to 6 exp)=y

plt.plot(thetas_experimento_1,gmedia,'ro')
plt.show()
  
  
  
  
  
  
  
  
  

