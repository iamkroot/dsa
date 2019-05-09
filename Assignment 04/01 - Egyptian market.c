#include <stdio.h>

int main(int argc, char const* argv[]) {
    int n, s;
    scanf("%d %d\n", &n, &s);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int cost[n][n + 1];
    for (int i = 0; i < n; i++) {
        for (int k = 0; k <= n; k++) {
            cost[i][k] = a[i] + ((i + 1) * (k));
        }
    }
    for (int k = n; k >= 0; k--) {
        // sort kth column in ascending order
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (cost[j][k] > cost[j + 1][k]) {
                    int t = cost[j][k];
                    cost[j][k] = cost[j + 1][k];
                    cost[j + 1][k] = t;
                }
            }
        }
        // calc total cost of first k items of kth column
        int tot = 0, num_items = 0;
        for (int i = 0; i < k; i++) {
            if (cost[i][k] + tot <= s) {
                tot += cost[i][k];
                num_items++;
            } else
                break;
        }
        if (num_items == k) {
            printf("%d %d", k, tot);
            return 0;
        }
    }
}
