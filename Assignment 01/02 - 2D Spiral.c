#include <math.h>
#include <stdio.h>

int check_sqrt(int x) {
    int s = sqrt(x);
    return (s * s == x) ? s : -1;
}

void main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    int a[n][n];
    int i = n / 2, j = (n - 1) / 2, di = 0, dj = 1, s, s2;
    int even = 0, odd = 0;
    for (int x = 0; x < n * n; x++) {
        a[i][j] = x + 1;
        int sqr = check_sqrt(x);
        if (!sqr) {
            i += di;
            j += dj;
            continue;
        }
        if (sqr > 0) {
            if (x % 2) {
                di = -1;
                dj = 0;
            } else {
                di = 1;
                dj = 0;
            }
            s = s2 = sqr;
        }
        if (!dj && (di == -1) && !s) {
            di = 0;
            dj = -1;
            s = s2;
        } else if (!dj && (di == 1) && !s) {
            di = 0;
            dj = 1;
        }
        s--;
        i += di;
        j += dj;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%3d ", a[i][j]);
        printf("\n");
    }
}
