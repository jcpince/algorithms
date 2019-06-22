#include <iostream>

using namespace std;

long long sum_even_fibonacci(long long max_fibo_term) {

  long long last2[2] = {1, 2};
  int index = 0;
  long long fibo = 3, sum = 2;

  while(fibo < max_fibo_term) {
    if ((fibo & 0x1) == 0) sum += fibo;
    last2[index & 0x1] = fibo;
    index = !index;
    fibo = last2[0] + last2[1];
  }
  return sum;
}

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        long n;
        cin >> n;
        cout << sum_even_fibonacci(n) << endl;
    }
    return 0;
}
