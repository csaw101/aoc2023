#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../boiler/getFileAsString.c"

typedef struct {
    int *buffer;
    size_t size;
} IntList;

IntList getListOfInts(char *tokens) {
    IntList list;
    int i;
    char *token, *p;
    size_t bufferSize;

    bufferSize = 10;
    list.buffer = malloc(bufferSize * sizeof(int));

    i = 0;
    token = strtok_r(tokens, " ", &p);
    while (token) {
        if (i >= bufferSize) {
            bufferSize *= 2;
            list.buffer = realloc(list.buffer, bufferSize * sizeof(int));
        }
        list.buffer[i] = atoi(token);
        token = strtok_r(NULL, " ", &p);
        i++;
    }
    list.size = i;

    return list;
}

bool isIntInList(int n, IntList list) {
    for (int i = 0; i < list.size; i++)
        if (n == list.buffer[i])
            return true;
    return false;
}

int getCardWorth(char *cardsToken, char *winningCardsToken) {
    int cardWorth = 0;

    IntList cardsList = getListOfInts(cardsToken);
    IntList winningCardsList = getListOfInts(winningCardsToken);

    for (int i = 0; i < cardsList.size; i++)
        if (isIntInList(cardsList.buffer[i], winningCardsList))
            cardWorth ? cardWorth *= 2 : (cardWorth = 1);

    return cardWorth;
}

int main() {
    char *buffer = getFileAsString("input.txt");

    char *lineToken, *cardsToken, *winningCardsToken, *p1, *p2;
    int totalWorth = 0;

    lineToken = strtok_r(buffer, "\n", &p1);
    while (lineToken) {
        strtok_r(lineToken, ":", &p2);
        cardsToken = strtok_r(NULL, "|", &p2);
        winningCardsToken = strtok_r(NULL, "", &p2);
        totalWorth += getCardWorth(cardsToken, winningCardsToken);

        lineToken = strtok_r(NULL, "\n", &p1);
    }

    printf("%d\n", totalWorth); // 20829

    return 0;
}
