//
// Created by Alex Lopez on 2019-05-13.
//

#include "game.h"


int numbers[MAXNUMCARDS] = {0, 13, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
                //Num cards:1,  1,  1, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2

char colors[MAXCARDSCOLORS][9] = {"amarillo", "verde", "rojo", "azul"};

Card gameDeck[MAXCARDSGAMEDECK];

Player player;

Bot bots[MAXBOTSGAME]; // Array bots for game


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

int GAME_load_bots() {

}

int GAME_generate_stacks() {

    GAME_generate_main_stack();

    GAME_shuffle_main_stack();
}

int GAME_start() {

    GAME_generate_stacks();

    GAME_load_bots;

    CLI_game_first();

}