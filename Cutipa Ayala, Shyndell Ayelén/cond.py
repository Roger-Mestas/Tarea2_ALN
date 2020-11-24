import numpy as np # para trabajar con arreglos
from math import factorial 
import math
from pprint import pprint #imprimir las matrices
from msvcrt import getch

##########################################
# MATRIZ HILBERT Y VANDERMONDE E INVERSA #
##########################################
def hilb(n, m=0):

    # Evaluamos condiciones
    if n < 1 or m < 0:
        raise ValueError("El orden de la matriz debe ser uno o mas")
    elif n == 1 and (m == 0 or m == 1):
        return np.array([[1]])
    elif m == 0:
        m = n
    # Generamos la matriz de hilbert con la fórmula
    v = np.arange(1, n + 1) + np.arange(0, m)[:, np.newaxis]

    return 1./v


def vandermonde(n,arr, m=0):
    
    # Evaluamos condiciones
    if n < 1 or m < 0:
        raise ValueError("El orden de la matriz debe ser uno o mas")
    elif n == 1 and (m == 0 or m == 1):
        return np.array([[1]])
    elif m == 0:
        m = n
    # Generamos la matriz de vandermonde

    vandermonde = np.vander(arr, increasing = True) 
    vandermonde = np.array(vandermonde, dtype=np.float64)

    return vandermonde


def binomial(n, k):

    if k < 0 or k > n:
        return 0
    if k == 0 or k == n:
        return 1
    
    return factorial(n) // (factorial(k) * factorial(n-k))


def inversa(n):

    H = np.empty((n, n))
    for i in range(n):
        for j in range(n):
            H[i, j] = ((-1)**(i + j)) * (i + j + 1) * binomial(n + i, n - j - 1) * \
             binomial(n + j, n - i - 1) * binomial(i + j, i) ** 2
    return H


###################
#      NORMAS     #
###################

# Norma uno
def norma_uno(matriz):

	n = len(matriz)
	t = [[matriz[j][i] for j in range(len(matriz))] for i in range(len(matriz[0]))] 
	sum = [] 
	rows = 0 
	count = 0 
	for i in t: 
		for j in i: 
			rows += abs(j) #suma los elementos en valor absoluto de cada una de las columnas
			count += 1 
			if count == n: 
				sum.append(rows) # agrega el resultado al arreglo sum
				rows = 0 
				count = 0 
	norma1 = max(sum) # encuentra el maximo de la sumas del arreglo sum
	return norma1 

# Norma Frobenius
def normafrobenius(matriz):
    f = 0
    # recorrido por las filas y columnas
    for i in np.arange(len(matriz)):
        for j in np.arange(len(matriz)):
            # almacena la suma de los cuadrados de los elementos de la matriz
            f = f + np.sum(np.power(np.abs(matriz[i, j]), 2))
    normaf = np.sqrt(f) # saca raiz al resultado de f
    return normaf


# Norma 2
def norma_dos(matriz):
    # Intercambio de filas por columnas para realizar la transpuesta
    T = [[0 for x in range(len(matriz))] for y in range(len(matriz))] 
    for i in range(len(matriz)): 
        for j in range(len(matriz)): 
            T[i][j] = matriz[j][i] 
    # Multiplicamos transpuesta y su matriz

    M = [[0 for x in range(len(matriz))] for y in range(len(matriz))] 

    for i in range(len(T)):
        for j in range(len(matriz[0])):
            for k in range(len(matriz)):
                M[i][j] += T[i][k] * matriz[k][j]
    #hallamos los eigenvalores
    E = [[]]
    E = np.linalg.eigvals(M)
    # Se halla el mayor valor de los eigenvalores
    max = E[0] 
    for i in range(1, len(E)): 
        if E[i] > max: 
            max = E[i]
    # Sacamos raíz al mayor de los eigenvalores        
    norma2 = pow(max, 0.5)
    return norma2

# Norma infinita
def norma_inf(matriz):
	n = len(matriz) 
	sum = []        
	rows = 0        
	count = 0       
	for i in matriz:
		for j in i:
			rows += abs(j) # suma los elementos en valor absoluto de cada una de las filas
			count += 1  
			if count == n: 
				sum.append(rows) # agrega el resultado a sum
				rows = 0 
				count = 0 
	normainf = max(sum) # encuentra el maximo en el arreglo sum
	return normainf 

 
