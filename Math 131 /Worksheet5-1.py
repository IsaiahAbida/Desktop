import numpy as np
import time

def forwardEliminateLoops(A, b):
    n = A.shape[0]
    A = A.copy()
    b = b.copy()
    for k in range(n-1):
        for i in range(k+1, n):
            r = A[i,k] / A[k,k]
            for j in range(k+1, n):
                A[i,j] -= r * A[k,j]
            b[i] -= r * b[k]
    return A, b

def forwardEliminateVectorized(A, b):
    n = A.shape[0]
    A = A.copy()
    b = b.copy()
    for k in range(n-1):
        r = A[k+1:, k] / A[k, k]
        A[k+1:, k+1:] -= np.outer(r, A[k, k+1:])
        b[k+1:] -= r * b[k]
    return A, b

# test matrices
n = 1000
np.random.seed(0)
A = np.tril(np.random.rand(n, n)) + np.eye(n) 
b = np.random.rand(n)

# benchmark
start = time.time()
forwardEliminateLoops(A, b)
t1 = time.time() - start

start = time.time()
forwardEliminateVectorized(A, b)
t2 = time.time() - start

print(f"Three-loop time:     {t1:.3f} s")
print(f"Full vectorized time:{t2:.3f} s")
print(f"Speedup (Vectorized vs 3-loop): {t1/t2:.2f}x faster")
