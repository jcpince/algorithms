#include <bits/stdc++.h>

using namespace std;

#define BITINT_CHUNK_RANGE (1000000ULL)

// Complete the extraLongFactorials function below.
void extraLongFactorials(int n) {

    vector<uint64_t> factorial = {1};

    for (int i = 2 ; i <= n ; i++) {
        // Mulpiply the chunks
        for (int idx = 0 ; idx < factorial.size() ; idx++) {
            factorial[idx] *= i;
        }
        // Now, propagate the carry
        for (int idx = 0 ; idx < factorial.size() ; idx++) {
            if (factorial[idx] > BITINT_CHUNK_RANGE) {
                uint64_t carry = factorial[idx] / BITINT_CHUNK_RANGE;
                factorial[idx] = factorial[idx] % BITINT_CHUNK_RANGE;
                if (idx < factorial.size()-1) {
                    factorial[idx+1] += carry;
                } else factorial.push_back(carry);
            }
        }
    }
    printf("%ld", factorial.back());
    for (int idx = factorial.size()-2 ; idx > -1 ; idx--)
        printf("%06ld", factorial[idx]);
    printf("\n");
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    extraLongFactorials(n);

    return 0;
}
