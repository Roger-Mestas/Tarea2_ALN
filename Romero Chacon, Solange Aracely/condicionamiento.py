import numpy as np
from numpy.core import (
    array, asarray, empty, single, double, csingle, cdouble, 
    inexact, complexfloating, all, Inf, dot, add, sqrt, sum,
    errstate, geterrobj, moveaxis, amin, amax, product, abs,
    atleast_2d, intp, asanyarray, object_, matmul,
    swapaxes, divide, isnan, sign, argsort, sort
)
from numpy.linalg import lapack_lite, _umath_linalg
from numpy.core.multiarray import normalize_axis_index

_complex_types_map = {single : csingle,
                      double : cdouble,
                      csingle : csingle,
                      cdouble : cdouble}

def NuevaMatriz(f,c):
    matriz=[]
    for i in range(f):
        matriz.append([0]*c)
    return matriz

def LLmatriz():
    f = int(input("Numero de filas: "))
    c = int(input("Numero de columnas: "))
    matriz=NuevaMatriz(f,c)
    for i in range (f):
        for j in range(c):
            matriz[i][j]=float(input("Elemento: "))
    return matriz

def mostrar(M,f,c):
    for i in range (f):
        for j in range (c):
            print(M[i][j], end="\t")
        print()

def hilb():
    n = int (input("N: "))
    matrizH = NuevaMatriz(n,n)
    for i in range (n):
        for j in range (n):
            matrizH[i][j] = 1/((i+1)+(j+1)-1)
    return matrizH

def vector(I, F=None, S=None):
  while True:
    if S > 0 and I > F:
      break
    elif S < 0 and I < F:
      break
    yield (I)
    I = I + S

def vander():
  i = float (input("Inicio: "))
  f = float (input("Final: "))
  s = float (input("Salto: "))
  V=list(vector(i, f, s))
  V = np.array(V)
  n = len(V)
  matrizV= NuevaMatriz(n,n)
  for i in range(n):
    for j in range(n):
      potencia = (n-1)-j
      matrizV[i][j] = V[i]**potencia
  return matrizV     

def _is_empty_2d(arr):
    return arr.size == 0 and product(arr.shape[-2:]) == 0

def _assert_stacked_2d(*arrays):
    for a in arrays:
        if a.ndim < 2:
            raise LinAlgError('%d-de la matriz dimensional dada. La matriz debe ser '
                    'al menos dos dimensiones' % a.ndim)

def _assert_stacked_square(*arrays):
    for a in arrays:
        m, n = a.shape[-2:]
        if m != n:
            raise LinAlgError('Las últimas 2 dimensiones de la matriz deben ser cuadradas')

def _commonType(*arrays):
    result_type = single
    is_complex = False
    for a in arrays:
        if issubclass(a.dtype.type, inexact):
            if isComplexType(a.dtype.type):
                is_complex = True
            rt = _realType(a.dtype.type, default=None)
            if rt is None:
                raise TypeError("Tipo de array %s no tiene apoyo en linalg" %
                        (a.dtype.name,))
        else:
            rt = double
        if rt is double:
            result_type = double
    if is_complex:
        t = cdouble
        result_type = _complex_types_map[result_type]
    else:
        t = double
    return t, result_type

def isComplexType(t):
    return issubclass(t, complexfloating)

def _realType(t, default=double):
    return _real_types_map.get(t, default)

