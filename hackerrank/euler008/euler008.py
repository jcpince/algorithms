#!/bin/python3

import sys

def prodk(digits):
    prod = 1
    for d in digits:
        prod *= int(d)
    print("%s => %d" % (digits, prod))
    return prod

t = int(input().strip())
for a0 in range(t):
    n,k = input().strip().split(' ')
    n,k = [int(n),int(k)]
    num = input().strip()
    #print("Looking for maxprod of %d digits in %s" % (k, num))
    maxprod  = prodk(num[0:k])
    origin = 1
    end = k+1
    prod = maxprod
    while(end <= n):
        if '0' == num[end-1]:
            origin += k
            end += k
            prod = 0
            continue
        if prod == 0:
            prod = prodk(num[origin:end])
            maxprod = max(prod, maxprod)
            origin += 1
            end += 1
            continue
        prod /= int(num[origin-1])
        prod *= int(num[end-1])
        print("%s => %d" % (num[origin:end], prod))
        maxprod = max(prod, maxprod)
        origin += 1
        end += 1
    print(int(maxprod))
