#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 1000

short n;
char adj[MAX_NODES][MAX_NODES], visited[MAX_NODES];
void dfs(int start, int v, int cur_path_len) {
    if (visited[v]) {
        if (start == v && cur_path_len % 2) {
            printf("Not bipartite!\n");
            exit(0);
        }
    } else {
        visited[v] = 1;
        for (int i = 0; i < n; i++)
            if (adj[v][i]) {
                dfs(start, i, cur_path_len + 1);
            }
        visited[v] = 0;
    }
}

void main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            scanf("%d ", &adj[i][j]);
    }
    for (int i = 0; i < n; i++) {
        dfs(i, i, 0);
        visited[i] = 1;
    }

    printf("Bipartite\n");
}