def norm(x, ord=None, axis=None, keepdims=False):

    x = asarray(x)

    if not issubclass(x.dtype.type, (inexact, object_)):
        x = x.astype(float)

    if axis is None:
        ndim = x.ndim
        if ((ord is None) or
            (ord in ('f', 'fro') and ndim == 2) or
            (ord == 2 and ndim == 1)):

            x = x.ravel(order='K')
            if isComplexType(x.dtype.type):
                sqnorm = dot(x.real, x.real) + dot(x.imag, x.imag)
            else:
                sqnorm = dot(x, x)
            ret = sqrt(sqnorm)
            if keepdims:
                ret = ret.reshape(ndim*[1])
            return ret

    nd = x.ndim
    if axis is None:
        axis = tuple(range(nd))
    elif not isinstance(axis, tuple):
        try:
            axis = int(axis)
        except Exception as e:
            raise TypeError("'axis' debe ser None, un entero o una tupla de enteros") from e
        axis = (axis,)

    if len(axis) == 1:
        if ord == Inf:
            return abs(x).max(axis=axis, keepdims=keepdims)
        elif ord == -Inf:
            return abs(x).min(axis=axis, keepdims=keepdims)
        elif ord == 0:
            return (x != 0).astype(x.real.dtype).sum(axis=axis, keepdims=keepdims)
        elif ord == 1:
            return add.reduce(abs(x), axis=axis, keepdims=keepdims)
        elif ord is None or ord == 2:
            s = (x.conj() * x).real
            return sqrt(add.reduce(s, axis=axis, keepdims=keepdims))
        elif isinstance(ord, str):
            raise ValueError(f"Orden de norma inválida '{ord}' para los vectores")
        else:
            absx = abs(x)
            absx **= ord
            ret = add.reduce(absx, axis=axis, keepdims=keepdims)
            ret **= (1 / ord)
            return ret
    elif len(axis) == 2:
        row_axis, col_axis = axis
        row_axis = normalize_axis_index(row_axis, nd)
        col_axis = normalize_axis_index(col_axis, nd)
        if row_axis == col_axis:
            raise ValueError('Duplicado de los ejes dados.')
        if ord == 2:
            ret =  _multi_svd_norm(x, row_axis, col_axis, amax)
        elif ord == -2:
            ret = _multi_svd_norm(x, row_axis, col_axis, amin)
        elif ord == 1:
            if col_axis > row_axis:
                col_axis -= 1
            ret = add.reduce(abs(x), axis=row_axis).max(axis=col_axis)
        elif ord == Inf:
            if row_axis > col_axis:
                row_axis -= 1
            ret = add.reduce(abs(x), axis=col_axis).max(axis=row_axis)
        elif ord == -1:
            if col_axis > row_axis:
                col_axis -= 1
            ret = add.reduce(abs(x), axis=row_axis).min(axis=col_axis)
        elif ord == -Inf:
            if row_axis > col_axis:
                row_axis -= 1
            ret = add.reduce(abs(x), axis=col_axis).min(axis=row_axis)
        elif ord in [None, 'fro', 'f']:
            ret = sqrt(add.reduce((x.conj() * x).real, axis=axis))
        elif ord == 'nuc':
            ret = _multi_svd_norm(x, row_axis, col_axis, sum)
        else:
            raise ValueError("Orden normativo inválido para las matrices.")
        if keepdims:
            ret_shape = list(x.shape)
            ret_shape[axis[0]] = 1
            ret_shape[axis[1]] = 1
            ret = ret.reshape(ret_shape)
        return ret
    else:
        raise ValueError("Número inadecuado de dimensiones a la norma.")

def _multi_svd_norm(x, row_axis, col_axis, op):
    y = moveaxis(x, (row_axis, col_axis), (-2, -1))
    result = op(svd(y, compute_uv=False), axis=-1)
    return result

def eigvalsh(a, UPLO='L'):
    UPLO = UPLO.upper()
    if UPLO not in ('L', 'U'):
        raise ValueError("El argumento de UPLO debe ser 'L' o 'U'")

    extobj = get_linalg_error_extobj(
        _raise_linalgerror_eigenvalues_nonconvergence)
    if UPLO == 'L':
        gufunc = _umath_linalg.eigvalsh_lo
    else:
        gufunc = _umath_linalg.eigvalsh_up

    a, wrap = _makearray(a)
    _assert_stacked_2d(a)
    _assert_stacked_square(a)
    t, result_t = _commonType(a)
    signature = 'D->d' if isComplexType(t) else 'd->d'
    w = gufunc(a, signature=signature, extobj=extobj)
    return w.astype(_realType(result_t), copy=False)


class LinAlgError(Exception):
    """
    """

