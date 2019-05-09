#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int arr;
    int proc;
} task;

int pq_len = 0;
task pq[1000];

void heapify_down(int i) {
    int l = 2 * i + 1, r = 2 * i + 2, largest = -1;
    if (l < pq_len) {
        largest = !(pq[l].proc < pq[r].proc || pq[l].arr <= pq[r].arr) ? l : r;
    }
    if (largest >= 0 && pq[largest] > pq[i]) {
        task t = pq[largest];
        pq[largest] = pq[i];
        pq[i] = t;
        heapify_down(largest);
    }
}

void heapify_up(int i) {
    if (i <= 0)
        return;
    int p = (i - 1) / 2;
    if (pq[i].proc > pq[p].proc || (pq[i].proc == pq[p].proc && pq[i].arr > pq[p].arr)) {
        int a = pq[i].arr, b = pq[i].proc;
        pq[i].arr = pq[p].arr;
        pq[i].proc = pq[p].proc;
        pq[p].arr = a;
        pq[p].proc = b;
        heapify_up(p);
    }
}

void insert(task t) {
    pq[pq_len].arr = t.arr;
    pq[pq_len].proc = t.proc;
    heapify_up(pq_len);
    pq_len++;
}

task pop() {
    if (pq_len <= 0)
        return;
    task top = pq[0];
    pq[0] = pq[pq_len - 1];
    heapify_down(0);
    pq_len--;
    return top;
}

void show() {
    for (int i = 0; i < pq_len; i++) {
        printf("%d ", pq[i]);
    }
    printf("\n");
}

int comp_sort_desc_arr(const void* a, const void* b) {
    task t1 = *((task*)a), t2 = *((task*)b);
    return (t1.arr == t2.arr) ? (t1.proc < t2.proc) : (t1.arr < t2.arr);
}

int main() {
    int n;
    scanf("%d", &n);
    task times[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &(times[i].arr), &(times[i].proc));
    }
    qsort((void*)times, n, sizeof(times[0]), comp_sort_desc_arr);
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", times[i].arr, times[i].proc);
    }
}
