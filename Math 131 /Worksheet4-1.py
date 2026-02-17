import numpy as np

def backwardSubstitution(U, b):
    n = U.shape[0]
    x = np.zeros(n)

    for i in range(n - 1, -1, -1):
        x[i] = (b[i] - np.dot(U[i, i+1:], x[i+1:])) / U[i, i]
    
    return x

 # part b
def GEPP(A, b):
    A = A.astype(float).copy()
    b = b.astype(float).copy()
    n = A.shape[0]

    for k in range(n-1):
        # find pivot row
        pivot = np.argmax(np.abs(A[k:n, k])) + k
        if A[pivot, k] == 0:
            raise ValueError("Matrix is singular!")

        # swap rows in A
        if pivot != k:
            A[[k, pivot]] = A[[pivot, k]]
            b[[k, pivot]] = b[[pivot, k]]

        # elimination
        for i in range(k+1, n):
            factor = A[i, k] / A[k, k]
            A[i, k:] -= factor * A[k, k:]
            b[i] -= factor * b[k]

    return A, b


# verifying solution from a
A = np.array([
    [2, 1, 0, 5],
    [0, 3, 1, 1],
    [-6, 3, -1, -23],
    [4, 5, 0, 9]
], dtype=float)

b = np.array([1, 1, 1, 1], dtype=float)

U, new_b = GEPP(A, b)

x = backwardSubstitution(U, new_b)
print("Solution from GEPP:", x)

# Verify with numpy
x_np = np.linalg.solve(A, b)
print("Solution from numpy:", x_np)
print("Error norm:", np.linalg.norm(x - x_np))

#-------------------------------------------------
# Part (c)
n = 500
np.random.seed(42)  # reproducibility
A_big = np.random.rand(n, n) * 10
b_big = np.random.rand(n)

U_big, b2_big = GEPP(A_big, b_big)
x_big = backwardSubstitution(U_big, b2_big)

# Verify with numpy
x_true = np.linalg.solve(A_big, b_big)
print("Error norm for 500x500:", np.linalg.norm(x_big - x_true))
