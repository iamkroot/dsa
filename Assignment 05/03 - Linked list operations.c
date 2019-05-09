#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;

node *head = NULL, *tail = NULL;

node* newnode(int a) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = a;
    new_node->next = new_node->prev = NULL;
    return new_node;
}

void append(int a) {
    node* new_node = newnode(a);
    if (tail) {
        tail->next = new_node;
    }
    new_node->prev = tail;
    tail = new_node;
    if (!head)
        head = new_node;
}

void print_list(node* head) {
    for (node* p = head; p; p = p->next) {
        printf("%d", p->data);
        printf(p->next ? " " : "\n");
    }
}

void insert(int a) {
    node* new_node = newnode(a);
    node *p = head, *pp = NULL;
    while (p && p->data <= a) {
        pp = p;
        p = p->next;
    }
    new_node->prev = pp;
    if (pp)
        pp->next = new_node;
    else
        head = new_node;

    new_node->next = p;
    if (p)
        p->prev = new_node;
    else
        tail = new_node;
}

void delete (int a) {
    node* p = head;
    while (p && p->data != a) {
        p = p->next;
    }
    if (!p) {
        printf("%d not in list.\n", a);
        return;
    }
    if (p->prev) {
        p->prev->next = p->next;
    } else
        head = p->next;
    if (p->next)
        p->next->prev = p->prev;
    else
        tail = p->prev;

    free(p);
}

void swap(int a, int b) {
    node *i = NULL, *j = NULL, *p = head;
    while (p) {
        if (p->data == a)
            i = p;
        if (p->data == b)
            j = p;
        if (i && j)
            break;
        p = p->next;
    }
    if (!i) {
        printf("%d not in list.\n", a);
        return;
    }
    if (!j) {
        printf("%d not in list.\n", b);
        return;
    }
    if (i->prev)
        i->prev->next = j;
    else
        head = j;
    if (i->next)
        i->next->prev = j;
    else
        tail = j;

    if (j->prev)
        j->prev->next = i;
    else
        head = i;
    if (j->next)
        j->next->prev = i;
    else
        tail = i;
    node* t = j->prev;
    j->prev = i->prev;
    i->prev = t;
    t = j->next;
    j->next = i->next;
    i->next = t;
}

node* split_half(node* start) {
    node *fast = start, *slow = start;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    node* temp = slow->next;
    slow->next = NULL;
    return temp;
}

node* merge(node* first, node* second) {
    if (!first)
        return second;
    if (!second)
        return first;
    if (first->data < second->data) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        if (!second->next && second->data > tail->data)
            tail = second;
        return first;
    } else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        if (!second->next && second->data > tail->data)
            tail = second;
        return second;
    }
}

node* merge_sort(node* start) {
    if (!start || !start->next) {
        return start;
    }
    node* second = split_half(start);
    start = merge_sort(start);
    second = merge_sort(second);
    return merge(start, second);
}

int main(int argc, char const* argv[]) {
    int a;
    char c;
    do {
        scanf("%d%c", &a, &c);
        append(a);
    } while (c != '\n');
    int n;
    scanf("%d", &n);
    while (n--) {
        char s[3];
        int i, j;
        scanf("%s", s);
        switch (s[0]) {
            case 'I':
                scanf("%d", &i);
                insert(i);
                break;
            case 'D':
                scanf("%d", &i);
                delete (i);
                break;
            case 'S': {
                scanf("%c", &c);
                if (c == '\n')
                    head = merge_sort(head);
                else {
                    scanf("%d %d", &i, &j);
                    swap(i, j);
                }
                break;
            }
        }
        print_list(head);
    }
}
