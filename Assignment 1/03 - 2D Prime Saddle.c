#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

node *start = NULL, *last = NULL;
void append(int data) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    if (last)
        last->next = newnode;
    last = newnode;
    if (!start)
        start = newnode;
}

int pop() {
    if (!start)
        return -1;
    int a = start->data;
    node* p = start->next;
    free(start);
    start = p;
    return a;
}

void fill_primes(int n) {
    int x = 3, count, p;
    if (n < 1)
        return;
    append(2);
    for (count = 2; count <= n; x++) {
        for (p = 2; p < x; p++)
            if (x % p == 0)
                break;
        if (p == x) {
            append(p);
            count++;
        }
    }
}

int check_sqrt(int x) {
    int s = sqrt(x);
    return (s * s == x) ? s : -1;
}

void main(int argc, char const* argv[]) {
    int n;
    scanf("%d", &n);
    int a[n][n];
    fill_primes(n * n);
    int i = n / 2, j = (n - 1) / 2, di = 0, dj = 1, s, s2;
    int even = 0, odd = 0;
    for (int x = 0; x < n * n; x++) {
        a[i][j] = pop();
        int sqr = check_sqrt(x);
        if (!sqr) {
            i += di;
            j += dj;
            continue;
        }
        if (sqr > 0) {
            if (x % 2) {
                di = -1;
                dj = 0;
            } else {
                di = 1;
                dj = 0;
            }
            s = s2 = sqr;
        }
        if (!dj && (di == -1) && !s) {
            di = 0;
            dj = -1;
            s = s2;
        } else if (!dj && (di == 1) && !s) {
            di = 0;
            dj = 1;
        }
        s--;
        i += di;
        j += dj;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%3d ", a[i][j]);
        printf("\n");
    }
}
