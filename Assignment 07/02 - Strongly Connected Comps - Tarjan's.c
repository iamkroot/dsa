#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 1000

typedef struct node {
    int v;
    struct node* next;
} node;

node* stack = NULL;
int n, instack[MAX_NODES] = {0}, time = 0, num_comps = 0, comps[MAX_NODES] = {0};

void prepend(node** head, int v) {
    node* newnode = malloc(sizeof(node));
    newnode->v = v;
    newnode->next = *head;
    *head = newnode;
}

int pop(node** head) {
    if (!*head)
        return -1;
    node* t = *head;
    int v = t->v;
    *head = (*head)->next;
    free(t);
    return v;
}

void dfs(int u, node* adjlst[], int disc[], int low[]) {
    disc[u] = low[u] = ++time;
    prepend(&stack, u);
    instack[u] = 1;
    for (node* p = adjlst[u]; p; p = p->next) {
        int v = p->v;
        if (disc[v] < 0) {
            dfs(v, adjlst, disc, low);
            low[u] = low[u] < low[v] ? low[u] : low[v];
        } else if (instack[v]) {
            low[u] = low[u] < disc[v] ? low[u] : disc[v];
        }
    }
    if (disc[u] == low[u]) {
        num_comps++;
        int v = -1;
        do {
            v = pop(&stack);
            instack[v] = 0;
            comps[v] = num_comps;
        } while (u != v);
    }
}

void main() {
    int m;
    scanf("%d", &n);
    node* adjlst[n];
    int disc[n], low[n], cost[n];
    for (int i = 0; i < n; i++) {
        low[i] = 0;
        disc[i] = -1;
        adjlst[i] = NULL;
        scanf("%d", &cost[i]);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        prepend(&adjlst[a], b);
    }
    for (int i = 0; i < n; i++) {
        if (disc[i] < 0) {
            dfs(i, adjlst, disc, low);
        }
    }
    int min_node_cost[num_comps], num_min_nodes[num_comps];
    for (int i = 0; i < num_comps; i++) {
        min_node_cost[i] = 1e9;
    }
    for (int i = 0; i < n; i++) {
        int comp = comps[i] - 1, c = cost[i];
        if (min_node_cost[comp] > c) {
            min_node_cost[comp] = c;
            num_min_nodes[i] = 1;
        } else if (min_node_cost[comp] == c) {
            num_min_nodes[comp]++;
        }
    }
    int money = 0, ways = 1;
    for (int i = 0; i < num_comps; i++) {
        money += min_node_cost[i];
        ways *= num_min_nodes[i];
    }
    printf("%d %d", money, ways);
}
