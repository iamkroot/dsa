#include <stdio.h>

int main(int argc, char const* argv[]) {
    int n, x;
    scanf("%d %d", &n, &x);
    int dist[n][n];
    x--;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = 1e9;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        dist[a][b] = dist[b][a] = 1;
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][j] >= dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    int max_dist = 0, moves = dist[0][x];
    for (int i = 0; i < n; i++) {
        int d = dist[0][i] - dist[x][i];
        if (max_dist <= d && moves < dist[0][i] * 2) {
            max_dist = d;
            moves = dist[0][i] * 2;
        }
    }
    printf("%d", moves);
}
