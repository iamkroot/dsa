#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_str {
    char s[100];
    struct node_str* next;
} node_str;

typedef struct node_int {
    int i;
    struct node_int* next;
} node_int;

int n, k;
char P[100];
node_int *seq = NULL, *seq_tail = NULL;
node_str* done = NULL;

void prepend(char str[]) {
    node_str* newnode = malloc(sizeof(node_str));
    strcpy(newnode->s, str);
    newnode->next = done;
    done = newnode;
}

int checkmember(char str[]) {
    for (node_str* p = done; p; p = p->next) {
        if (strcmp(str, p->s) == 0) {
            return 1;
        }
    }
    return 0;
}

void append(int i) {
    node_int* newnode = malloc(sizeof(node_int));
    newnode->i = i;
    newnode->next = NULL;
    if (!seq)
        seq = newnode;
    if (seq_tail)
        seq_tail->next = newnode;
    seq_tail = newnode;
}

void dfs(char prefix[]) {
    for (int i = 0; i < k; i++) {
        char str[n + 1];
        for (int j = 0; j < n - 1; j++) {
            str[j] = prefix[j];
        }
        str[n - 1] = P[i];
        str[n] = '\0';
        if (!checkmember(str)) {
            prepend(str);
            dfs(str + 1);
            append(i);
        }
    }
}

void main() {
    scanf("%d %d\n", &n, &k);
    scanf("%s", P);
    P[k] = '\0';
    char start[n];
    for (int i = 0; i < n - 1; i++) {
        start[i] = P[0];
    }
    start[n - 1] = '\0';
    dfs(start);
    int len = (int)pow(k, n) + n, i;
    char S[len];
    for (i = 0; seq; i++) {
        S[i] = P[seq->i];
        seq = seq->next;
    }
    for (; i < len - 1; i++) {
        S[i] = P[0];
    }
    S[i] = '\0';
    printf("%s", S);
}
