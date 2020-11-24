def Hilbert(n) :
    H=[]   
    for i in range (n): 
        for j in range (n): 
            H[i][j] = 1.0 /((i + 1) + (j + 1) - 1.0)  
  
    for fila in H:
            print("[", end = " ")
            for elemento in fila:
                print("{:8.2f}".format(elemento), end= " ")
            print("]")
    print() 
def Vander(monde,vander) :
    matriz11=[]
    v1=[]
    tmp = 1
    contador = 0
    while tmp<=monde:
                tmp= tmp + vander
                contador=contador +1    
    a = 1
    for i in range (contador):
        for j in range (contador):
                if( i == 0):
                        matriz[i][j] = 1
                elif (i == 1):
                    if(j==0):
                            matriz[i][j]= 1
                        
                    else:
                            a = a+vander
                            matriz[i][j]= a
                else: 
                    matriz[i][j]= matriz[i-1][j]*matriz[i-1][j] 
                    
    for i in range(contador):
        for j in range (contador):
            print(matriz[i][j]," ")
        print()
    mayor = 0
    for i in range (contador):
        a= 0
        tmp = 0
        for j in range(contador):
            a = abs(matriz11[i][j])
            tmp += a
        v1.append(tmp)
    for i in range (contador):
        if(v1[i]>mayor):
            mayor = v1[i]        
        return mayor
def norma(matriz11,contador):
        v1=[]
        mayor = 0
        for i in range (contador):
            a= 0
            tmp = 0
            for j in range(contador):
                a = abs(matriz11[i][j])
                tmp += a                
            v1.append(tmp)
        for i in range(contador):
            if(v1[i]>mayor):
                mayor = v1[i]          
        return mayor
def nombra2(matriz):
    m = (np.linalg.norm((matriz), ord=2))
    matrizinv = np.linalg.inv(matriz)
    n = (np.linalg.norm((matrizinv), ord=2))
    print(m * n)
    return m * n
import numpy as np
from scipy.linalg import hilbert
menu = """
Menu 
1-Ingresar Matriz
2-Matriz Vandermonde
3-Matriz de Hilbert
4-Salir
"""

pop = True
while pop == True :
    print(menu)
    op = int(input("Elija un caso: "))  
    if op is 1:
        matriz =[]
        fila = int(input("Digite el tamaño de las filas de la matriz: "))
        columna = int(input("Digite el tamaño de las columnas de la matriz: "))
        for i in range(fila):
            matriz.append([])
            for j in range(columna):
                valor = float(input("Fila {}, Columna {}: ".format(i+1,j+1)))
                matriz[i].append(valor)
        print()
        for fila in matriz:
            print("[", end = " ")
            for elemento in fila:
                print("{:8.2f}".format(elemento), end= " ")
            print("]")
        print()
        menu1 = """
        1-Aplicar Norma 1
        2-Aplicar Norma inf
        3-Aplicar Norma 2
        """
        print(menu1)
        tmp = int(input("ingrese su opcion : "))
        if tmp is 1:
            y = np.linalg.inv(matriz)
            invnor = np.linalg.norm(y,1)
            nor = np.linalg.norm(matriz,1)
            print("El resultado de la matriz con la Norma 1 es: ",invnor * nor)
        elif tmp is 2:
            y = np.linalg.inv(matriz)
            invnor = np.linalg.norm(y,np.inf)
            nor = np.linalg.norm(matriz,np.inf)
            print("El resultado de la matriz con la Norma inf es: ",invnor * nor)
        elif tmp is 3:
            y = np.linalg.inv(matriz)
            invnor = np.linalg.norm(y,2)
            nor = np.linalg.norm(matriz,2)
            print("El resultado de la matriz con la Norma 2 es: ",invnor * nor)
        else :
            print("Tecla errada")
    elif op is 2:
        vector1 = []
        a = int(input("ingrese cantidad de elementos a ingresar: "))         
        for i in range (a): 
                valor = float(input("ingrese un numero que empiece en uno: "))
                vector1.append(valor)    
        menu1 = """
        1-Aplicar Norma 1
        2-Aplicar Norma inf
        3-Aplicar Norma 2
        """
        print(menu1)
        tmp = int(input("ingrese su opcion : "))
        if tmp is 1:
            x = np.vander(vector1)
            y = np.linalg.inv(x)
            invnor = np.linalg.norm(y,1)
            nor = np.linalg.norm(x,1)
            print("El resultado de la matriz con la Norma 1 es: ",invnor * nor)
        elif tmp is 2:
            x = np.vander(vector1)
            y = np.linalg.inv(x)
            invnor = np.linalg.norm(y,np.inf)
            nor = np.linalg.norm(x,np.inf)
            print("El resultado de la matriz con la Norma inf es: ",invnor * nor)
        elif tmp is 3:
            x = np.vander(vector1)
            y = np.linalg.inv(x)
            invnor = np.linalg.norm(y,2)
            nor = np.linalg.norm(x,2)
            print("El resultado de la matriz con la Norma 2 es: ",invnor * nor)
        else :
            print("Tecla errada")
    elif op is 3:
        a = int(input("ingrese el tamaño de la matriz: "))
        menu1 = """
        1-Aplicar Norma 1
        2-Aplicar Norma inf
        3-Aplicar Norma 2
        """
        print(menu1)
        tmp = int(input("ingrese su opcion : "))
        if tmp is 1:
            x = hilbert(a)
            y = np.linalg.inv(x)
            invnor = np.linalg.norm(y,1)
            nor = np.linalg.norm(x,1)
            print("El resultado de la matriz con la Norma 1 es: ",invnor * nor)
        elif tmp is 2:
            x = hilbert(a)
            y = np.linalg.inv(x)
            invnor = np.linalg.norm(y,np.inf)
            nor = np.linalg.norm(x,np.inf)
            print("El resultado de la matriz con la Norma inf es: ",invnor * nor)
        elif tmp is 3:
            x = hilbert(a)
            y = np.linalg.inv(x)
            invnor = np.linalg.norm(y,2)
            nor = np.linalg.norm(x,2)
            print("El resultado de la matriz con la Norma 2 es: ",invnor * nor)
        else :
            print("Tecla errada")
    else:
        pop = False
        print("Adios")