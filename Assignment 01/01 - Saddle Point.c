#include <stdio.h>

void main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    int a[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    int row_min[n], col_max[n];
    for (int i = 0; i < n; i++) {
        row_min[i] = -1;
        col_max[i] = -1;
        for (int j = 0; j < n; j++) {
            if (a[i][j] < row_min[i] || row_min[i] == -1)
                row_min[i] = a[i][j];
            if (a[j][i] > col_max[i] || col_max[i] == -1)
                col_max[i] = a[j][i];
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (row_min[i] == col_max[j]) {
                printf("Saddle point found at row %d, column %d, with value %d\n", i, j, row_min[i]);
                return;
            }
        }
    }
    printf("Matrix doesn't have a saddle point.\n");
}
