#include <vector>
#include <cstdio>

using namespace std;

int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
    int x = 0, y = 0, z = 0;
    for (int a : A)
    {
        ++x *= a <= R;
        ++y *= a < L;
        printf("x is %d, y is %d\n", x, y);
        z += x - y;
    }
    return z;
}

int main(int argc, char **argv)
{
    vector<int> A;

    A = {3,3,3};
    printf("numSubarrayBoundedMax([3,3,3], 3, 3) => %d\n", numSubarrayBoundedMax(A,3,3));

    A = {3,1,1,3};
    printf("numSubarrayBoundedMax([3,1,1,3], 3, 3) => %d\n", numSubarrayBoundedMax(A,3,3));

    A = {3,1,3,1};
    printf("numSubarrayBoundedMax([3,1,3,1], 3, 3) => %d\n", numSubarrayBoundedMax(A,3,3));
    return 0;
}
