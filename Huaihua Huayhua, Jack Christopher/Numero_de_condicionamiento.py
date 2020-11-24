from math import sqrt
from decimal import *

#Genera una Matriz de Hilbert de n x n
def  hilbert(n):
	A = []
	indice = 0
	for i in range(n):
		temp = []
		for j in range(n):
			temp.append((Decimal(1/(i+j+1))))
		A.append(temp)

	return A


#Genera una matriz de Vandermonde de n x n  con en un vector ingresado 
def vandermonde(Vector, n):
	A = []
	indice = 0
	for i in range(n):
		temporal = Decimal(float(Vector[i]))
		temp = []
		for j in range(n):
			temp.insert(0, temporal**j)
		A.append(temp)

	return A


#Genera la Matriz Identidad de n x n 
#Se usa para la eliminacion gaussiana
def identidad(n):
	A = []
	for i in range(n):
		temp = []
		for j in range(n):
			if i == j:
				temp.append(1)
			else:
				temp.append(0)
		A.append(temp)
	return A


#Genera una copia de una Matriz A
#Se usa para no afectar los valores de una matriz dada y
#poder operar con sus valores sin inconvenientes 
def copia(A):
	Copia = []
	for i in range(len(A)):
		temp = []
		for j in range(len(A)):
			temp.append(A[i][j])
		Copia.append(temp)
	return Copia


#Produce el intercambio de filas 
#Se usa para la eliminacion gaussiana
def intercambio(A, i, j):
	temp = A[i]
	A[i] = A[j]
	A[j] = temp


#Se usa para la eliminacion gaussiana
def sustitucion_progresiva(A, I):
	n = len(A[0])
	m = len(A)

	for i in range(m):
		if A[i][i] == 0:
			if i != m-1:
				intercambio(A, i , i+1)
				intercambio(I, i , i+1)
			else:
				intercambio(A, i, 0)
				intercambio(I, i, 0)

	for j in range(n-1):
		for i in range(j+1, m):
			if A[i][j] != 0:
				proporcion = (-1) * (A[j][j] / A[i][j])
				for p in range(n):
					A[i][p] *=  proporcion
					A[i][p] += A[j][p]
					
					I[i][p] *=  proporcion
					I[i][p] += I[j][p]

	return A


#Se usa para la eliminacion gaussiana
def sustitucion_regresiva(A, I):
	n = len(A[0])
	m = len(A)

	for j in range(n-1, 0, -1):
		for i in range(j, -1, -1):
			if A[i][j] != 0:
				proporcion = (-1) * (A[j][j] / A[i][j])
				for p in range(n-1, -1, -1):
					A[i][p] *=  proporcion
					A[i][p] += A[j][p]
					
					I[i][p] *=  proporcion
					I[i][p] += I[j][p]

	return A


#Se usa para obtener la inversa de una matriz
def Eliminacion_Gaussiana(Matriz):
	A = copia(Matriz)
	I = identidad(len(A))
	
	A = sustitucion_progresiva(A, I)
	
	A = sustitucion_regresiva(A, I)
	
	n = len(A[0])
	m = len(A)

	for i in range(n):
		if A[i][i] != 0:
			proporcion = 1/A[i][i]
			for k in range(n):
				A[i][k] *= proporcion
				I[i][k] *= proporcion
	
	return (A, I)


#Generaa la matriz inversa de una matriz dada
def inversa(Matriz):
	A = copia(Matriz)
	Inversa = copia(A)
	Identidad = identidad(len(A))
	Inversa = Eliminacion_Gaussiana(A)[1]

	return Inversa


#Se usa para el metodo de las potencias
def multiplicacionDeMatrizPorVector(Matriz, B):

	A = copia(Matriz)	
	tam = len(A)
	Resultado = []

	for i in range(tam):
		subtotal = 0
		for j in range(tam):
			subtotal += (Decimal(A[i][j] * B[j]))
		Resultado.append( subtotal)

	return Resultado


#Se usa para calcular la norma 2 de una matriz
def multiplicacionDeMatrices(MatrizA, MatrizB):
	A = copia(MatrizA)
	B = copia(MatrizB)
	
	tam = len(A)
	Resultado = copia(A)

	for i in range(tam):
		for j in range(tam):
			subtotal = 0
			for t in range(tam):
				subtotal += (A[i][t] * B[t][j])
			Resultado[i][j] = subtotal

	return Resultado


