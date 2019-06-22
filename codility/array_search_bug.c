#include <stdio.h>
#include <assert.h>

#define min

int solution(int *A, int N, int X) {
    int r, m, l;
    if (N == 0) {
        return -1;
    }
    printf("Starts\n", m, A[m]);
    l = 0;
    r = N - 1;
    while (l < r) {
        m = (r > l+1) ? (l + r) / 2 : r;
        printf("A[%d](%d)\n", m, A[m]);
        if (A[m] > X)  {
            printf("Set r(%d) to m(%d) - 1\n", r, m);
            r = m - 1;
        } else {
            printf("Set l(%d) to m(%d)\n", l, m);
            l = m;
        }
    }
    printf("Return A[%d](%d)\n", l, A[l]);
    if (A[l] == X) {
        return l;
    }
    return -1;
}

int main(int argc, char **argv)
{
    int A[] = {1,2,3,4,5,6,7};
    assert(solution(A, 7, 1) == 0);
    assert(solution(A, 7, 3) == 2);
    assert(solution(A, 7, 4) == 3);
    assert(solution(A, 7, 7) == 6);
    assert(solution(A, 6, 7) == -1);
    assert(solution(A, 6, -1) == -1);
    int B[] = {1,2,3,4,5,6};
    assert(solution(A, 6, 1) == 0);
    assert(solution(B, 6, 3) == 2);
    assert(solution(B, 6, 4) == 3);
    assert(solution(B, 6, 6) == 5);
    assert(solution(B, 6, 7) == -1);
    assert(solution(B, 6, -1) == -1);
    int C[] = {1,1,2,4,5,6};
    assert((solution(C, 6, 1) == 0) || (solution(C, 6, 1) == 1));
    assert(solution(C, 6, 3) == -1);
    assert(solution(C, 6, 4) == 3);
    assert(solution(C, 6, 6) == 5);
    assert(solution(C, 6, 7) == -1);
    assert(solution(C, 6, -1) == -1);
    return 0;
}
