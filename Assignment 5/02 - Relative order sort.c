#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 106
int comp(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x > y;
}
int main(int argc, char const* argv[]) {
    int n, m;
    scanf("%d %d", &n, &m);
    int a1[n], a2[m];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a1[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &a2[i]);
    }
    int pos = 0;
    for (int i = 0; i < m; i++) {
        for (int j = pos; j < n; j++) {
            if (a2[i] == a1[j]) {
                int t = a1[pos];
                a1[pos] = a1[j];
                a1[j] = t;
                pos++;
            }
        }
    }
    qsort((void*)(a1 + pos), n - pos, sizeof(int), comp);
    for (int i = 0; i < n; i++) {
        printf("%d ", a1[i]);
    }
}
