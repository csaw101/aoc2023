#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../boiler/getFileAsString.c"

int parseNumber(char *line, int i) {
    int start, end;
    char *numberString;

    while (i != -1 && isdigit(line[i])) i--;
    start = i + 1;

    end = start;
    while (isdigit(line[end])) end++;

    size_t strLen = (end - start) * sizeof(char) + 1;

    numberString = malloc(strLen);
    strncpy(numberString, line+start, strLen-1);
    numberString[strLen-1] = '\0';
    int n = atoi(numberString);

    free (numberString);

    return n;
}

void insertNumber(unsigned *twoNumbers, int n) {
    if (twoNumbers[0] == 0)
        twoNumbers[0] = n;
    else if (twoNumbers[1] == 0)
        twoNumbers[1] = n;
}

void getNewPartNumber(char *line, int i, unsigned *partNumberPerGear, unsigned *twoNumbers) {
    if (i >= 0 && i < strlen(line) && isdigit(line[i])) {
        (*partNumberPerGear)++;
        insertNumber(twoNumbers, parseNumber(line, i));
    }
}

void checkLineForPartNumber(char *line, int i, unsigned *partNumberPerGear, unsigned *twoNumbers) {
    if (line && line[i] == '.') {
        getNewPartNumber(line, i - 1, partNumberPerGear, twoNumbers);
        getNewPartNumber(line, i + 1, partNumberPerGear, twoNumbers);
    } else {
        getNewPartNumber(line, i, partNumberPerGear, twoNumbers);
    }
}

int main() {
    char *buffer, *token;
    int sum = 0;
    char* square[3] = { 0 };

    unsigned partNumberPerGear = 0;
    unsigned twoNumbers[2] = { 0 };

    buffer = getFileAsString("input.txt");

    token = strtok(buffer, "\n");
    square[2] = strdup(token);
    token = strtok(NULL, "\n");
    while (square[2]) {
        if (square[1]) square[0] = strdup(square[1]);
        if (square[2]) square[1] = strdup(square[2]);
        if (token)
            square[2] = strdup(token);
        else
            square[2] = NULL;

        for (int i = 0; i < strlen(square[1]); i++) {
            if (square[1][i] == '*') {
                // numbers on the left and right
                getNewPartNumber(square[1], i - 1, &partNumberPerGear, twoNumbers);
                getNewPartNumber(square[1], i + 1, &partNumberPerGear, twoNumbers);

                // numbers above the star then numbers below the star
                checkLineForPartNumber(square[0], i, &partNumberPerGear, twoNumbers);
                checkLineForPartNumber(square[2], i, &partNumberPerGear, twoNumbers);

                if (partNumberPerGear == 2) {
                    sum += twoNumbers[0] * twoNumbers[1];
                }

                twoNumbers[0] = twoNumbers[1] = partNumberPerGear = 0;
            }
        }
        token = strtok(NULL, "\n");
    }

    printf("%d\n", sum); // 79842967

    return 0;
}
