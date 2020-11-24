import numpy as np
from math import factorial
from numpy.core.numeric import (asarray, empty, promote_types,multiply)
from numpy import linalg as LA

def hilbert(n, m=0):
    if n == 1 and (m == 0 or m == 1):
        return np.array([[1]])
    elif m == 0:
        m = n

    v = np.arange(1, n + 1) + np.arange(0, m)[:, np.newaxis]
    return 1. / v


def vandermonde(x, N=None, increasing=False):
    x = asarray(x)
    if N is None:
        N = len(x)

    v = empty((len(x), N), dtype=promote_types(x.dtype, int))
    tmp = v[:, ::-1] if not increasing else v

    if N > 0:
        tmp[:, 0] = 1
    if N > 1:
        tmp[:, 1:] = x[:, None]
        multiply.accumulate(tmp[:, 1:], out=tmp[:, 1:], axis=1)

    return v


a = np.array([[1, 0, -1], [0, 1, 0], [1, 0, 1]])
#Numero de Condicionamiento
print(LA.cond(a))

x = np.array([1,2,3,5])
print(vandermonde(x, 3))
#print(hilbert(2,2))