print("****************************************************************")
print("PROGRAMA PARA HALLAR EL NUMERO DE CONDICIONAMIENTO DE UNA MATRIZ")
print("****************************************************************")
print("Elija una opcion:")
print("****************************************")
print("1. Matriz de Hilbert")
print("2. Matriz de Vandermonde")
opcion = int(input("presione 1 o 2: "))

###########################
# NRO DE CONDICIONAMIENTO #
###########################

if opcion == 1:
    n = int(input("Longitud de la Matriz de Hilbert: "))
    print("****************************************+")
    print("Matriz de Hilbert:")
    H = hilb(n)
    pprint(H)
    print("****************************************+")
    print("Inversa de la Matriz de Hilbert:")
    pprint(inversa(n))

    
    print("*******************************************************")
    print("ELIJA LA NORMA CON LA QUE TRABAJARÁ EL CONDICIONAMIENTO")
    print("*******************************************************")
    print("1. Norma 1")
    print("2. Norma 2")
    print("3. Norma de Frobenius")
    print("4. Norma Infinita")
    op2 = int(input("Ingrese la opcion: "))
    print("******************************************************")
    if op2 == 1: 
        print("Nro de condicionamiento con norma 1: ")
        cond1 = norma_uno(H) * norma_uno(inversa(n))
        k1 = np.around(cond1, decimals=6)
        print(k1)
    
    elif op2 == 2:
        print("Nro de condicionamiento con norma 2: ")
        cond2 = norma_dos(H) * norma_dos(inversa(n))
        print(cond2)
    elif op2 == 3:
        print("Nro de condicionamiento con norma de frobenius:")
        condfr = normafrobenius(H) * normafrobenius(inversa(n))
        print(condfr)
    elif op2 == 4:
        print("Nro de condicionamiento con norma infinita: ")
        condinf = norma_inf(H) * norma_inf(inversa(n))
        kinf = np.around(condinf, decimals=6)
        print(kinf)


elif opcion == 2:
    m = int(input("Longitud de la Matriz de Vandermonde: "))
    arr = []
    print("Ingrese los valores del vector...")
    print("Ejemplo:")
    print("Vector con valores : 1 2 3")
    print("Genera matriz Vandermonde: 1 1 1")
    print("                           1 2 4")
    print("                           1 3 9")
    
    for i in range (0,m):
        print("Vector[ 1 ][",i+1,"]")
        e= float(input("Valor: "))
        arr.insert(i, e)
    print("*******************************************************")
    print("ELIJA LA NORMA CON LA QUE TRABAJARÁ EL CONDICIONAMIENTO")
    print("*******************************************************")
    print("1. Norma 1")
    print("2. Norma 2")
    print("3. Norma de Frobenius")
    print("4. Norma Infinita")
    op2 = int(input("Ingrese la opcion: "))
    print("******************************************************")
    print("Vector: ")
    print(arr)
    print("******************************************************")
    print("Matriz de Vandermonde:")
    V = vandermonde(m,arr)
    pprint(V)
    print("******************************************************")
    print("Inversa de la Matriz Vandermonde: ")
    pprint(np.linalg.inv(V))
    if op2 == 1:
        print("Nro de condicionamiento con norma 1: ")
        cond1 = norma_uno(V) * norma_uno(np.linalg.inv(V))
        print(cond1)
    elif op2 == 2:
        print("Nro de condicionamiento con norma 2: ")
        cond2 = norma_dos(V) * norma_dos(np.linalg.inv(V))
        print(cond2)
    elif op2 == 3:
        print("Nro de condicionamiento con norma de frobenius:")
        condfr = normafrobenius(V) * normafrobenius(np.linalg.inv(V))
        print(condfr)
    elif op2 == 4:
        print("Nro de condicionamiento con norma infinita: ")
        condinf = norma_inf(V) * norma_inf(np.linalg.inv(V))
        print(condinf)

print("Presione enter para salir del programa")
getch()