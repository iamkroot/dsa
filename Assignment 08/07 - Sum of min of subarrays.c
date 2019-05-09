#include <stdio.h>

int main() {
    int n = 0;
    scanf("%d", &n);
    int arr[n], left[n], right[n];
    int stack[n][2], stack_len = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (stack_len > 0 && stack[stack_len - 1][0] > arr[i]) {
            count += stack[stack_len - 1][1];
            stack_len--;
        }
        stack[stack_len][0] = arr[i];
        stack[stack_len++][1] = count;
        left[i] = count;
    }
    stack_len = 0;
    for (int i = n - 1; i >= 0; i--) {
        int count = 1;
        while (stack_len > 0 && stack[stack_len - 1][0] >= arr[i]) {
            count += stack[stack_len - 1][1];
            stack_len--;
        }
        stack[stack_len][0] = arr[i];
        stack[stack_len++][1] = count;
        right[i] = count;
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += arr[i] * left[i] * right[i];
    }
    printf("%d", res);
}
