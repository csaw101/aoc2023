#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../boiler/getFileAsString.c"

bool isDigit(char c) {
    return (c >= 48 && c <= 57) ? true : false;
}

char findFirstDigitInString(const char* string) {
    char c;

    int i = 0;
    do {
        c = string[i];
        i++;
    } while (!isDigit(c));

    return c;
}

char findLastDigitInString(const char* string) {
    char c;

    int i = strlen(string) - 1;
    do {
        c = string[i];
        i--;
    } while (!isDigit(c));

    return c;
}

int main() {
    char *buffer = getFileAsString("input.txt");

    int sum = 0, strLen;
    char a, b;

    char *tok = strtok(buffer, "\n");
    while (tok) {
        a = findFirstDigitInString(tok);
        b = findLastDigitInString(tok);

        char arr[3] = {a, b, '\0'};
        sum += atoi(arr);

        tok = strtok(NULL, "\n");
    }

    free(buffer);
    printf("%d\n", sum); // 53334

    return 0;
}
