#include <stdio.h>

int pq_len = 0, pq[1000];

void heapify_down(int i) {
    int l = 2 * i + 1, r = 2 * i + 2, smaller = -1;
    if (l < pq_len) {
        smaller = pq[l] < pq[r] ? l : r;
    }
    if (smaller >= 0 && pq[smaller] < pq[i]) {
        int t = pq[smaller];
        pq[smaller] = pq[i];
        pq[i] = t;
        heapify_down(smaller);
    }
}

void heapify_up(int i) {
    if (i <= 0)
        return;
    int p = (i - 1) / 2;
    if (pq[i] < pq[p]) {
        int t = pq[i];
        pq[i] = pq[p];
        pq[p] = t;
        heapify_up(p);
    }
}

void insert(int x) {
    pq[pq_len] = x;
    heapify_up(pq_len);
    pq_len++;
}

int pop() {
    if (pq_len <= 0)
        return -1;
    int top = pq[0];
    pq[0] = pq[--pq_len];
    heapify_down(0);
    return top;
}
void show() {
    for (int i = 0; i < pq_len; i++) {
        printf("%d ", pq[i]);
    }
    printf("\n");
}
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        insert(a);
    }
    int count = 0;
    while (pq[0] < k && pq_len > 1) {
        int least = pop();
        int least2 = pop();
        insert(least + 2 * least2);
        count++;
    }
    if (pq_len < 1 || pq[0] < k) {
        printf("Not possible");
        return 0;
    }
    printf("%d", count);
}
