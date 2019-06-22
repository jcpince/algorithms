#!/bin/python3

import sys

def prodk(digits):
    prod = 1
    for d in digits:
        prod *= int(d)
    return prod

t = int(input().strip())
for a0 in range(t):
    n,k = input().strip().split(' ')
    n,k = [int(n),int(k)]
    num = input().strip()
    #print("Looking for maxprod of %d digits in %s" % (k, num))
    maxprod  = prodk(num[0:k])
    end = k+1
    while(end < n):
        maxprod = max(prodk(num[end-k:end]), maxprod)
        end += 1
    print(int(maxprod))
