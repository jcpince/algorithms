#!/bin/python3

import sys
import math

def is_pythagorean_triplet(a, b, c):
    return a**2 + b**2 == c**2

def get_c(a, b):
    c = math.sqrt(a**2 + b**2)
    if c == int(c):
        return int(c)
    return -1

pythagoreans = {}
t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    if n < 12:
        print(-1)
        continue
    a = 1
    b = 1
    maxprod = -1
    while a+b+math.sqrt(a**2+b**2) <= n:
        while a+b+math.sqrt(a**2+b**2) <= n:
            b += 1
            #print("Check %d + %d" % (a, b))
            c = get_c(a,b)
            if c == -1:
                continue
            if (pythagoreans.setdefault(a+b+c, -1) < a*b*c):
                #print("{%d: %d}," % (a+b+c, a*b*c))
                pythagoreans[a+b+c] = a*b*c
            if a+b+c == n:
                maxprod = max(maxprod, a*b*c)
            elif a+b+c > n:
                break
        a += 1
        b = a
    print(maxprod)
    print(pythagoreans)
