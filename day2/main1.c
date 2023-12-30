#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../boiler/getFileAsString.c"

typedef struct {
    unsigned id;
    unsigned red;
    unsigned green;
    unsigned blue;
} Bag, Game;

Game getCubesForGame(char *gameString) {
    char *ptr, *token;
    Game game = { 0 }; // should I intitialize to zero, and is this the proper way
    int cubes;

    char *cpy = malloc(strlen(gameString) + 1);
    strcpy(cpy, gameString);

    token = strtok_r(cpy, " ", &ptr);
    token = strtok_r(NULL, ":", &ptr);
    game.id = atoi(token);

    token = strtok_r(NULL, " ", &ptr);
    while (token) {
        if (isdigit(token[0])) {
            cubes = atoi(token);
        } else if (strncmp(token, "blue", 4) == 0) {
            if (game.blue < cubes)
                game.blue = cubes;
        } else if (strncmp(token, "red", 3) == 0) {
            if (game.red < cubes)
                game.red = cubes;
        } else if (strncmp(token, "green", 5) == 0) {
            if (game.green < cubes)
                game.green = cubes;
        }

        token = strtok_r(NULL, " ", &ptr);
    }

    return game;
}

int main() {
    char *buffer = getFileAsString("input.txt");
    Bag bag = { 0, 12, 13, 14 };
    Game game;

    unsigned sum = 0;
    char *ptr;

    char *token = strtok_r(buffer, "\n", &ptr);
    while (token) {
        game = getCubesForGame(token);
        if (game.blue <= bag.blue && game.red <= bag.red && game.green <= bag.green)
            sum += game.id;
        token = strtok_r(NULL, "\n", &ptr);
    }

    printf("%d\n", sum);

    return 0;
}
