import numpy as np

def menu():
    opc=int(input("1)Vandermonde \n2)Hilbert\nopc: "))
    print(opc)
    N=int(input("Numero de fila y columna: "))
    if opc==1:
        vander(N)
    elif opc==2:
        hilbert(N)
        
def vander(N):
    x = np.array([1, 2, 3, 5])
    H = np.vander(x, N)
    operacion(H)
    
def hilbert(N):
    H = [[0]*N]*N
    for i in range(N):
        for j in range(N):
            H[i][j] = 1/(i+j+1)
    operacion(H)
    
def operacion(H):
    m = np.array(H)
    print(m)
    print("n:", np.linalg.cond(m))
    
    
menu()
