#include <limits.h>
#include <stdio.h>

typedef struct {
    int arr_tm;
    int proc_tm;
} Order;

int main() {
    int n;
    scanf("%d", &n);
    Order orders[n];
    int arr_tm[n], proc_tm[n], total = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &(arr_tm[i]), &(proc_tm[i]));
    }
    int num_complete = 0, t = 0, min = INT_MAX, shortest = 0, found = 0;
    for (; num_complete != n; t++) {
        for (int i = 0; i < n; i++) {
            if (arr_tm[i] <= t && proc_tm[i] < min && proc_tm[i] > 0) {
                shortest = i;
                min = proc_tm[i];
                found = 1;
            }
        }
        if (!found) {
            continue;
        }
        proc_tm[shortest]--;
        min--;
        if (!proc_tm[shortest]) {
            min = INT_MAX;
            num_complete++;
            found = 0;
            total += t + 1 - arr_tm[shortest];
        }
    }
    printf("%d", total / n);
}