def _determine_error_states():
    errobj = geterrobj()
    bufsize = errobj[0]

    with errstate(invalid='call', over='ignore',
                  divide='ignore', under='ignore'):
        invalid_call_errmask = geterrobj()[1]

    return [bufsize, invalid_call_errmask, None]


_linalg_error_extobj = _determine_error_states()
del _determine_error_states

def _raise_linalgerror_singular(err, flag):
    raise LinAlgError("Matrix Singular")

def _raise_linalgerror_nonposdef(err, flag):
    raise LinAlgError("La matriz no es positiva definitiva")

def _raise_linalgerror_eigenvalues_nonconvergence(err, flag):
    raise LinAlgError("Los valores propios no convergieron")

def _raise_linalgerror_svd_nonconvergence(err, flag):
    raise LinAlgError("La SVD no convergió")

def _raise_linalgerror_lstsq(err, flag):
    raise LinAlgError("La SVD no convergió en los Cuadrados Mínimos Lineales")

def get_linalg_error_extobj(callback):
    extobj = list(_linalg_error_extobj) 
    extobj[2] = callback
    return extobj

def _makearray(a):
    new = asarray(a)
    wrap = getattr(a, "__array_prepare__", new.__array_wrap__)
    return new, wrap

_real_types_map = {single : single,
                   double : double,
                   csingle : single,
                   cdouble : double}

_complex_types_map = {single : csingle,
                      double : cdouble,
                      csingle : csingle,
                      cdouble : cdouble}

def _realType(t, default=double):
    return _real_types_map.get(t, default)

def _complexType(t, default=cdouble):
    return _complex_types_map.get(t, default)

def _linalgRealType(t):
    """Echa el tipo t a doble o cdoble."""
    return double

def _commonType(*arrays):
    result_type = single
    is_complex = False
    for a in arrays:
        if issubclass(a.dtype.type, inexact):
            if isComplexType(a.dtype.type):
                is_complex = True
            rt = _realType(a.dtype.type, default=None)
            if rt is None:
                raise TypeError("tipo de array %s no tiene apoyo en linalg" %
                        (a.dtype.name,))
        else:
            rt = double
        if rt is double:
            result_type = double
    if is_complex:
        t = cdouble
        result_type = _complex_types_map[result_type]
    else:
        t = double
    return t, result_type

def eigh(a, UPLO='L'):
    UPLO = UPLO.upper()
    if UPLO not in ('L', 'U'):
        raise ValueError("El argumento de UPLO debe ser 'L' o 'U'")

    a, wrap = _makearray(a)
    _assert_stacked_2d(a)
    _assert_stacked_square(a)
    t, result_t = _commonType(a)

    extobj = get_linalg_error_extobj(
        _raise_linalgerror_eigenvalues_nonconvergence)
    if UPLO == 'L':
        gufunc = _umath_linalg.eigh_lo
    else:
        gufunc = _umath_linalg.eigh_up

    signature = 'D->dD' if isComplexType(t) else 'd->dd'
    w, vt = gufunc(a, signature=signature, extobj=extobj)
    w = w.astype(_realType(result_t), copy=False)
    vt = vt.astype(result_t, copy=False)
    return w, wrap(vt)

def transpose(a):
    return swapaxes(a, -1, -2)

