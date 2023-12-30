#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../boiler/getFileAsString.c"

typedef struct {
    char character;
    char *text;
} Digit;

char findFirstOrLastDigitInString(const char *string, bool reverse) {
    Digit digits[9] = {
        {'1', "one"},
        {'2', "two"},
        {'3', "three"},
        {'4', "four"},
        {'5', "five"},
        {'6', "six"},
        {'7', "seven"},
        {'8', "eight"},
        {'9', "nine"},
    };

    int i = reverse ? strlen(string) - 1 : 0;
    while (1) {
        for (int j = 0; j < 9; j++) {
            if (string[i] == digits[j].character || strncmp(string + i, digits[j].text, strlen(digits[j].text)) == 0) {
                return digits[j].character;
            }
        }
        reverse ? i-- : i++;
    }
}

int main() {
    char *buffer = getFileAsString("input.txt");
    int sum = 0;

    char *tok = strtok(buffer, "\n");
    while (tok) {
        char arr[3] = {
            findFirstOrLastDigitInString(tok, false),
            findFirstOrLastDigitInString(tok, true),
            '\0',
        };
        sum += atoi(arr);
        tok = strtok(NULL, "\n");
    }

    free(buffer);
    printf("%d\n", sum); // 52834

    return 0;
}
