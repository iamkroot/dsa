#include <stdio.h>
#include <string.h>

void reverse(char str[], char rev[]) {
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        rev[i] = str[len - i - 1];
    rev[len] = '\0';
}

void encode(char str[]) {
    int len = strlen(str);
    char encoded[len];
    encoded[0] = '\0';
    int prev_space = -1;
    for (int i = 0, count = 0; i <= len; i++) {
        char c = str[i];
        char a;
        if ('a' <= c && c <= 'z')
            a = 'a';
        else if ('A' <= c && c <= 'Z')
            a = 'A';
        else {
            int n = prev_space >= 0 ? (i - prev_space - 1) : i;
            char substr[n + 1];
            strncpy(substr, str + prev_space + 1, n);
            substr[n] = '\0';
            char rev[n + 1];
            reverse(substr, rev);
            strcat(encoded, rev);
            strcat(encoded, " \0");
            prev_space = i;
            continue;
        }
        str[i] = count & 1 ? str[i] : ((c - a + 3) % 26) + a;
        count++;
    }
    encoded[strlen(encoded) - 1] = '\0';
    printf("%s", encoded);
}

void decode(char str[]) {
    int len = strlen(str);
    char decoded[len + 1];
    decoded[0] = '\0';
    int i = 0, substr_len = 0, count = 0;

    while (i < len) {
        substr_len = strcspn(str + i, " \0");
        char substr[substr_len + 1], rev[substr_len + 1];
        substr[substr_len] = '\0';
        strncpy(substr, str + i, substr_len);
        reverse(substr, rev);
        strcat(decoded, rev);
        strcat(decoded, " \0");
        i += substr_len + 1;
    }
    decoded[strlen(decoded) - 1] = '\0';
    for (int i = 0; i < strlen(decoded); i++) {
        char ch = decoded[i];
        char a;
        if ('a' <= ch && ch <= 'z')
            a = 'a';
        else if ('A' <= ch && ch <= 'Z')
            a = 'A';
        else
            continue;
        decoded[i] = count & 1 ? decoded[i] : ((ch - a - 3) % 26) + a;
        count++;
    }
    printf("%s\n", decoded);
}

void main(int argc, char const* argv[]) {
    char str[100];
    scanf("%99[^\n]", str);
    encode(str);
    // decode(str);
}
