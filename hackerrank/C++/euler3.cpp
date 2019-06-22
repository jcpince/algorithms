#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#if defined(DBG)
#define dbg_print(fmt, ...) do { fprintf(stderr, fmt, __VA_ARGS__); } while (0)
#define info_print(fmt, ...) do { fprintf(stdout, fmt, __VA_ARGS__); } while (0)
#else
#define dbg_print(...)
#define info_print(...)
#endif

long largest_prime(long long n) {
  long long factor = 2;
  long long i, bound;

  dbg_print("Compute the largest prime of %lld\n", n);
  // Divide by two until it gets odd
  while ((n & 0x1) == 0) n = n >> 1;

  dbg_print("First pass done, compute the largest prime of %lld\n", n);
  bound = (long long)sqrt(n);
  for (i = 3 ; i <= bound ; i+=2) {
    while ((n % i) == 0) {
      n /= i;
      factor = i;
    }
    if (n == 1) break;
  }
  if (n > factor) factor = n;
  return factor;
}

int main() {
    int t;
    time_t begin,end; // time_t is a datatype to store time values.

    cin >> t;

    time (&begin); // note time before execution
    for(int a0 = 0; a0 < t; a0++){
        long n;
        cin >> n;
        cout << largest_prime(n) << endl;
    }
    time (&end); // note time after execution
    info_print("Terminated in %lf seconds.\n", 1000*difftime(end,begin));
    return 0;
}
