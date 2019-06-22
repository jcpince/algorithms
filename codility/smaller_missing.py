#! /usr/bin/python3
from random import randint

def solution(A):
    # write your code in Python 3.6
    # filter <= 0 first? might depend on the data
    A.sort()
    expected = 1
    for e in A:
        if e < expected:
            continue
        if e != expected:
            break
        expected = e+1
    return expected


def check_solution():
    A = [1,3,6,4,1,2]
    assert(solution(A) == 5)

    A = [1,3,2]
    assert(solution(A) == 4)

    A = [-1,-2]
    assert(solution(A) == 1)

    A = [randint(-100, 100) for _ in range(100000)]
    print("solution(A) is ", solution(A))

    print("All tests passed!")

check_solution()
