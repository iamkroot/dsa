#include <limits.h>
#include <stdio.h>
int n, a[100][100], sum[100][100];

int max_submatrix(int m) {
    int total, max = INT_MIN;
    for (int i = m - 1; i < n; i++) {
        for (int j = m - 1; j < n; j++) {
            total = sum[i][j];
            if (i - m >= 0)
                total -= sum[i - m][j];
            if (j - m >= 0)
                total -= sum[i][j - m];
            if (i - m >= 0 && j - m >= 0)
                total += sum[i - m][j - m];
            if (total > max)
                max = total;
        }
    }
    return max;
}
int main(int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d ", &a[i][j]);
    sum[0][0] = a[0][0];
    for (int i = 1; i < n; i++)
        sum[0][i] = a[0][i] + sum[0][i - 1];
    for (int i = 1; i < n; i++)
        sum[i][0] = a[i][0] + sum[i - 1][0];
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            sum[i][j] = a[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    int max = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int m = max_submatrix(i);
        if (max < m)
            max = m;
    }
    printf("%d\n", max);
}
