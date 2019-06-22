FIBO_NUMBERS = [2, 8, 34, 144, 610, 2584, 10946, 46368,
  196418, 832040, 3524578, 14930352, 63245986, 267914296, 1134903170,
  4807526976, 20365011074, 86267571272, 365435296162, 1548008755920,
  6557470319842, 27777890035288, 117669030460994, 498454011879264,
  2111485077978050, 8944394323791464, 37889062373143906 ]

def sum_even_fibonacci(max_fibo_term):
    evensum = 0
    index = 0

    while index < len(FIBO_NUMBERS) and FIBO_NUMBERS[index] < max_fibo_term:
        evensum += FIBO_NUMBERS[index]
        index += 1
    return evensum

for i in range(int(input())):
    n = int(input())
    print(sum_even_fibonacci(n))
