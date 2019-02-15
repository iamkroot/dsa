#include <stdio.h>
#define MAX_NUM 105
void run() {
    int n;
    scanf("%d\n", &n);
    int ranges[MAX_NUM][3] = {}, root[MAX_NUM], include[MAX_NUM] = {0};
    for (int i = 0; i < MAX_NUM; i++) {
        root[i] = i;
    }
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        ranges[i][0] = a;
        ranges[i][1] = b;
        for (int j = a; j < MAX_NUM; j++) {
            if (j <= b) {
                include[j] = 1;
                root[j] = root[a];
            } else if (root[j] >= a && root[j] <= b) {
                root[j] = root[a];
            }
        }
    }
    int team = 0, teams[MAX_NUM] = {0}, flag = 0;
    for (int i = 0; i < MAX_NUM; i++) {
        if (!include[i])
            continue;
        teams[i] = team;
        if (i < MAX_NUM - 1 && root[i] != root[i + 1]) {
            team = !team;
        }
        for (int j = 0; j < n; j++) {
            if (ranges[j][0] <= i && ranges[j][1] >= i) {
                if (!teams[i] && !flag)
                    flag++;
                else if (flag == 1 && teams[i])
                    flag = 2;
                ranges[j][2] = teams[i];
            }
        }
    }
    if (flag < 2) {
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
