import numpy as np

def backwardSubstitution(U, b):
    n = U.shape[0]
    x = np.zeros(n)

    for i in range(n - 1, -1, -1):
        x[i] = (b[i] - np.dot(U[i, i+1:], x[i+1:])) / U[i, i]
    
    return x

def gaussianElimination(A, b):
    A = A.astype(float)
    b = b.astype(float)
    n = A.shape[0]
    
    # forward elimination
    for k in range(n-1):
        for i in range(k+1, n):
            m = A[i, k] / A[k, k]
            A[i, k:] = A[i, k:] - m * A[k, k:]
            b[i] = b[i] - m * b[k]

    return backwardSubstitution(A, b)


A = np.array([
    [1, -2, 1],
    [3, 0, 1],
    [2, -2, 1], #stop removing      
], dtype=float)

b = np.array([2, 0, 1], dtype=float)

x = gaussianElimination(A, b)
print("Solution:", x)
