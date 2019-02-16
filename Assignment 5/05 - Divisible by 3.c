#include <stdio.h>

void print_sorted(int freq[]) {
    for (int i = 9; i >= 0; i--) {
        while (freq[i]) {
            printf("%d", i);
            freq[i]--;
        }
    }
}

void remove_and_print(int rem, int freq[]) {
    // remove smallest and least possible digit(s) to make sum divisible by 3

    // 1, 4, 7 for rem=1
    // 2, 5, 8 for rem=2
    for (int i = rem; i < 10; i++) {
        if (i % 3 == rem && freq[i]) {
            freq[i]--;
            print_sorted(freq);
            return;
        }
    }

    // 2+2, 2+5, 5+5, 2+8, 5+8, 8+8 for rem=1
    // 1+1, 1+4, 4+4, 1+7, 4+7, 7+7 for rem=2
    for (int i = rem; i < 10; i++) {
        for (int j = 0; j <= i; j++) {
            if (i % 3 == 3 - rem && freq[i] && j % 3 == 3 - rem && freq[j]) {
                freq[i]--;
                freq[j]--;
                print_sorted(freq);
                return;
            }
        }
    }
}

int main(int argc, char const* argv[]) {
    int n;
    scanf("%d", &n);
    int freq[10] = {0}, sum = 0;
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        freq[a]++;
        sum += a;
    }
    switch (sum % 3) {
        case 0:
            print_sorted(freq);
            break;
        case 1:
            remove_and_print(1, freq);
            break;
        case 2:
            remove_and_print(2, freq);
            break;
    }
}
