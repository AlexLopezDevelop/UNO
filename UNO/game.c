//
// Created by Alex Lopez on 2019-05-13.
//

#include "game.h"


char colors[MAXCARDSCOLORS][9] = {"amarillo", "verde", "rojo", "azul"};

int numbers[MAXNUMCARDS] = {0, 13, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
                //Num cards:1,  1,  1, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2

Card gameDeck[MAXCARDSGAMEDECK];

Player player;

int GAME_generate_game_stacks() {

        int cardIndex = 0;

        for (int i = 0; i < MAXCARDSCOLORS; i++) { // Load cards with colors, Ex. Yellow

            for (int j = 0; j < MAXNUMCARDS; j++) { // Load cards one by one

                if (j == 0 || j == 1 || j == 2) { // Cards with one type: 0 to 2

                    gameDeck[cardIndex].number = numbers[j];
                    strcpy(gameDeck[cardIndex].color, colors[i]);

                    cardIndex++;

                } else { // Cards with two type: 1 to 12

                    for (int k = 0; k < 2; k++) {

                        gameDeck[cardIndex].number = numbers[j];
                        strcpy(gameDeck[cardIndex].color, colors[i]);

                        cardIndex++; // We need these aux because j index not change value after exit from switch
                    }
                }
            }
        }
}

int GAME_generate_stacks() {

    GAME_generate_game_stacks();

    for (int i = 0; i < 108; i++) { // Print cards loaded
        printf("%s: %d\n", gameDeck[i].color, gameDeck[i].number);
    }

}

int GAME_start() {

    GAME_generate_stacks();

    CLI_game_first();

}