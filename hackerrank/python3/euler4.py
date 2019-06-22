from math import sqrt

def flip3bytes(w):
    unit = w % 10
    deci = int(w % 100 / 10)
    mill = int((w - 10 * deci - unit) / 100)
    #print("flip of", w, 'is', mill + 10 * deci + unit * 100)
    return mill + 10 * deci + unit * 100

def get_palindrom(n):
    assert(n > 101101)
    assert(n < 1000000)
    n -= 1;
    upper = int(n / 1000);
    lower = n % 1000;
    upperflip = flip3bytes(upper);
    #print(upper, lower, upperflip)

    if upperflip > lower:
        upper -= 1
        upperflip = flip3bytes(upper);

    return upper*1000 + upperflip;

def satisfy_condition(n):
    sqrtn = int(sqrt(n))
    loops = 0
    for div in range(100, sqrtn):
        loops += 1
        if n % div == 0 and n / div < 1000:
            #print(div, 'found in ', loops, 'loops')
            return True
    return False

def satisfy_condition2(n):
    sqrtn = int(sqrt(n))
    if sqrtn - 100 > 999 - sqrtn:
        # scan the upper range
        lower = sqrtn
        upper = 1000
    else:
        # scan the upper range
        lower = 100
        upper = sqrtn+1
    loops = 0
    for div in range(lower, upper):
        loops += 1
        if n % div == 0 and n / div < 1000:
            #print(div, 'found in ', loops, 'loops')
            return True
    return False

import subprocess
for n0 in range(101102, 1000000):
    n = get_palindrom(n0)
    while not satisfy_condition2(n):
        n = get_palindrom(n)
    output = int(subprocess.Popen(["../C++/euler4.x", str(n0)], stdout=subprocess.PIPE).communicate()[0])
    if output != n:
        print('Input:', n0)
        print('Python:', n)
        print('C++:', output)
    assert(output == n)
print("Sanity test succeeded")

t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    n = get_palindrom(n)
    while not satisfy_condition2(n):
        n = get_palindrom(n)
    print(n)
