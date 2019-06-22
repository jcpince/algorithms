#!/usr/bin/python3
import time
from math import sqrt

count3 = 0
count5 = 0
count7 = 0

def get_primes_below_N_index(primes, primes_sum, N):
    global count3, count5, count7
    if N < primes[-1]:
        for index in range(0, len(primes)):
            if primes[index] >= N:
                return index-2 # -2 because we start from index 2
    candidate = primes[-1]
    while primes[-1] < N:
        candidate += 2
        s = int(sqrt(candidate))
        #print("candidate = %d, primes = %s" % (candidate, primes))
        for p in primes[1:]:
            if p > s:
                primes.append(candidate)
                primes_sums.append(primes_sums[-1] + candidate)
                break
            if (candidate % p) == 0:
                break
    return len(primes)-2  # -2 because we start from index 2

start = time.time()
primes = [2, 3, 5, 7, 11]
primes_sums = [2, 5, 10, 17, 28]
t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    index = get_primes_below_N_index(primes, primes_sums, n)
    #print(index, primes_sums[0:index+1])
    print(primes_sums[index])
print("Computation time: %f seconds" % (time.time() - start))
