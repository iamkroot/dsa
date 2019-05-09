#include <stdio.h>
#define MAX_NUM 105
void run() {
    int n;
    scanf("%d\n", &n);
    int ranges[MAX_NUM][3] = {},  // stores (l_index, r_index, team_num) for each range
        root[MAX_NUM],
        include[MAX_NUM] = {0};  // skip over the indices not in any range
    for (int i = 0; i < MAX_NUM; i++) {
        root[i] = i;
    }
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--; // 0-based indexing ftw
        ranges[i][0] = a;
        ranges[i][1] = b;

        // update roots for all indices after a
        for (int j = a; j < MAX_NUM; j++) {
            if (j <= b) {  // inside the new range that has been entered
                include[j] = 1;
                root[j] = root[a];
            } else if (a <= root[j] && root[j] <= b) {  // for those indices whose roots were inside the new range -> update roots to root[a]
                root[j] = root[a];
            }
        }
    }
    int team = 0, not_possible = 1;
    for (int i = 0; i < MAX_NUM; i++) {
        if (!include[i])
            continue;
        for (int j = 0; j < n; j++) {
            if (ranges[j][0] <= i && i <= ranges[j][1]) {  // assign team to all ranges that contain the current index
                if (team)
                    not_possible = 0;  // both teams have been given at least one range
                ranges[j][2] = team;
            }
        }
        if (i < MAX_NUM - 1 && root[i] != root[i + 1]) {
            team = !team;  // if the next root is different, change team. Basically, alternate the teams for disconnected ranges.
        }
    }
    if (not_possible) {  // if all ranges have same team
        printf("-1\n");
        return;
    }
    for (int i = 0; i < n; i++)
        printf("%s ", ranges[i][2] ? "CA" : "IM");
    printf("\n");
}

int main(int argc, char const* argv[]) {
    int t;
    scanf("%d", &t);
    while (t--)
        run();
}
