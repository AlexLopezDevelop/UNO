//
// Created by Alex Lopez on 2019-05-13.
//

#include "game.h"
#include "stack.h"
#include "plist.h"

#include <ctype.h>

// -------------------------- Aux array -------------------------------- (Can be replaced directly by gameStack)
int numbers[MAXNUMCARDS] = {0, 13, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
                //Num cards:1,  1,  1, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2

char colors[MAXCARDSCOLORS][9] = {"amarillo", "verde", "rojo", "azul"};

Card gameDeck[MAXCARDSGAMEDECK];

// -------------------------- End Aux array --------------------------------

Stack gameStack;

GamePlayers gamePlayers;

int GAME_deal_cards() {

    gameStack = PLIST_create(); // Initialize with phantom node

    for (int i = 0; i < MAXCARDSGAMEDECK; i++) { // Transfer data from aux array to gameStack

        PLIST_insert(&gameStack, gameDeck[i]);
    }

    for (int j = 0; j < QUANTITYCARDSPLAYER; j++) { // Quantity cards for player

        gamePlayers.player.deck[j] = gameStack.first->next->card;
        PLIST_remove(&gameStack); // Remove card given to player
    }

    for (int k  = 0; k < gamePlayers.numBots; k++) { // Loop for each bot player

        for (int l = 0; l < gamePlayers.bots[k].cardsAvailable; l++) { // Loop for each available cards by bot

            gamePlayers.bots[k].deck[l] = gameStack.first->next->card;
            PLIST_remove(&gameStack);
        }
    }
}

int GAME_shuffle_main_stack() {

    Card temp;
    int j;

    for (int i = 0; i < MAXCARDSGAMEDECK; i++) {

        j = (rand()%MAXCARDSGAMEDECK);
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

int GAME_configuration(char nameFilePLayer[], char nameFileBots[]) {

    if (FILE_export_bots_config(nameFileBots,  &gamePlayers) == 0 ) { // Load bots conf
        return 0;
    }

    stpcpy(gamePlayers.player.name, FILE_get_player_name(nameFilePLayer)); // Add player name

    GAME_generate_stacks();

    return 1;
}

int GAME_start(char nameFilePLayer[], char nameFileBots[]) {

    if (GAME_configuration(nameFilePLayer, nameFileBots) == 0) {
        return 0;
    }

    GAME_deal_cards();

    char optionSelected;

    char playerName[MAXCHAR];
    stpcpy(playerName, gamePlayers.player.name);

    do {

        char a = CLI_game_first(playerName);
        optionSelected = toupper(a);


        switch (optionSelected) {

            case CLI_GAME_FIRST_SEE_HAND:

                CLI_game_second(playerName);

                break;


            case CLI_GAME_FIRST_STEAL_CARD:

                printf("\nB selected\n");

                break;
        }

    } while (optionSelected != 'C');

}