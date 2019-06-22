def sum_even_fibonacci(max_fibo_term):
    last2 = [1, 2]
    index = 0
    fibo = 3
    evensum = 2

    while fibo < max_fibo_term:
        if (fibo & 0x1) == 0:
            evensum += fibo
        last2[index & 0x1] = fibo
        index = ~index
        fibo = last2[0] + last2[1];
    return evensum

for i in range(int(input())):
    n = int(input())
    print(sum_even_fibonacci(n))
