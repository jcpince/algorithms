#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'getTotalX' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER_ARRAY a
#  2. INTEGER_ARRAY b
#
def isCommonFactor(b, num):
    for e in b:
        if (e % num) != 0:
            return False
    return True

def isCommonMultiple(a, num):
    for e in a:
        if (num % e) != 0:
            return False
    return True

debug = False

def debug_print(*args):
    global debug
    if debug:
        for arg in args:
            sys.stdout.write(str(arg))
            sys.stdout.write(' ')
        sys.stdout.write('\n')

def findMultiplesFactors(a, b):
    ismultiple = (b % a) == 0
    result = []
    if not ismultiple:
        return result
    result.append(a)
    multiple = 1
    while a * multiple < b:
        multiple += 1
        if multiple * a == b:
            break
        ismultiple = ((b % (a * multiple)) == 0) 
        if ismultiple:
            debug_print("adds", a * multiple)
            result.append(a * multiple)
        else:
            debug_print("skips", a * multiple)
    return result + [b]

def findMultiplesFactors2(a, b):
    result = []
    tmp = b // a
    if a * tmp != b:
        return []
    max_multiple = (b + a) // 2
    result.append(a)
    multiple = 1
    a_mult = a
    while a_mult < max_multiple:
        multiple += 1
        a_mult = a * multiple
        tmp = b // a_mult
        if a_mult == b or a_mult * tmp != b:
            debug_print("skips", a_mult)
            continue 
        debug_print("adds", a_mult)
        result.append(a_mult)
    result.append(b)
    return sorted(result)

if debug:
    for a in range(1, 200):
        for b in range(a, 200):
            ref = findMultiplesFactors(a, b)
            cand = findMultiplesFactors2(a, b)
            if ref != cand:
                print('findMultiplesFactors(%d, %d) returned %s' % (a, b, ref))
                print('findMultiplesFactors2(%d, %d) returned %s' % (a, b, cand))
                assert(False)

def getTotalX(a, b):
    a.sort()
    b.sort()
    if a[-1] > b[0]:
        # No solution here
        return 0
    elif a[-1] == b[0]:
        # only possible solution is b[0]
        if isCommonFactor(b, b[0]) and isCommonMultiple(a, b[0]):
            return 1
        return 0
    # Find the possible solutions
    solutions = 0
    mults = findMultiplesFactors2(a[-1], b[0])
    for mult in mults:
        if isCommonFactor(b, mult) and isCommonMultiple(a, mult):
            solutions += 1
    return solutions


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    m = int(first_multiple_input[1])

    arr = list(map(int, input().rstrip().split()))

    brr = list(map(int, input().rstrip().split()))

    total = getTotalX(arr, brr)

    fptr.write(str(total) + '\n')

    fptr.close()