def svd(a, full_matrices=True, compute_uv=True, hermitian=False):
    import numpy as _nx
    a, wrap = _makearray(a)

    if hermitian:
        if compute_uv:
            s, u = eigh(a)
            sgn = sign(s)
            s = abs(s)
            sidx = argsort(s)[..., ::-1]
            sgn = _nx.take_along_axis(sgn, sidx, axis=-1)
            s = _nx.take_along_axis(s, sidx, axis=-1)
            u = _nx.take_along_axis(u, sidx[..., None, :], axis=-1)
            vt = transpose(u * sgn[..., None, :]).conjugate()
            return wrap(u), s, wrap(vt)
        else:
            s = eigvalsh(a)
            s = s[..., ::-1]
            s = abs(s)
            return sort(s)[..., ::-1]

    _assert_stacked_2d(a)
    t, result_t = _commonType(a)

    extobj = get_linalg_error_extobj(_raise_linalgerror_svd_nonconvergence)

    m, n = a.shape[-2:]
    if compute_uv:
        if full_matrices:
            if m < n:
                gufunc = _umath_linalg.svd_m_f
            else:
                gufunc = _umath_linalg.svd_n_f
        else:
            if m < n:
                gufunc = _umath_linalg.svd_m_s
            else:
                gufunc = _umath_linalg.svd_n_s

        signature = 'D->DdD' if isComplexType(t) else 'd->ddd'
        u, s, vh = gufunc(a, signature=signature, extobj=extobj)
        u = u.astype(result_t, copy=False)
        s = s.astype(_realType(result_t), copy=False)
        vh = vh.astype(result_t, copy=False)
        return wrap(u), s, wrap(vh)
    else:
        if m < n:
            gufunc = _umath_linalg.svd_m
        else:
            gufunc = _umath_linalg.svd_n

        signature = 'D->d' if isComplexType(t) else 'd->d'
        s = gufunc(a, signature=signature, extobj=extobj)
        s = s.astype(_realType(result_t), copy=False)
        return s

def cond(x, p=None):
    x = asarray(x)  
    if _is_empty_2d(x):
        raise LinAlgError("La condición no se define en las matrices vacías")
    if p is None or p == 2 or p == -2:
        s = svd(x, compute_uv=False)
        with errstate(all='ignore'):
            if p == -2:
                r = s[..., -1] / s[..., 0]
            else:
                r = s[..., 0] / s[..., -1]
    else:
        _assert_stacked_2d(x)
        _assert_stacked_square(x)
        t, result_t = _commonType(x)
        signature = 'D->D' if isComplexType(t) else 'd->d'
        with errstate(all='ignore'):
            invx = _umath_linalg.inv(x, signature=signature)
            r = norm(x, p, axis=(-2, -1)) * norm(invx, p, axis=(-2, -1))
        r = r.astype(result_t, copy=False)


    r = asarray(r)
    nan_mask = isnan(r)
    if nan_mask.any():
        nan_mask &= ~isnan(x).any(axis=(-2, -1))
        if r.ndim > 0:
            r[nan_mask] = Inf
        elif nan_mask:
            r[()] = Inf

    if r.ndim == 0:
        r = r[()]

    return r

def metodo(matriz):
    salir = False
    while not salir:
        print ("1. Num de condicionamiento de la norma 1")
        print ("2. Num de condicionamiento de la norma 2")
        print ("3. Num de condicionamiento de la norma inf")
        print ("4. Num de condicionamiento de la norma Frobenius")
        print ("5. Salir")
        opcion = int(input("Opcion: "))
        if opcion == 1:
            print(cond(matriz,1))
        elif opcion == 2:
            print(cond(matriz,2))
        elif opcion == 3:
            print(cond(matriz,np.Inf))
        elif opcion == 4:
            print(cond(matriz,'fro'))
        elif opcion == 5:
            salir = True
        else:
            print ("Introduce un numero entre 1 y 3")

salir = False
while not salir:
    print ("1. Usar matriz de Hilbert")
    print ("2. Usar matriz de Valdermonde")
    print ("3. Usar otra matriz")
    print ("4. Salir")
    opcion = int(input("Opcion: "))
    if opcion == 1:
        matriz=hilb()
        print("MATRIZ DE HILBERT")
        mostrar(matriz,len(matriz),len(matriz))
        metodo(matriz)
    elif opcion == 2:
        matriz=vander()
        print("MATRIZ DE VANDERMONDE")
        mostrar(matriz,len(matriz),len(matriz))
        metodo(matriz)
    elif opcion == 3:
        matriz=LLmatriz()
        print("MATRIZ")
        mostrar(matriz,len(matriz),len(matriz))
        metodo(matriz)
    elif opcion == 4:
        salir = True
    else:
        print ("Introduce un numero entre 1 y 3")