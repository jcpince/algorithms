def sum_n_multiples(a, d, n):
    # sum up n times counting a even if 0
    # right shift by 1 instead of dividing by 2 because
    # python will approximate the division
    return int((n * (2 * a + (n - 1) * d))) >> 1

def sum_35_multiples(N):
    # d + 2d + ... + kd for k = (n - (n % d)) / d
    # k/2 * (k - 1) * d
    N -= 1
    k3 = int((N - (N % 3)) / 3) + 1 # +1 to count 0
    k5 = int((N - (N % 5)) / 5) + 1 # +1 to count 0
    k15 = int((N - (N % 15)) / 15) + 1 # +1 to count 0
    return sum_n_multiples(0, 3, k3) + sum_n_multiples(0, 5, k5) - sum_n_multiples(0, 15, k15)

t = int(input().strip())
ns = list()
for a0 in range(t):
    ns.append(int(input().strip()))

for n in ns:
    print(sum_35_multiples(n))
