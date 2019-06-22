#!/bin/python3
import time
from math import sqrt

count3 = 0
count5 = 0
count7 = 0

def get_prime(primes, N):
    global count3, count5, count7
    if N < len(primes):
        return primes[N-1]
    candidate = primes[-1]
    while len(primes) != N:
        candidate += 2
        count3 += 1
        count5 += 1
        count7 += 1
        if count3 == 2:
             #print("count3 = %d -- candidate = %d" % (count3, candidate))
             count3 = 0
             count5 += 1
             count7 += 1
             candidate += 2
             if candidate % 5 == 0: #count5 == 5:
                 #print("count5 = %d -- candidate = %d" % (count5, candidate))
                 count5 = 0
                 count3 += 1
                 count7 += 1
                 candidate += 2
             if candidate % 7 == 0: #count7 == 6:
                 #print("count7 = %d -- candidate = %d" % (count7, candidate))
                 count7 = 0
                 count3 += 1
                 count5 += 1
                 candidate += 2
        elif candidate % 5 == 0: #count5 == 5:
            #print("count5 = %d -- candidate = %d" % (count5, candidate))
            count5 = 0
            count3 += 1
            count7 += 1
            candidate += 2
            if candidate % 7 == 0: #count7 == 6:
                #print("count7 = %d -- candidate = %d" % (count7, candidate))
                count7 = 0
                count3 += 1
                count5 += 1
                candidate += 2
        elif candidate % 7 == 0: #count7 == 6:
            #print("count7 = %d -- candidate = %d" % (count7, candidate))
            count7 = 0
            count3 += 1
            count5 += 1
            candidate += 2
        s = int(sqrt(candidate))
        #print("candidate = %d, primes = %s" % (candidate, primes))
        for p in primes[1:]:
            if p > s:
                primes.append(candidate)
                break
            if (candidate % p) == 0:
                break
    return primes[-1]

start = time.time()
primes = [2, 3, 5, 7, 11]
t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    print(get_prime(primes, n))
assert(get_prime(primes, 168) == 997)
assert(get_prime(primes, 10000) == 104729)
print("Computation time: %f seconds" % (time.time() - start))
#print(primes)
