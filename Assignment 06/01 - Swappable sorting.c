#include <stdio.h>
#define MAX_NODES 1000
int n, adj[MAX_NODES][MAX_NODES], visited[MAX_NODES] = {0}, swappable[MAX_NODES] = {0};

void dfs(int prev, int cur) {
    visited[cur] = 1;
    if (prev >= 0)
        swappable[cur] = swappable[prev] = 1;
    for (int i = 0; i < n; i++)
        if (adj[cur][i] && !visited[i])
            dfs(cur, i);
}

int main(int argc, char const* argv[]) {
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        if (visited[i])
            continue;
        for (int j = 0; j < n; j++) {
            swappable[j] = 0;
        }
        dfs(-1, i);
        // sort the swappable elements
        for (int j = 0; j < n; j++) {
            if (!swappable[j])
                continue;
            for (int k = 0; k < n - i - 1; k++) {
                if (swappable[k] && a[j] < a[k]) {
                    int t = a[j];
                    a[j] = a[k];
                    a[k] = t;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}
