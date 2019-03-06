#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 20

typedef struct TreeNode {
    char c;
    int visited;
    struct TreeNode* children[MAX_CHILDREN];
} TreeNode;

TreeNode* root = NULL;
int n, k, child_count[MAX_CHILDREN] = {0}, child_index[MAX_CHILDREN];

TreeNode* make_node(int c) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->c = c;
    node->visited = 0;
    for (int i = 0; i < k; i++) {
        node->children[k] = NULL;
    }

    return node;
}

void generate_tree(TreeNode* parent, char children[], int level) {
    if (level == 0)
        return;
    for (int i = 0; i < k; i++) {
        parent->children[i] = make_node(children[i]);
        printf("%c ", children[i]);
        generate_tree(parent->children[i], children, level - 1);
    }
    printf("\n");
}

char get_next(char prefix[]) {
    int min = 1e9, next_child = 0;
    for (int i = 0; i < k; i++) {
        if (min > child_count) {
            min = child_count;
            next_child = i;
        }
    }
    TreeNode* parent = root;
    for (char c = 0; c < k - 1; c++) {
    }
}

void main() {
    scanf("%d %d\n", &n, &k);
    char children[k];
    for (int i = 0; i < k; i++) {
        scanf("%c", &children[i]);
    }

    root = make_node('\0');

    generate_tree(root, children, n);
}
