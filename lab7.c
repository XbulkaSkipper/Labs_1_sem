#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1024

int is_valid_char(char c) {
    return (isalnum(c));
}

int main() {
    char input[MAX_LENGTH];
    printf("Введите строку: ");
    fgets(input, MAX_LENGTH, stdin);

    char *start = NULL;
    char *end = NULL;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(') {
            start = &input[i + 1];
        } else if (input[i] == ')') {
            if (start != NULL) {
                end = &input[i];
                *end = '\0';
                for (char *p = start; p != end; p++) {
                    if (!is_valid_char(*p)) {
                        start = NULL;
                        break;
                    }
                }
                if (start != NULL) {
                    printf("Найдено слово: %s\n", start);
                }
                *end = ')';
                start = NULL;
            }
        }
    }

    return 0;
}
