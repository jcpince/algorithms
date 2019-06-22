#include <stdio.h>

static long long FIBO_NUMBERS[] = {2, 8, 34, 144, 610, 2584, 10946, 46368,
  196418, 832040, 3524578, 14930352, 63245986, 267914296, 1134903170,
  4807526976, 20365011074, 86267571272, 365435296162, 1548008755920,
  6557470319842, 27777890035288, 117669030460994, 498454011879264,
  2111485077978050, 8944394323791464, 37889062373143906, -1 };

long long sum_even_fibonacci(long long max_fibo_term) {

  long long sum = 0, *fibo = &FIBO_NUMBERS[0];
  int index = 0;

  while(*fibo < max_fibo_term && *fibo != -1)
    sum += *fibo++;
  return sum;
}

int main(int argc, char **argv) {
  int T;
  scanf("%d", &T);
  while (T--) {
    long long max_fibo_term;
    scanf("%lld", &max_fibo_term);
    printf("%lld\n", sum_even_fibonacci(max_fibo_term));
  }
  return 0;
}
