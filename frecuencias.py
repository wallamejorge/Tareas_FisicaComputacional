'''
Tarea No.2 Fisica Computacional Uniandes 
Autor:Jorge Luis Mayorga Taborda
Codigo:201110382
'''

'''
 ____________________________________
|                                    |
|Modulo 0 para importar Librerias    |
|____________________________________|
'''
import sys, string, os,codecs
'''
'''
def invertDictionary(orig_dict):
    result = {} # or change to defaultdict(list)
    for k, v in orig_dict.iteritems():
        result.setdefault(v, []).append(k)

def contar_letras(s):
    d = {}
    for letra in s:
        if not letra in d:
            d[letra] = 1
        else:
            d[letra] = d[letra] + 1
    return d





'''
 ____________________________________
|                                    |
|Modulo 1 Adquisicion de parametros  |
|____________________________________|
'''

n_args = len(sys.argv)




#Verificar entrada de datos

if(n_args!=2):
 print "Ingrese solo como parametro el nombre del libro" 
 sys.exit(1)

libro=sys.argv[1];
librolong=len(libro);

if((libro[librolong-1]=='t') and (libro[librolong-2]=='x') and (libro[librolong-3]=='t') and (libro[librolong-4]=='.')):
 print "  "
 print "  "
 print "|---------------------------------------------|"
 print "|El formato del archivo del libro es .txt ....|"
 print "|Inicializando programa en python.....        |"
 print "|Llamando al arhivo "+libro                
 print "|---------------------------------------------|"
 print "  "
 print "  "
else:
 print "Ingrese un nombre de archivo con formato .txt, el que ud ingreso no es .txt.... :(  ....ABORTANDO PROGRAMA!!!...."
 sys.exit(1)

# Lectura del archivo
infile = open(libro, 'r')
#Cargar el texto por caracteres
fulltext= infile.readlines()
palabras="";

#clean and split
for i in range(len(fulltext)):
 linea_instantanea=fulltext[len(fulltext)-i-1].rstrip('\n')+""
 for j in range(len(linea_instantanea)):
  palabras=""+linea_instantanea[len(linea_instantanea)-j-1]+palabras 


totalletras=0;

palabras=palabras.replace(".","")
palabras=palabras.replace(",","")
palabras=palabras.replace(":","")
palabras=palabras.replace(";","")
palabras=palabras.replace(" ","")
palabras=palabras.replace("\\n","")
palabras=palabras.replace("\n","")
palabras=palabras.replace("","")

listadecaracteres=palabras
   
'''
 ____________________________________
|                                    |
|Modulo 2 Procesamiento de los datos |
|____________________________________|
'''
#Defino el diccionario
cuentaLetras = {}


#Codigo para escribir archivo
nombrearchivodesalida="frecuencias_"+libro;
f=open(nombrearchivodesalida,"w")
f.write(" \n")
f.write("Bienvenido!\n")
f.write("\n")
f.write("\n")
f.write("Caracter=frecuencia en el texto\n")
f.write("\n")
f.write("\n")

#llamo a contador letras
h =contar_letras(listadecaracteres)

totalletras=len(palabras);

temp=0.0



for w in sorted(h, key=h.get, reverse=True):
  temp=0.0
  temp=((h[w]+0.0)/totalletras)*100
  f.write(' {} = {}% '.format(w,temp))
  temp=0.0
  f.write("\n")
 
print  "Fin de programa con exito!\n"

f.close()







infile.close()



