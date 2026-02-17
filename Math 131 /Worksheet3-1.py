import numpy as np

def backwardSubstitution(U, b):
    n = U.shape[0]
    x = np.zeros(n)

    for i in range(n - 1, -1, -1):
        x[i] = (b[i] - np.dot(U[i, i+1:], x[i+1:])) / U[i, i]
    
    return x

U = np.array([
    [2, 1, 0, 5],
    [0, 3, 1, 1],
    [0, 0, -3, -10],
    [0, 0, 0, 4]
], dtype=float)

b = np.array([1, 1, 2, -8], dtype=float)

x = backwardSubstitution(U, b)
print("Solution:", x)
