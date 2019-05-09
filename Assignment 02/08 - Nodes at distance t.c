#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

int n, t;
int adj[MAX_NODES][MAX_NODES], count[MAX_NODES];

void dfs_level(int v, int level) {
    for (int i = 0; i < n; i++) {
        if (adj[v][i]) {
            if (level == t) {
                count[i] = 1;
            } else {
                dfs_level(i, level + 1);
            }
        }
    }
}

int main(int argc, char const* argv[]) {
    int m;
    scanf("%d %d\n", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d\n", &a, &b);
        adj[a][b] = adj[b][a] = 1;
    }
    scanf("%d", &t);
    for (int i = 0; i < n; i++) {
        dfs_level(i, 0);
    }
    int tot = 0;
    for (int i = 0; i < n; i++) {
        tot += count[i];
    }
    printf("%d\n", tot);
}
