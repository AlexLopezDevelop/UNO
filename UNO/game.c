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

// Turns
char gameTurns[MAXPLAYERSGAME][MAXCHAR];
int senseOfTurns = 0; // 0: clockwise, 1: counter-clock wise
int indexTurns = 0;

char optionSelected;

int GAME_player(char playerName[]) {

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
}


int GAME_turns() {

    switch (senseOfTurns) {
        case CLOCKWISE:

            indexTurns++; // Next turn

            if (indexTurns == gamePlayers.numBots) { // Check if last player array
                indexTurns = 0;
            }

            break;


        case COUNTERCLOCKWISE:



            break;
    }

    /*for (int i = 0; i < (gamePlayers.numBots + 1); i++) {
        printf("Name = %s\n", gameTurns[i]);
    }*/
}

int GAME_sort_turns() {

    for (int i = 0; i < gamePlayers.numBots; i++) {

        stpcpy(gameTurns[i], gamePlayers.bots[i].name);
    }

    stpcpy(gameTurns[gamePlayers.numBots], gamePlayers.player.name);

    char t[MAXCHAR];

    for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (strcmp(gameTurns[j - 1], gameTurns[j]) > 0) {
                strcpy(t, gameTurns[j - 1]);
                strcpy(gameTurns[j - 1], gameTurns[j]);
                strcpy(gameTurns[j], t);
            }
        }
    }
}

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

    GAME_deal_cards();

    GAME_sort_turns();

    return 1;
}

int GAME_start(char nameFilePLayer[], char nameFileBots[]) {

    if (GAME_configuration(nameFilePLayer, nameFileBots) == 0) {
        return 0;
    }

    char playerName[MAXCHAR];
    stpcpy(playerName, gamePlayers.player.name);

    Card cardInGame;
    Bot botPlaying;
    int findTurnBot = 0;

    do {

        cardInGame = gameStack.first->next->card; //Top card from stack

        if (strcmp(gamePlayers.player.name, gameTurns[indexTurns]) == 0) { // Player Turn

            GAME_player(playerName);

        } else { // Bots turn

            for (int i = 0; i < gamePlayers.numBots && findTurnBot == 0; i++) {

                if (strcmp(gamePlayers.bots[i].name, gameTurns[indexTurns]) == 0) { // Bot turn

                    botPlaying = gamePlayers.bots[i];

                    findTurnBot = 1; // Bot turn found
                }
            }

            // Play of the bot --------------------------- TODO: Make a function

            if (botPlaying.status == AGGRSSIVE) {

                for (int i = 0; i < botPlaying.cardsAvailable; i++) {

                    if (botPlaying.deck[i].number == 12 || botPlaying.deck[i].number == 14) { // Check if have +2 or +4

                    }
                }

            } else {

            }

            // End play of the bot -----------------------

            findTurnBot = 0; // Reset for next loop
        }

        GAME_turns(); // Change sense of the game TODO: IMPLEMENT


    } while (optionSelected != 'C'); // TODO: Change infinite loop for endGame flag

}