#include <stdio.h>

int main(int argc, char const* argv[]) {
    int n, m;
    scanf("%d %d\n", &n, &m);
    double x;
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d ", &a);
        x += (double)1 / a;
    }

    int lo = 1, hi = m, mid;
    while (lo < hi) {
        mid = (hi + lo) / 2;
        if ((int)(mid * x) < m)
            lo = mid + 1;
        else
            hi = mid;
    }
    printf("%d\n", hi);
}
