#include <stdio.h>
#include <stdlib.h>

int comp(const void* p, const void* q) {
    return *(int*)p > *(int*)q;
}

int main(int argc, char const* argv[]) {
    int n, k, s, t;
    scanf("%d %d %d %d", &n, &k, &s, &t);
    k++;
    int cars[n][2], pumps[k];
    pumps[k - 1] = s;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cars[i][0], &cars[i][1]);
    }
    for (int i = 0; i < k - 1; i++) {
        scanf("%d", &pumps[i]);
    }

    qsort((void*)pumps, k, sizeof(int), comp);
    int max_dist = -1, min_price = -1;
    for (int i = k - 1; i > 0; i--) {
        pumps[i] -= pumps[i - 1];
        if (max_dist < pumps[i])
            max_dist = pumps[i];
    }
    for (int i = 0; i < n; i++) {
        int cap = cars[i][1];
        if (cap < max_dist) continue;
        int sum = 0;
        for (int j = 0; j < k; j++) {
            if (cap > 2 * pumps[j]) {
                sum += pumps[j];
            } else {
                sum += (3 * pumps[j]) - cap;
            }
            if (sum > t)
                break;
        }
        if (sum <= t && (min_price < 0 || cars[i][0] < min_price)) {
            min_price = cars[i][0];
        }
    }
    printf("%d\n", min_price);
}
