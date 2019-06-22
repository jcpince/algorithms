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

int inline flip3bytes(int w) {
  int unit = w % 10, deci = (w % 100) / 10;
  int mill = (w - 10 * deci - unit) / 100;
  return mill + 10 * deci + unit * 100;
}

int get_palindrom(int n) {
  int upper = --n / 1000;
  int lower = n % 1000;
  int upperflip = flip3bytes(upper);

  if (upperflip > lower)
      upperflip = flip3bytes(--upper);

  dbg_print("%d => %d\n", n, upper*1000 + upperflip);
  return upper*1000 + upperflip;
}

bool satisfy_condition2(int n) {
  int sqrtn = sqrt(n);
  int lower, upper;
  if (sqrtn - 100 > 999 - sqrtn) {
    lower = sqrtn;
    upper = 1000;
  } else {
    lower = 100;
    upper = sqrtn;
  }
  dbg_print("Check %d between %d and %d\n", n, lower, upper);
  for (int div = lower ; div <= upper ; div++) {
    if (((n % div) == 0) and ((n / div) < 1000)) {
      dbg_print("Returns %s\n", "true");
      return true;
    }
  }
  dbg_print("Returns %s\n", "false");
  return false;
}

int main(int argc, char **argv) {
    int t;
    time_t begin,end; // time_t is a datatype to store time values.

    if (argc == 2) {
      long n;
      sscanf(argv[1], "%ld", &n);
      do {
        n = get_palindrom(n);
      }
      while (!satisfy_condition2(n));
      cout << n << endl;
      return 0;
    }

    cin >> t;

    time (&begin); // note time before execution
    for(int a0 = 0; a0 < t; a0++){
        long n;
        cin >> n;
        do {
          n = get_palindrom(n);
        }
        while (!satisfy_condition2(n));
        cout << n << endl;
    }
    time (&end); // note time after execution
    //info_print("Terminated in %lf seconds.\n", 1000*difftime(end,begin));
    return 0;
}
