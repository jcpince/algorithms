#!/bin/python3
import time

primes = [2, 3]
non_primes = [9]

def get_prime(N):
    global primes, non_primes
    candidate = primes[-1] + 2
    if N < len(primes):
        return primes[N-1]
    while len(primes) != N:
        if candidate in non_primes:
            for p in primes[1:]:
                non_primes.append(p*candidate)
            for np in non_primes:
                if np > candidate:
                    break
                non_primes.remove(np)
        else:
            for p in primes[1:]:
                non_primes.append(p*candidate)
            non_primes.append(candidate**2)
            non_primes.sort()
            primes.append(candidate)
            for np in non_primes:
                if np > candidate:
                    break
                non_primes.remove(np)
        candidate += 2
    return primes[-1]

start = time.time()
t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    print(get_prime(n))
print("min(non_primes) = %d" % min(non_primes))
assert(get_prime(168) == 997)
print("Computation time: %f seconds" % (time.time() - start))
#print(primes)
