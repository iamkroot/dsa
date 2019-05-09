#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node* next;
} node;

node *start = NULL, *last = NULL;

node* new_node(int data) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void append(int data) {
    node* newnode = new_node(data);
    if (last)
        last->next = newnode;
    last = newnode;
    if (!start)
        start = newnode;
}

void fill_primes() {
    int n = 31623, sqrtn = 177;
    short is_prime[n];
    for (int i = 0; i < n; i++)
        is_prime[i] = 1;
    int i;
    for (i = 3; i <= sqrtn; i += 2) {
        if (is_prime[i]) {
            append(i);
            for (int j = i * i; j <= n; j += 2 * i)
                is_prime[j] = 0;
        }
    }
    for (; i <= n; i += 2)
        if (is_prime[i])
            append(i);
}

void segmented_sieve(int m, int n) {
    int range = n - m;
    short is_prime[range + 1];
    for (int i = 0; i <= range; i++)
        is_prime[i] = 1;
    for (node* p = start; p; p = p->next) {
        int prime = p->data;
        int ps = prime * prime;
        int begin = (m + prime - 1) / prime;
        begin = begin > ps ? begin : ps;
        if ((begin & 1) == 0)
            begin += prime;
        begin -= m;
        for (int i = 0; i <= range; i += 2 * prime)
            is_prime[i] = 0;
    }
    if (m <= 2 && n >= 2)
        printf("2 ");
    for (int i = (m & 1) ? 0 : 1; i <= range; i += 2) {
        if (is_prime[i])
            printf("%d ", m + i);
    }
}

void main(int argc, char const* argv[]) {
    fill_primes();
    int a, b;
    scanf("%d %d\n", &a, &b);
    segmented_sieve(a, b);
}
