#include <stdio.h>

int merge(int a[], int l[], int nl, int r[], int nr) {
    int i = 0, j = 0, count = 0;
    while (i < nl || j < nr) {
        if (i == nl) {
            a[i + j] = r[j];
            j++;
        } else if (j == nr) {
            a[i + j] = l[i];
            i++;
        } else if (l[i] <= r[j]) {
            a[i + j] = l[i];
            i++;
        } else {
            a[i + j] = r[j];
            count += nl - i;
            j++;
        }
    }
    return count;
}

int count_inv(int a[], int n) {
    if (n < 2)
        return 0;
    int p = (n + 1) / 2;
    int l[p], r[n - p];
    for (int i = 0; i < p; i++) {
        l[i] = a[i];
    }
    for (int i = 0; i < n - p; i++) {
        r[i] = a[p + i];
    }
    return count_inv(l, p) + count_inv(r, n - p) + merge(a, l, p, r, n - p);
}

int main(int argc, char const* argv[]) {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    printf("%d\n", count_inv(a, n));
}
