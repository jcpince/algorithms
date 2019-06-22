#  S = 1 + 2 + ... + n-1 + n
#  S = n + n-1 +... + 2 + 1
# 2S = n+1 + n+1 + ... + n+1 + n+1 = n*(n+1)
# S = n*(n+1)/2

# S = 1^2 + 2^2 + ... + (n-1)^2 + n^2
# Sum of first squares = n^3/3 + n^2/2 + n/6

def euler6(n):
    sumnat = n*(n+1)/2
    sumsq  = n**3/3 + n**2/2 + n/6
    return sumnat**2 - sumsq

t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    print(euler6(n))
