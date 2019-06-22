#include <assert.h>
#include <stdio.h>

int solution(int A[], int N) {
    int result = 0;
    int missing = 0;
    for (int idx = 0 ; idx < N ; idx++)
    {
        if (A[idx] > ((idx + 1) + missing))
            missing++;
        else if (A[idx] < ((idx + 1) + missing))
            missing--;

        if (missing == 0)
            result += 1;
    }
    return result;
}

int main(int argc, char **argv)
{
    int A[] = {2,1,3,5,4};
    assert(solution(A, 5) == 3);
    int B[] = {2,3,4,1,5};
    assert(solution(B, 5) == 2);
    int C[] = {1,3,4,2,5};
    assert(solution(C, 5) == 3);
    return 0;
}
