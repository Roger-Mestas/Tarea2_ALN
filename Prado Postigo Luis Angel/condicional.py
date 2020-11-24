import numpy

matrix = numpy.array([[4, 2, 8], [3, 1, 5], [1, 5, 6]])

# usando la norma 2
result = numpy.linalg.cond(matrix)
print(result)

# usando la norma 1
result = numpy.linalg.cond(matrix,1)
print(result)

# usando la norma infinita
result = numpy.linalg.cond(matrix,numpy.inf)
print(result)
