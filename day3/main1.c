#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../boiler/getFileAsString.c"

bool isSymbol(char c) {
    if (c == '.' || isdigit(c))
        return false;
    return true;
}

bool symbolAdjacent(char *line, int i) {
    if (line && (
        isSymbol(line[i]) ||
        ((i - 1) >= 0 && isSymbol(line[i - 1])) ||
        (i + 1) < strlen(line) && isSymbol(line[i+1])
    ))
        return true;
    return false;
}

bool symbolNextTo(char *line, int i) {
    if (
        (i-1 >= 0) && isSymbol(line[i-1]) ||
        (i+1 < strlen(line) && isSymbol(line[i+1]))
    )
        return true;
    return false;
}

int parseNumber(char *line, int i) {
    int start, end;
    char *numberString;

    while (i != -1 && isdigit(line[i])) {
        i--;
    }
    start = i + 1;

    end = start;
    while (isdigit(line[end])) {
        end++;
    }

    size_t strLen = (end - start) * sizeof(char) + 1;

    numberString = malloc(strLen);
    strncpy(numberString, line+start, strLen-1);
    numberString[strLen-1] = '\0';
    int n = atoi(numberString);

    free (numberString);

    return n;
}

int main() {
    char *buffer, *token, *ptr;
    int n = 0, sum = 0;
    char* square[3] = { 0 };

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
            if (isdigit(square[1][i])) {
                if (symbolAdjacent(square[0], i) ||
                    symbolAdjacent(square[2], i) ||
                    symbolNextTo(square[1], i)
                    ) {
                    sum += parseNumber(square[1], i);
                    while (isdigit(square[1][i])) i++;
                }
            }
        }

        token = strtok(NULL, "\n");
    }

    printf("%d\n", sum); // 532445
    return 0;
}
