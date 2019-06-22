#include <assert.h>
#include <stdio.h>

int interval_sum(int A[], int N)
{
    int sum = 0;
    for (int idx = 0 ; idx < N ; idx++)
        sum += A[idx];
    return sum;
}

int solution(int A[], int N, int K, int L) {
    int max = -1;

    for (int idx = 0 ; idx < (N - K - L) ; idx++)
    {
        for (int jdx = idx + K ; jdx < (N - L + 1) ; jdx++)
        {
            int sum = interval_sum(&A[idx], K) + interval_sum(&A[jdx], L);
            if (max < sum)
                max = sum;
        }
    }

    for (int idx = 0 ; idx < (N - K - L) ; idx++)
    {
        for (int jdx = idx + K ; jdx < (N - K + 1) ; jdx++)
        {
            int sum = interval_sum(&A[idx], L) + interval_sum(&A[jdx], K);
            if (max < sum)
                max = sum;
        }
    }
    return max;
}

int main(int argc, char **argv)
{
    int A[] = {6,1,4,6,3,2,7,4};
    assert(solution(A, 8, 3, 2) == 24);
    assert(solution(A, 8, 2, 3) == 24);
    printf("Tests succeeded\n");
    return 0;
}
