#include <stdio.h>
#define MAX 10000

int stack[MAX], min_stack[MAX], stack_len = 0, min_stack_len = 0;

void push(int a) {
    if (stack_len >= MAX)
        return;
    stack[stack_len++] = a;
    if (!min_stack_len || min_stack[min_stack_len - 1] >= a) {
        min_stack[min_stack_len++] = a;
    }
}

int pop() {
    if (stack_len <= 0)
        return -1;
    int top = stack[--stack_len];
    if (min_stack[min_stack_len - 1] == top)
        min_stack_len--;
    return top;
}

int get_min() {
    return min_stack[min_stack_len - 1];
}

int main() {
    int n = 0;
    while (n >= 0) {
        printf("1. Push\n2. Pop\n3. Get min\n4. Exit\nEnter option: ");
        scanf("%d", &n);
        switch (n) {
            case 1: {
                int a;
                printf("Enter num to be inserted: ");
                scanf("%d", &a);
                push(a);
                printf("Element %d inserted!\n", stack[stack_len - 1]);
                break;
            }
            case 2: {
                if (stack_len <= 0) {
                    printf("Stack underflow.\n");
                } else {
                    printf("Popped: %d\n", pop());
                }
                break;
            }
            case 3: {
                if (stack_len <= 0) {
                    printf("Stack underflow.\n");
                } else {
                    printf("Minimum element: %d\n", get_min());
                }
                break;
            }
            default: {
                n = -1;
                break;
            }
        }
    }
}
