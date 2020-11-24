import numpy


def gaussian_elimination(A: numpy.array, b: numpy.array) -> numpy.array:
    n = len(A)
    A, b = numpy.asarray(A, dtype=numpy.float64), numpy.asarray(b, dtype=numpy.float64)
    Ab = numpy.asarray(numpy.c_[A, b], dtype=numpy.float64)

    for k in range(n):
        for i in range(k + 1, n):
            if abs(Ab[i][k]) > abs(Ab[k][k]):
                Ab[[k, i]] = Ab[[i, k]]
            else:
                pass

        for j in range(k + 1, n):
            q = float(Ab[j][k]) / Ab[k][k]
            for m in range(k, n + 1):
                Ab[j][m] -= q * Ab[k][m]

    x = numpy.zeros(n)

    x[n - 1] = float(Ab[n - 1][n]) / Ab[n - 1][n - 1]
    for i in range(n - 1, -1, -1):
        z = 0.0
        for j in range(i + 1, n):
            z = z + float(Ab[i][j]) * x[j]
        x[i] = float(Ab[i][n] - z) / Ab[i][i]
    return x


def vandermonde_matrix(X) -> numpy.array:
    n = len(X)
    V = numpy.zeros((n, n))
    for i in range(n):
        for j in range(n):
            V[i][j] = X[i] ** j
    return V


def hilbert_matrix(n, m) -> numpy.array:
    H = numpy.zeros((n, m))
    for i in range(n):
        for j in range(m):
            H[i][j] = 1 / (i + 1 + j)
    return H


# datos
X = [1, 4, 2, 7]
y = [10, 40, 20, 70]

# se crea la matriz de vandermonde a partir de X
V = vandermonde_matrix(X)

# se resuelve para x en Vx=y, x son los coeficientes del polinomio
x = gaussian_elimination(V, y)

print("Aproximacion polinomial", x)

# Creacion de la matrix de hilbert
H = hilbert_matrix(5, 5)
print("Matrix de hilbert", H)
