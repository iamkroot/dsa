#include <stdio.h>

void heapify_down(int heap[], int heap_len, int i, int max_heap) {
    int l = 2 * i + 1, r = 2 * i + 2, child = -1;
    if (l >= heap_len)
        return;
    if (l < heap_len) {
        child = (max_heap ^ (heap[l] < heap[r])) ? l : r;
    }
    if (max_heap ^ (heap[child] < heap[i])) {
        int t = heap[child];
        heap[child] = heap[i];
        heap[i] = t;
        heapify_down(heap, heap_len, child, max_heap);
    }
}

void heapify_up(int heap[], int i, int max_heap) {
    if (i <= 0)
        return;
    int p = (i - 1) / 2;
    if (max_heap ^ (heap[i] < heap[p])) {
        int t = heap[i];
        heap[i] = heap[p];
        heap[p] = t;
        heapify_up(heap, p, max_heap);
    }
}

void insert(int heap[], int *heap_len, int x, int max_heap) {
    heap[*heap_len] = x;
    heapify_up(heap, *heap_len, max_heap);
    (*heap_len)++;
}

int pop(int heap[], int *heap_len, int max_heap) {
    if (heap_len <= 0)
        return -1;
    int top = heap[0];
    heap[0] = heap[--(*heap_len)];
    heapify_down(heap, *heap_len, 0, max_heap);
    return top;
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    int a[n];
    int left_heap[n], right_heap[n], left_len = 0, right_len = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        int x = a[i];
        insert(left_heap, &left_len, x, 1);
        int top = pop(left_heap, &left_len, 1);
        insert(right_heap, &right_len, top, 0);
        if (left_len < right_len) {
            top = pop(right_heap, &right_len, 0);
            insert(left_heap, &left_len, top, 1);
        }
        double med = left_len > right_len ? left_heap[0] : (double)(left_heap[0] + right_heap[0]) / 2;
        printf("%.1f\n", med);
    }
    return 0;
}
