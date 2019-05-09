#include <limits.h>
#include <stdio.h>
#define MAX_NODES 1000

int n, del;
int vert[MAX_NODES], f[MAX_NODES], adj[MAX_NODES][MAX_NODES], visited[MAX_NODES];

void dfs(int prev, int cur, int comp_adj[][MAX_NODES]) {
    visited[cur] = 1;
    if (prev >= 0)
        comp_adj[prev][cur] = comp_adj[cur][prev] = 1;
    for (int i = 0; i < n; i++)
        if (adj[cur][i] && !visited[i]) {
            dfs(cur, i, comp_adj);
        }
}

int main(int argc, char const *argv[]) {
    printf("Enter number of vertices: ");
    scanf("%d\n", &n);
    printf("Enter vertex and factor:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d\n", &vert[i], &f[i]);
        visited[i] = 0;
    }
    printf("Enter delta: ");
    scanf("%d", &del);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a = f[i] - f[j];
            adj[i][j] = a >= del || -a >= del;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int comp_adj[MAX_NODES][MAX_NODES];
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    comp_adj[j][k] = 0;
                }
            }
            dfs(-1, i, comp_adj);
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    printf("%d ", comp_adj[j][k]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}
