#include <stdio.h>

int main(int argc, char const* argv[]) {
    int n, k;
    scanf("%d %d\n", &n, &k);
    int lo = 1, hi = n, mid;
    while (lo < hi) {
        mid = (lo / 2) + (hi / 2);
        int v = mid, tot = 0;
        while (v) {
            tot += v;
            v /= k;
        }
        if (tot >= n)
            hi = mid;
        else
            lo = mid + 1;
    }
    printf("%d", lo);
}
