#include <iostream>

using namespace std;

long long sum_n_multiples(long long a, long long d, long long n) {
  /* sum up n times counting a even if 0
    right shift by 1 instead of dividing by 2 because
    python will approximate the division
  */
  return (n * ((a << 1) + (n - 1) * d)) >> 1;
}

long long sum_35_multiples(long long N) {
  /* d + 2d + ... + kd for k = (n - (n % d)) / d
    k/2 * (k - 1) * d
  */
  N -= 1;
  long long k3  = ((N - (N %  3)) /  3) + 1; // +1 to count 0
  long long k5  = ((N - (N %  5)) /  5) + 1; // +1 to count 0
  long long k15 = ((N - (N % 15)) / 15) + 1; // +1 to count 0
  return sum_n_multiples(0, 3, k3) + sum_n_multiples(0, 5, k5) - sum_n_multiples(0, 15, k15);
}

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        long n;
        cin >> n;
        cout << sum_35_multiples(n) << endl;
    }
    return 0;
}
