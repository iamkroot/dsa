#include <stdio.h>

int main(int argc, char const* argv[]) {
    int N;
    scanf("%d", &N);
    if (N <= 6)
        return N;
    int optimal[N + 1];
    for (int i = 0; i < 7; i++) {
        optimal[i] = i;
    }
    for (int i = 7; i <= N; i++) {
        optimal[i] = 0;
        for (int j = i - 3; j > 0; j--) {
            int best = (i - j - 1) * optimal[j];
            if (optimal[i] < best)
                optimal[i] = best;
        }
    }
    for (int i = 0; i < N + 1; i++) {
        printf("%d\n", optimal[i]);
    }
}
