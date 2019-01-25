#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int v;
    struct node* next;
} node;

node* cur_path_start = NULL;
node* cycles[1000];
int cycles_counter = 0, weights[1000], min_weight = 1e9;

void prepend(node** head, int v) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->v = v;
    newnode->next = *head;
    *head = newnode;
}

void prlist(node* head) {
    for (node* p = head; p; p = p->next) {
        printf("%d", p->v);
        printf(p->next ? "->" : "\n");
    }
}

int adj[1000][1000], visited[1000];
int n, m;

void dfs(int start, int v, int cur_weight) {
    prepend(&cur_path_start, v);
    if (visited[v]) {
        if (start == v) {
            for (node* p = cur_path_start; p; p = p->next)
                prepend(&cycles[cycles_counter], p->v);
            weights[cycles_counter] = cur_weight;
            if (min_weight > cur_weight)
                min_weight = cur_weight;
            cycles_counter++;
        }
    } else {
        visited[v] = 1;
        for (int i = 0; i < n; i++)
            if (adj[v][i]) {
                dfs(start, i, cur_weight + adj[v][i]);
            }
        visited[v] = 0;
    }
    cur_path_start = cur_path_start->next;
}

void main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a][b] = c;
    }
    for (int i = 0; i < n; i++) {
        dfs(i, i, 0);
        visited[i] = 1;
    }
    if (!cycles_counter) {
        printf("No cycles found.\n");
        return;
    }
    printf("Cycles with minimum weight %d are:\n", min_weight);
    for (int i = 0; i < cycles_counter; i++) {
        if (weights[i] == min_weight)
            prlist(cycles[i]);
    }
}
