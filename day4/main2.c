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

int getNumberOfScratchpads(char *cardsToken, char *winningCardsToken) {
    int card_worth = 0;

    IntList cards_list = getListOfInts(cardsToken);
    IntList winningCardsList = getListOfInts(winningCardsToken);

    for (int i = 0; i < cards_list.size; i++)
        if (isIntInList(cards_list.buffer[i], winningCardsList))
            card_worth++;

    return card_worth;
}

void setArrayOfIntsToOne(IntList *list, unsigned start) {
    for (int i = start; i < list->size; i++)
        list->buffer[i] = 1;
}

int main() {
    char *buffer = getFileAsString("input.txt");

    char *lineToken, *cardsToken, *winningCardsToken, *p1, *p2;
    IntList scorePerCard;
    size_t cardCounter;
    int scratchPads, totalScore;

    scorePerCard.size = 10;
    scorePerCard.buffer = malloc(scorePerCard.size * sizeof(int));
    setArrayOfIntsToOne(&scorePerCard, 0);

    scratchPads = totalScore = cardCounter = 0;

    lineToken = strtok_r(buffer, "\n", &p1);
    while (lineToken) {
        strtok_r(lineToken, ":", &p2);
        cardsToken = strtok_r(NULL, "|", &p2);
        winningCardsToken = strtok_r(NULL, "", &p2);

        scratchPads = getNumberOfScratchpads(cardsToken, winningCardsToken);
        for (int i = cardCounter+1; i < cardCounter+scratchPads+1; i++) {
            if (i >= scorePerCard.size) {
                scorePerCard.size *= 2;
                scorePerCard.buffer = realloc(scorePerCard.buffer, scorePerCard.size * sizeof(int));
                setArrayOfIntsToOne(&scorePerCard, i);
            }
            scorePerCard.buffer[i] += scorePerCard.buffer[cardCounter];
        }

        cardCounter++;
        lineToken = strtok_r(NULL, "\n", &p1);
    }

    for (int i = 0; i < cardCounter; i++)
        totalScore += scorePerCard.buffer[i];

    printf("%d\n", totalScore); // 12648035

    return 0;
}
