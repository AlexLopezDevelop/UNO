//
// Created by Alex Lopez on 2019-05-13.
//

#include "game.h"

#include <ctype.h>


int numbers[MAXNUMCARDS] = {0, 13, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
                //Num cards:1,  1,  1, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2

char colors[MAXCARDSCOLORS][9] = {"amarillo", "verde", "rojo", "azul"};

Card gameDeck[MAXCARDSGAMEDECK];

GamePlayers gamePlayers;


int GAME_shuffle_main_stack() {

    Card temp;
    int j;

    for (int i = 0; i < MAXCARDSGAMEDECK; i++) {

        j = (rand()%MAXCARDSGAMEDECK) + 1;
        temp = gameDeck[i];
        gameDeck[i] = gameDeck[j];
        gameDeck[j] = temp;
    }
}

int GAME_generate_main_stack() {

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

    GAME_generate_main_stack();

    GAME_shuffle_main_stack();
}

int GAME_configuration(char nameFileBots[]) {

    if (FILE_export_bots_config(nameFileBots, gamePlayers) == 0 ) { // Load bots conf
        return 0;
    }

    GAME_generate_stacks();

    return 1;
}

int GAME_start(char nameFileBots[]) {

    if (GAME_configuration(nameFileBots) == 0) {
        return 0;
    }

    char optionSelected;

    do {

        optionSelected = toupper(CLI_game_first());
        printf("Selected: %c\n", optionSelected);

        switch (optionSelected) {

            case 'A':

                printf("\nA selected\n");

                break;


            case CLI_GAME_FIRST_STEAL_CARD:

                printf("\nA selected\n");

                break;
        }

    } while (optionSelected != 'C');

}