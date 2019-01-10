#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

node *start = NULL, *last = NULL;

node* new_node(int data) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void append(int data) {
    node* newnode = new_node(data);
    if (last)
        last->next = newnode;
    last = newnode;
    if (!start)
        start = newnode;
}

void search(int s) {
    if (!start)
        return;
    int i = 0;
    for (node* p = start; p; p = p->next, i++)
        if (p->data == s)
            printf("%d ", i);
    printf("\n");
}

void delete(int s) {
    int found = 0;
    node* pp = start;
    for (node* p = start; p; pp = p, p = p->next) {
        last = p;
        if (p->data == s) {
            if (!found)
                found = 1;
            else {
                pp->next = p->next;
                last = pp;
                free(p);
            }
        }
    }
}

void swap(int s) {
    node *p = start, *pp = start;
    for (; p && p->data != s; pp = p, p = p->next)
        ;
    if (!p || !p->next)
        return;
    node* next = p->next;
    p->next = next->next;
    next->next = p;
    if (p == start) {
        start = next;
        return;
    }
    pp->next = next;
}

void printlist() {
    for (node* p = start; p; p = p->next)
        printf("%d->", p->data);
    printf("NULL\n");
}

void main(int argc, char const* argv[]) {
    append(2);
    append(9);
    append(3);
    append(8);
    append(3);
    append(5);
    append(2);
    append(3);
    printlist();
    delete(3);
    printlist();
    swap(9);
    printlist();
}
