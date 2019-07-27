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

Card cardInGame;

// Turns
char gameTurns[MAXPLAYERSGAME][MAXCHAR];
int senseOfTurns = 0; // 0: clockwise, 1: counter-clock wise
int indexTurns = 0;

char optionSelected;

int GAME_remove_bot_card(Bot * bot, int index) {

    Card deckAux[MAXDECK];

    int n = 0;

    for (int i = 0; i < bot->cardsAvailable; i++) {

        if (i == index) {


        } else {

            deckAux[n].number = bot->deck[i].number;
            strcpy(deckAux[n].color, bot->deck[i].color);

            n++;

        }
    }

    //Add auxDeck to player deck
    for (int i = 0; i < n; i++) {
        bot->deck[i].number = deckAux[i].number;
        strcpy(bot->deck[i].color, deckAux[i].color);
    }

    bot->cardsAvailable = n; // Decrement cards

    //Check new player deck
    /*for (int i = 0; i < n; i++) {
        printf("%d) Numero: %d - Color: %s \n", i, player->deck[i].number, player->deck[i].color);
    }*/


}

int GAME_remove_player_card(Player * player, int index) {

    Card deckAux[MAXDECK];

    int n = 0;

    for (int i = 0; i < player->cardsAvailable; i++) {

        if (i == index) {


        } else {

            deckAux[n].number = player->deck[i].number;
            strcpy(deckAux[n].color, player->deck[i].color);

            n++;

        }
    }

    //Add auxDeck to player deck
    for (int i = 0; i < n; i++) {
        player->deck[i].number = deckAux[i].number;
        strcpy(player->deck[i].color, deckAux[i].color);
    }

    player->cardsAvailable = n; // Decrement cards

    //Check new player deck
    /*for (int i = 0; i < n; i++) {
        printf("%d) Numero: %d - Color: %s \n", i, player->deck[i].number, player->deck[i].color);
    }*/


}

int GAME_player_steel_card() {

    gamePlayers.player.cardsAvailable = gamePlayers.player.cardsAvailable + 1; // Increment deck player counter

    gamePlayers.player.deck[gamePlayers.player.cardsAvailable] = gameStack.first->next->card; // Insert top card from game stack to player deck

    PLIST_remove(&gameStack); // Delete card from game stack
}

int GAME_bot(Bot * bot) {

    int noCardFound = 1; // Check if the bot can throw some card

    /*if (botPlaying.status == AGGRSSIVE) {

        for (int i = 0; i < botPlaying.cardsAvailable; i++) {

            if (botPlaying.deck[i].number == 12 || botPlaying.deck[i].number == 14) { // Check if have +2 or +4

            }
        }

    } else {

    }*/

    for (int i = 0; i < bot->cardsAvailable; i++) {

        if (bot->deck[i].number == cardInGame.number ) {

            cardInGame = bot->deck[i]; // Replace game card for bot card thrown

            //Remove card form bot deck
            GAME_remove_bot_card(&bot, i);


            noCardFound = 0;

        } else if (strcmp(bot->deck[i].color, cardInGame.color) == 0) {

            cardInGame = bot->deck[i]; // Replace game card for bot card thrown

            //Remove card form bot deck
            GAME_remove_bot_card(&bot, i);

            noCardFound = 0;

        }
    }

    if (noCardFound == 1) {

        bot->cardsAvailable = bot->cardsAvailable + 1; // Increment bot deck counter

        bot->deck[bot->cardsAvailable] = gameStack.first->card; // Insert top card from game stack to bot deck

        PLIST_remove(&gameStack); // Delete card from game stack
    }

}

int GAME_player(char playerName[]) {

    int continueGame = 0;

    while (continueGame == 0) {


        printf("\nCarta en juego: %d - %s \n\n", cardInGame.number, cardInGame.color);

        char response = CLI_game_first(playerName);
        optionSelected = toupper(response);

        switch (optionSelected) {

            case CLI_GAME_FIRST_SEE_HAND:

                // Print hand
                for (int i = 0; i < gamePlayers.player.cardsAvailable; i++) {
                    printf("%d) Numero: %d - Color: %s \n", i, gamePlayers.player.deck[i].number,
                           &gamePlayers.player.deck[i].color);
                }

                char response = CLI_game_second(playerName);
                optionSelected = toupper(response);

                switch (optionSelected) {

                    case CLI_GAME_SECOND_PLAY_CARD:

                        printf("\n ¿Qué carta quieres jugar? ");

                        //User selected card
                        char str_option[5];

                        fgets(str_option, 5, stdin);
                        str_option[strlen(str_option) - 1] = '\0';

                        int userCardPlay = atoi(str_option);


                        //Check if the user can trow TODO: Create function (duplicated content)
                        if (cardInGame.number == gamePlayers.player.deck[userCardPlay].number) {

                            PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                            cardInGame = gamePlayers.player.deck[userCardPlay]; // Change cardInGame

                            GAME_remove_player_card(&gamePlayers.player, userCardPlay);

                            continueGame = 1; //Exit from loop to continue playing

                        } else if (strcmp(cardInGame.color, gamePlayers.player.deck[userCardPlay].color) == 0) {

                            PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                            cardInGame = gamePlayers.player.deck[userCardPlay]; // Change cardInGame

                            GAME_remove_player_card(&gamePlayers.player, userCardPlay);

                            continueGame = 1;

                        } else {

                            printf("\nEsta carta no se puede jugar\n");
                        }

                        break;

                    case CLI_GAME_SECOND_STEAL_CARD:

                        GAME_player_steel_card();

                        break;

                }

                break;


            case CLI_GAME_FIRST_STEAL_CARD:

                GAME_player_steel_card();

                break;
        }
    }
}


int GAME_turns() {

    switch (senseOfTurns) {
        case CLOCKWISE:

            indexTurns++; // Next turn

            if (indexTurns == MAXPLAYERSGAME) { // Check if last player array
                indexTurns = 0;
            }

            break;


        case COUNTERCLOCKWISE:

            // TODO: Change game direction

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

    for (int i = 1; i < MAXPLAYERSGAME; i++) {
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

    gamePlayers.player.cardsAvailable = QUANTITYCARDSPLAYER; // Set the quantity cards

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

    Bot botPlaying;
    int findTurnBot = 0;

    int validCard = 0;

    while (validCard == 0) {

        if (gameStack.first->next->card.number >= 0 &&
            gameStack.first->next->card.number <= 9) { // Check if it's a valid card for start

            cardInGame = gameStack.first->next->card; //Top card from stack

            validCard = 1; // Exit loop

        } else { // No valid card

            PLIST_insert(&gameStack, gameStack.first->next->card); // Add card to bottom game stack

            PLIST_remove(&gameStack); // Remove card

        }

    }

    do {

        if (strcmp(gamePlayers.player.name, gameTurns[indexTurns]) == 0) { // Player Turn

            GAME_player(playerName);

        } else { // Bots turn

            for (int i = 0; i < gamePlayers.numBots && findTurnBot == 0; i++) { // Loop for find and get bot info

                if (strcmp(gamePlayers.bots[i].name, gameTurns[indexTurns]) == 0) { // Bot turn

                    botPlaying = gamePlayers.bots[i];

                    findTurnBot = 1; // Bot turn found
                }
            }

            GAME_bot(&botPlaying);

            // End play of the bot -----------------------

            findTurnBot = 0; // Reset for next loop
        }

        GAME_turns(); // Change sense of the game TODO: IMPLEMENT


    } while (optionSelected != 'C'); // TODO: Change infinite loop for endGame flag

}