#Se usa para calcular la norma 2 de una matriz
def transpuesta(Matriz):
	A = copia(Matriz)
	tam = len(A)

	T = []
	for k in range(tam):
		T.append(A[k][:])

	for i in range(tam):
		for j in range(tam):
			if  i < j:
				(T[i][j], T[j][i]) = (T[j][i], T[i][j])
		
	return T


#Se usa para calcular la norma 1 y la norma infinito
def sumatoria(A, indice, modo,  n):
	suma = 0
	if modo == "j":
		for i in range(n):
			suma += abs(A[i][indice])
		return suma
	elif modo == "i":
		for j in range(n):
			suma += abs(A[indice][j])
		return suma


#Para calcular el eigenvalue mas grande de una matriz y de ese modo calcular la norma 2 de dicha matriz
def metodo_de_las_potencias(Matriz):
	A = copia(Matriz)
	v = [Decimal(1)]
	for k in range(len(A)-1):
		v.append(Decimal(0))

	Akv = v[0]
	v = multiplicacionDeMatrizPorVector(A, v)
	Ak1v = v[0]
	actual = Decimal(Ak1v) / Decimal(Akv)

	for k in range(1000):
		Akv = Ak1v
		v = multiplicacionDeMatrizPorVector(A, v)
		Ak1v = v[0]

		anterior = actual
		actual = Decimal(Ak1v) / Decimal(Akv)

		if abs(anterior - actual ) < Decimal(1e-50):
			break

	return actual


def norma_1(A):
	filas = len(A)
	columnas = len(A[0])

	Lista = []

	for j in range(columnas):
		elemento = sumatoria(A, j, "j", filas)
		Lista.append(elemento)

	return max(Lista)


def norma_2 (Matriz):
	A = copia(Matriz)
	filas = len(A)
	columnas = len(A[0])

	At = transpuesta(A)

	MatrizResultado = multiplicacionDeMatrices(At, A)
	maximoEigenValue = metodo_de_las_potencias(MatrizResultado)

	return sqrt(maximoEigenValue)


def norma_infinito(A):
	filas = len(A)
	columnas = len(A[0])

	Lista = []

	for i in range(filas):
		elemento = sumatoria(A, i, "i", columnas)
		Lista.append(elemento)
	return max(Lista)


#Obtiene el numero de condicionamiento con la norma que se haya elegido de una matriz dada 
def Numero_de_condicionamiento(A, n):
	if n == 1: 
		Resultado = norma_1(A)*norma_1(inversa(A))
	elif n == 2:
		Resultado = norma_2(A)*norma_2(inversa(A))		
	elif n == 3:
		Resultado = norma_infinito(A)*norma_infinito(inversa(A))		

	return Resultado



#### Ingreso de datos

print("\n1-. Matriz de Hilbert ")
print("2-. Matriz de Vandermonde ")
print("3-. Matriz personalizada ") #El usuario puede ingresar cualquier matriz 

opcion = int(input("\nIngrese una opcion: "))

if opcion == 1:
	n = int(input("Ingrese el tamanio de la Matriz de Hilbert: ")) 
	A = hilbert(n) #genera una matriz de Hilbert de n x n

elif opcion ==2:
	vector = input("Ingrese el vector: ")
	Vector = vector.split()
	A = vandermonde(Vector, len(Vector)) #genera una matriz de Vandermonde con el vector ingresado

elif opcion == 3:
	n_columnas = int(input("Ingrese la cantidad de columnas de la matriz : "))
	n_filas = int(input("Ingrese la cantidad de filas de la matriz : "))
	print("Ingrese los datos de la Matriz: ")

	#ingresa datos personalizados
	A = []
	for k in range(n_filas):
		A.append([])
		fila = input()
		elementos_fila = fila.split()
		for p in range(n_columnas):
			A[k].append(float(elementos_fila[p]))

print("\nNumero de condicionamiento: ")
print("1- Usar Norma 1")
print("2- Usar Norma 2")
print("3- Usar Norma infinito")

opcion = int(input("\nIngrese una opcion:  ")) #elige una norma para el numero de condicionamiento

Resultado = Numero_de_condicionamiento(A, opcion)

print("Resultado: ", Resultado)