#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000
#define MAX_EDGES (MAX_NODES * (MAX_NODES - 1)) / 2

typedef struct node {
    int data;
    struct node* next;
} node;

int orig_adj[MAX_NODES][MAX_NODES], edges[MAX_EDGES][2];

void append(node** head, int v) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = v;
    newnode->next = NULL;
    if (*head == NULL) {
        *head = newnode;
        return;
    }
    node* t = *head;
    *head = newnode;
    newnode->next = t;
}

int checkmember(node* head, int v) {
    for (; head; head = head->next) {
        if (head->data == v)
            return 1;
    }
    return 0;
}

int time = 1;
node* critical;

void find_critical_nodes(node* adjlst[], int disc[], int visited[], int low[], int parent[], int v) {
    visited[v] = 1;
    disc[v] = low[v] = time++;
    int child_count = 0;
    for (node* connected_node = adjlst[v]; connected_node; connected_node = connected_node->next) {
        int i = connected_node->data;
        if (!visited[i]) {
            child_count++;
            parent[i] = v;
            find_critical_nodes(adjlst, disc, visited, low, parent, i);
            low[v] = low[i] < low[v] ? low[i] : low[v];
            if ((parent[v] == -1 && child_count > 1) || (parent[v] != -1 && low[i] >= disc[v]) && !checkmember(critical, v)) {
                append(&critical, v);
            }
        } else if (parent[v] != i) {
            low[v] = ((low[v] == -1) || (disc[i] <= low[v])) ? disc[i] : low[v];
        }
    }
}

void print_edge(int e) {
    printf("(%d, %d)", edges[e][0], edges[e][1]);
}

void dfs(node* adjlst[], int prev, int cur, int blacklist, int visited[]) {
    visited[cur] = 1;
    if (cur == blacklist)
        return;
    print_edge(cur);
    for (node* p = adjlst[cur]; p; p = p->next)
        if (!visited[p->data]) {
            dfs(adjlst, cur, p->data, blacklist, visited);
        }
}

void print_components(node* adjlst[], int m, int critical_vert) {
    int visited[MAX_EDGES] = {0};
    for (int i = 0; i < m; i++) {
        if (!visited[i]) {
            dfs(adjlst, -1, i, critical_vert, visited);
            printf("\n");
        }
    }
}

int main(int argc, char const* argv[]) {
    int n, m;
    scanf("%d %d", &n, &m);
    node* adjlst[m];
    int disc[m], visited[m], low[m], parent[m];
    for (int i = 0; i < m; i++) {
        disc[i] = visited[i] = 0;
        low[i] = parent[i] = -1;
        adjlst[i] = NULL;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d ", &orig_adj[i][j]);
        }
    }
    int edge_counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (orig_adj[i][j] == 1) {
                edges[edge_counter][0] = i;
                edges[edge_counter][1] = j;
                edge_counter++;
                orig_adj[i][j] = orig_adj[j][i] = -1;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int v1 = edges[i][0], v2 = edges[i][1];
        for (int j = 0; j < m; j++) {
            if (i == j)
                continue;
            int v3 = edges[j][0], v4 = edges[j][1];
            if (v1 == v3 || v1 == v4 || v2 == v3 || v2 == v4) {
                append(&adjlst[i], j);
            }
        }
    }
    printf("Adjacency list of G':\n");
    for (int i = 0; i < m; i++) {
        print_edge(i);
        printf(": ");
        for (node* p = adjlst[i]; p; p = p->next) {
            print_edge(p->data);
            printf(p->next ? ", " : "\n");
        }
    }
    printf("\n");
    find_critical_nodes(adjlst, disc, visited, low, parent, 0);
    int num_undiscovered_nodes = 0, first_node;
    for (int i = 0; i < n; i++) {
        if (low[i] < 0) {
            num_undiscovered_nodes++;
            first_node = i;
        }
    }
    if (num_undiscovered_nodes == 1) {
        critical = NULL;
        for (int i = 0; i < n; i++) {
            if (i != first_node) {
                append(&critical, i);
            }
        }
    } else if (num_undiscovered_nodes > 1) {
        critical = NULL;
        for (int i = 0; i < n; i++) {
            append(&critical, i);
        }
    }
    if (!critical) {
        printf("No such vertex exists.\n");
        return 0;
    }
    printf("Critical points:\n");
    while (critical) {
        int e = critical->data;
        print_edge(e);
        printf("\nComponents:\n");
        print_components(adjlst, m, e);
        critical = critical->next;
        printf("\n");
    }
}
