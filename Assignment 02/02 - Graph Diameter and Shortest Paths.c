#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 1000

typedef struct node {
    short v;
    unsigned int w;
    struct node* next;
    struct node* prev;
} node;

void store_min(node** head, int v, unsigned int w) {  // add v to list if w <= p->w for all p in list
    if (*head && w < (*head)->w) {
        for (node* p = *head; p; p = p->next) {
            free(p);
        }
        *head = NULL;
    } else if (*head && w > (*head)->w) {
        return;
    }
    for (node* p = *head; p; p = p->next) {
        if (p->v == v)
            return;
    }
    node* newnode = (node*)malloc(sizeof(node));
    newnode->v = v;
    newnode->w = w;
    newnode->next = *head;
    *head = newnode;
}

void prlist(node* start) {
    for (node* p = start; p; p = p->next) {
        printf("%d", p->v);
        printf(p->next ? "->" : "\n");
    }
}

short n;
char adj[MAX_NODES][MAX_NODES];
unsigned short dist[MAX_NODES][MAX_NODES];
node* next[MAX_NODES][MAX_NODES];

void floyd_warshall() {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][j] >= dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    if (next[i][k])
                        store_min(&next[i][j], next[i][k]->v, dist[i][j]);
                }
}

node *cur_path = NULL, *cur_path_last = NULL;

void append(int v) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->v = v;
    newnode->next = NULL;
    newnode->prev = NULL;
    if (!cur_path) {
        cur_path = newnode;
    }
    if (cur_path_last) {
        cur_path_last->next = newnode;
        newnode->prev = cur_path_last;
    }
    cur_path_last = newnode;
}

void pop() {
    if (!cur_path_last)
        return;
    node* cur_path_last_prev = cur_path_last->prev;
    free(cur_path_last);
    if (cur_path_last_prev)
        cur_path_last_prev->next = NULL;
    else
        cur_path = NULL;
    cur_path_last = cur_path_last_prev;
}

void shortest_path(int i, int j) {
    if (next[i][j] == NULL) {
        printf("No path\n");
        return;
    }
    append(i);
    if (i == j) {
        prlist(cur_path);
        return;
    }
    for (node* p = next[i][j]; p; p = p->next) {
        shortest_path(p->v, j);
        pop();
    }
}

void main() {
    int m;
    scanf("%hi %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
            next[i][j] = NULL;
            dist[i][j] = SHRT_MAX;
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][b] = adj[b][a] = dist[a][b] = dist[b][a] = 1;
        store_min(&next[a][b], b, 1);
        store_min(&next[b][a], a, 1);
    }
    floyd_warshall();
    floyd_warshall();  // not a typo :P
    int diameter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (diameter < dist[i][j])
                diameter = dist[i][j];
            printf("(%d, %d): \n", i, j);
            shortest_path(i, j);
            while (cur_path)
                pop();
            printf("\n");
        }
    }
    printf("Diameter: %d\n", diameter);
}
