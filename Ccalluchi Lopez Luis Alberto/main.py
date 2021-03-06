# -*- coding: utf-8 -*-
"""main.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1_PsdM1pi5DxgUAOWo89NUjZJBX44EIGQ
"""

import numpy as np
from math import sqrt
from numpy import linalg as LA

def vandermonde(input_vector, N, increasing=False):  
    if not increasing:
        output_matrix = np.array([x**(N-1-i) for x in input_vector for i in range(N)]).reshape(input_vector.size,N)
        
    elif increasing:
         output_matrix = np.array([x**i for x in input_vector for i in range(N)]).reshape(input_vector.size,N)
    
    return output_matrix

def hilbert(n):
    x = np.arange(1, n+1) + np.arange(0, n)[:, np.newaxis]
    return 1.0/x
  
def frobeniusNorm(input_vector): 
    sumSq = 0
    for col in input_vector: 
        for fila in col: 
            sumSq += pow(fila, 2) 
    res = sqrt(sumSq) 
    return round(res, 5) 

print("Coloca el numero de filas y columnas:")
no_of_col = int(input())
input_vector = np.random.randint(1, 10, size=(n)) # generar un vector aleatorio de n

no_of_col
output_matrixVander_dec_order = vandermonde(input_vector,no_of_col,False)
output_matrixVAnder_inc_order = vandermonde(input_vector,no_of_col,True)
output_matrix_hilbert = hilbert(no_of_col)
#
print("Nuestro arreglo es:",input_vector,"\n")
print("El numero de columnas y filas es :",no_of_col,"\n")
print("Matriz de vandermonde:\n\n",output_matrixVander_dec_order,"\n")
print("Matriz de vandermonde inversa:\n\n",output_matrixVAnder_inc_order,"\n \n")
print("Matriz de hilbert:\n\n",output_matrix_hilbert,"\n \n")
print("Numero de condicionamiento Hilbert", LA.cond(output_matrix_hilbert),"\n")
print("Numero de condicionamiento vandermonde", LA.cond(output_matrixVander_dec_order),"\n")
print("Norma frobenius para matriz de hilbert: \n\n", frobeniusNorm(output_matrix_hilbert),"\n \n")
print("Norma frobenius para matriz de vandermonde: \n\n", frobeniusNorm(output_matrixVander_dec_order),"\n \n")
