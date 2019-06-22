#!/usr/bin/python3
import time
import array
from math import sqrt

primes = bytearray(1000000)
primes_sums = array.array('L', bytearray(8000000))
primes_sums[2] = 2
# print(len(primes))
# print(len(primes_sums))

def get_primes_below_N(N):
    global primes
    for i in range(3, int(sqrt(N))+1, 2):
        if primes[i] == 0:
            j = i**2
            while j < N:
                primes[j] = 1
                j += i

def get_primes_sums():
    global primes, primes_sums
    primes_sum = 2
    for i in range(3, len(primes), 2):
        if primes[i] == 0:
            primes_sum += i
        primes_sums[i] = primes_sum

start = time.time()
get_primes_below_N(1000000)
get_primes_sums()
#print("Computation time: %f seconds" % (time.time() - start))

# print(primes_sums[0:20])
# print(primes_sums[2])
# print(primes_sums[9])

t = int(input().strip())
start = time.time()
for _ in range(t):
    n = int(input().strip())
    if n&0x1 == 0x0 and n != 2:
        n -= 1
    #print("%d => %d" % (n, primes_sums[n]))
    print(primes_sums[n])



# Input: an integer n > 1.
#
#  Let A be an array of Boolean values, indexed by integers 2 to n,
#  initially all set to true.
#
#  for i = 2, 3, 4, ..., not exceeding √n:
#    if A[i] is true:
#      for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding n:
#        A[j] := false.
#
#  Output: all i such that A[i] is true.
