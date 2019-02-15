// O(n**2) Pls don't use irl
#include <limits.h>
#include <stdio.h>

void swap(int a[], int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

int main(int argc, char const* argv[]) {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int swaps = 0;
    for (int i = 0; i < n; i++) {
        int min = INT_MAX, loc = i;
        for (int j = i; j < n; j++) {
            if (min > a[j]) {
                min = a[j];
                loc = j;
            }
        }
        if (loc == i)
            continue;
        swap(a, i, loc);
        swaps++;
    }
    printf("%d\n", swaps);
}
