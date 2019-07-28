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

int GAME_bot_steel_card(Bot * bot) {

    bot->cardsAvailable = bot->cardsAvailable + 1; // Increment bot deck counter

    bot->deck[bot->cardsAvailable] = gameStack.first->card; // Insert top card from game stack to bot deck

    PLIST_remove(&gameStack); // Delete card from game stack
}

int GAME_player_steel_card() {

    gamePlayers.player.cardsAvailable = gamePlayers.player.cardsAvailable + 1; // Increment deck player counter

    gamePlayers.player.deck[gamePlayers.player.cardsAvailable] = gameStack.first->next->card; // Insert top card from game stack to player deck

    PLIST_remove(&gameStack); // Delete card from game stack
}

int GAME_bot(Bot * bot) { // TODO: Create a function in thrown action (Duplicated content)

    int cardFound = 0; // Check if the bot can throw some card
    int countYellow = 0;
    int countGreen = 0;
    int countRed = 0;
    int countBlue = 0;
    char maxColor[15];


    for (int i = 0; i < bot->cardsAvailable; i++) { // Count colors

        if (strcmp(bot->deck[i].color, "amarillo") == 0) {

        } else if (strcmp(bot->deck[i].color, "amarillo") == 0) {

            countYellow++;

        } else if (strcmp(bot->deck[i].color, "verde") == 0) {

            countGreen++;

        } else if (strcmp(bot->deck[i].color, "rojo") == 0) {

            countRed++;

        } else if (strcmp(bot->deck[i].color, "azul") == 0) {

            countBlue++;

        }

    }

    if (countYellow > countGreen) {
        if(countYellow > countRed) {
            if (countYellow > countBlue) {
                strcpy(maxColor, "amarillo");
            } else {
                strcpy(maxColor, "azul");
            }
        } else {
            if (countRed > countBlue) {
                strcpy(maxColor, "rojo");
            } else {
                //blue
            }
        }
    } else {
        if (countGreen > countRed) {
            if (countGreen > countBlue) {
                strcpy(maxColor, "verde");
            } else {
                strcpy(maxColor, "azul");
            }
        } else {
            if (countRed > countBlue) {
                strcpy(maxColor, "rojo");
            } else {
                strcpy(maxColor, "azul");
            }
        }
    }


    for (int i = 0; i < bot->cardsAvailable && cardFound == 0; i++) { // Check if have 0

        if (bot->deck[i].number == 0 ) {

            if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                strcpy(cardInGame.color, ""); // Reset color to put in the deck

            }

            PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

            cardInGame = bot->deck[i]; // Replace game card for bot card thrown


            //Remove card form bot deck
            GAME_remove_bot_card(&bot, i);


            cardFound = 1;

        }

    }

    if (cardFound == 0) { // Now check if have the same color

        for (int j = 0; j < bot->cardsAvailable && cardFound == 0; j++) {

            if (strcmp(bot->deck[j].color, cardInGame.color) == 0) {

                if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                    strcpy(cardInGame.color, ""); // Reset color to put in the deck

                }

                PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                cardInGame = bot->deck[j]; // Replace game card for bot card thrown

                //Remove card form bot deck
                GAME_remove_bot_card(&bot, j);

                cardFound = 1;

            }

        }
    }

    if (cardFound == 0) { // Agressive thrown joker after check colors

        if (bot->status == AGGRSSIVE) {

            for (int l = 0; l < bot->cardsAvailable && cardFound == 0; l++) {

                if (bot->deck[l].number == 13 || bot->deck[l].number == 14) {

                    if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                        strcpy(cardInGame.color, ""); // Reset color to put in the deck

                    }

                    PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                    strcpy(bot->deck[l].color, maxColor); // Add color

                    cardInGame = bot->deck[l]; // Replace game card for bot card thrown

                    //Remove card form bot deck
                    GAME_remove_bot_card(&bot, l);

                    cardFound = 1;

                }
            }
        }
    }

    if (cardFound == 0) { // Now check if have the same number

        for (int k = 0; k < bot->cardsAvailable && cardFound == 0; k++) {

            if (bot->deck[k].number == cardInGame.number ) {

                if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                    strcpy(cardInGame.color, ""); // Reset color to put in the deck

                }

                PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                cardInGame = bot->deck[k]; // Replace game card for bot card thrown

                //Remove card form bot deck
                GAME_remove_bot_card(&bot, k);


                cardFound = 1;

            }

        }
    }

    if (bot->status != AGGRSSIVE) { // Agressive joker checked before

        if (cardFound == 0) { // Play some joker card

            for (int l = 0; l < bot->cardsAvailable && cardFound == 0; l++) {

                if (bot->deck[l].number == 13 || bot->deck[l].number == 14) {

                    if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                        strcpy(cardInGame.color, ""); // Reset color to put in the deck

                    }

                    PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                    strcpy(bot->deck[l].color, maxColor); // Add color

                    cardInGame = bot->deck[l]; // Replace game card for bot card thrown

                    //Remove card form bot deck
                    GAME_remove_bot_card(&bot, l);

                    cardFound = 1;

                }
            }
        }
    }

    if (cardFound == 0) { // Steel card if no have card

        GAME_bot_steel_card(&bot);

        // Check if the stolen card can be thrown
        if (bot->deck[bot->cardsAvailable].number == cardInGame.number) {

            if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                strcpy(cardInGame.color, ""); // Reset color to put in the deck

            }


            PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

            cardInGame = bot->deck[bot->cardsAvailable]; // Replace game card for bot card thrown

            //Remove card form bot deck
            GAME_remove_bot_card(&bot, bot->cardsAvailable);


        } else if (strcmp(bot->deck[bot->cardsAvailable].color, cardInGame.color)) {

            if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                strcpy(cardInGame.color, ""); // Reset color to put in the deck

            }

            PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

            cardInGame = bot->deck[bot->cardsAvailable]; // Replace game card for bot card thrown

            //Remove card form bot deck
            GAME_remove_bot_card(&bot, bot->cardsAvailable);

        } else { // Check if it's agressive & can thrown joker card

            if (bot->status == AGGRSSIVE) {

                if (bot->deck[bot->cardsAvailable].number == 13 || bot->deck[bot->cardsAvailable].number == 14) {

                    if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                        strcpy(cardInGame.color, ""); // Reset color to put in the deck

                    }

                    PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                    strcpy(bot->deck[bot->cardsAvailable].color, maxColor); // Add color

                    cardInGame = bot->deck[bot->cardsAvailable]; // Replace game card for bot card thrown

                    //Remove card form bot deck
                    GAME_remove_bot_card(&bot, bot->cardsAvailable);

                }

            }

        }

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
                    if (gamePlayers.player.deck[i].number == cardInGame.number || strcmp(gamePlayers.player.deck[i].color, cardInGame.color) == 0) { // Show card available to play

                        printf("%d) Numero: %d - Color: %s   *\n", i, gamePlayers.player.deck[i].number,
                               &gamePlayers.player.deck[i].color);

                    } else if (gamePlayers.player.deck[i].number == 13 || gamePlayers.player.deck[i].number == 14) { // Change color, +4

                        printf("%d) Numero: %d - Color: %s   *\n", i, gamePlayers.player.deck[i].number,
                               &gamePlayers.player.deck[i].color);

                    } else {

                        printf("%d) Numero: %d - Color: %s \n", i, gamePlayers.player.deck[i].number,
                               &gamePlayers.player.deck[i].color);
                    }
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

                            if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                                strcpy(cardInGame.color, ""); // Reset color to put in the deck

                            }

                            PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                            cardInGame = gamePlayers.player.deck[userCardPlay]; // Change cardInGame

                            GAME_remove_player_card(&gamePlayers.player, userCardPlay);

                            continueGame = 1; //Exit from loop to continue playing

                        } else if (strcmp(cardInGame.color, gamePlayers.player.deck[userCardPlay].color) == 0) {

                            if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                                strcpy(cardInGame.color, ""); // Reset color to put in the deck

                            }

                            PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                            cardInGame = gamePlayers.player.deck[userCardPlay]; // Change cardInGame

                            GAME_remove_player_card(&gamePlayers.player, userCardPlay);

                            continueGame = 1;

                        } else if (gamePlayers.player.deck[userCardPlay].number == 13 || gamePlayers.player.deck[userCardPlay].color == 14) { // Change color, +4

                            int correctColor = 0;

                            while (correctColor == 0) {

                            printf("\n¿Que color quiere cambiar?\n");

                            //User selected card
                            char str_option[15];

                            fgets(str_option, 5, stdin);
                            str_option[strlen(str_option) - 1] = '\0';

                            for (int i = 0; str_option[i]; i++) { // Lower case
                                str_option[i] = tolower(str_option[i]);
                            }

                            for (int j = 0; j < 4; j++) {

                                if (strcmp(str_option, colors[j]) == 0) {

                                    strcpy(gamePlayers.player.deck[userCardPlay].color,
                                           str_option); // Add color to change color card

                                    correctColor = 1;

                                } else {

                                    printf("\nColor incorrecto\n");

                                }
                            }
                        }

                        }else {

                            printf("\nEsta carta no se puede jugar\n");
                        }

                        break;

                    case CLI_GAME_SECOND_STEAL_CARD:

                        GAME_player_steel_card();

                        int end = 0;

                        // Check if can throw the steal card
                        if (cardInGame.number == gamePlayers.player.deck[gamePlayers.player.cardsAvailable].number){

                             // TODO: Create a function (duplicated content)
                            while (end == 0) {

                                printf("\nSe ha robado un %d %s. ¿Deseas jugarlo? [s/n]\n",
                                       gamePlayers.player.deck[gamePlayers.player.cardsAvailable].number,
                                       gamePlayers.player.deck[gamePlayers.player.cardsAvailable].color);

                                fgets(str_option, 5, stdin);
                                str_option[strlen(str_option) - 1] = '\0';

                                if (strcmp(tolower(str_option[0]), "s") == 0) { // throw steal card

                                    if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                                        strcpy(cardInGame.color, ""); // Reset color to put in the deck

                                    }

                                    PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                                    cardInGame = gamePlayers.player.deck[gamePlayers.player.cardsAvailable]; // Change cardInGame

                                    GAME_remove_player_card(&gamePlayers.player, gamePlayers.player.cardsAvailable);

                                    continueGame = 1;

                                    end = 1;

                                } else if (strcmp(tolower(str_option[0]), "n") == 0) {

                                    end = 1;

                                } else {

                                    printf("\nRespuesta incorrecta\n");

                                }
                            }

                        } else if (strcmp(cardInGame.color, gamePlayers.player.deck[gamePlayers.player.cardsAvailable].color)) {

                            while (end == 0) {

                                printf("\nSe ha robado un %d %s. ¿Deseas jugarlo? [s/n]\n",
                                       gamePlayers.player.deck[gamePlayers.player.cardsAvailable].number,
                                       gamePlayers.player.deck[gamePlayers.player.cardsAvailable].color);

                                fgets(str_option, 5, stdin);
                                str_option[strlen(str_option) - 1] = '\0';

                                if (strcmp(tolower(str_option[0]), "s") == 0) { // throw steal card

                                    if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                                        strcpy(cardInGame.color, ""); // Reset color to put in the deck

                                    }

                                    PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                                    cardInGame = gamePlayers.player.deck[gamePlayers.player.cardsAvailable]; // Change cardInGame

                                    GAME_remove_player_card(&gamePlayers.player, gamePlayers.player.cardsAvailable);

                                    continueGame = 1;

                                    end = 1;

                                } else if (strcmp(tolower(str_option[0]), "n") == 0) {

                                    end = 1;

                                } else {

                                    printf("\nRespuesta incorrecta\n");

                                }
                            }

                        } else if (gamePlayers.player.deck[gamePlayers.player.cardsAvailable].number == 13 || gamePlayers.player.deck[gamePlayers.player.cardsAvailable].number == 14) {

                            while (end == 0) {

                                printf("\nSe ha robado un %d %s. ¿Deseas jugarlo? [s/n]\n",
                                       gamePlayers.player.deck[gamePlayers.player.cardsAvailable].number,
                                       gamePlayers.player.deck[gamePlayers.player.cardsAvailable].color);

                                fgets(str_option, 5, stdin);
                                str_option[strlen(str_option) - 1] = '\0';

                                if (strcmp(tolower(str_option[0]), "s") == 0) { // throw steal card

                                    if (cardInGame.number = 13 || cardInGame.number == 14) { // Check if it's card change color

                                        strcpy(cardInGame.color, ""); // Reset color to put in the deck

                                    }

                                    PLIST_insert(&gameStack, cardInGame); // Add the card to bottom deckGame

                                    cardInGame = gamePlayers.player.deck[gamePlayers.player.cardsAvailable]; // Change cardInGame

                                    GAME_remove_player_card(&gamePlayers.player, gamePlayers.player.cardsAvailable);

                                    continueGame = 1;

                                    end = 1;

                                } else if (strcmp(tolower(str_option[0]), "n") == 0) {

                                    end = 1;

                                } else {

                                    printf("\nRespuesta incorrecta\n");

                                }
                            }

                        } else {

                            printf("\nSe ha robado un %d %s. No se puede jugar\n", gamePlayers.player.deck[gamePlayers.player.cardsAvailable].number, gamePlayers.player.deck[gamePlayers.player.cardsAvailable].color);

                        }

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

            if (indexTurns == MAXPLAYERSGAME) { // Check if it's the last player of array
                indexTurns = 0;
            } else {
                indexTurns++; // Next turn
            }

            break;


        case COUNTERCLOCKWISE:

            if (indexTurns == 0) { // Check if it's the first player of array
                indexTurns = MAXPLAYERSGAME;
            } else {
                indexTurns--; // Next turn
            }

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

    stpcpy(gameTurns[MAXPLAYERSGAME-1], gamePlayers.player.name);

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
    int endGame = 0;

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

        for (int i  = 0; i < MAXPLAYERSGAME; i++) {
            if (indexTurns == i) {
                printf("%s  V\n", gameTurns[i]);
            } else {
                printf("%s\n", gameTurns[i]);
            }
        }

        printf("--------------\n");

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

        // Check if some player dont have cards == end game
        if (gamePlayers.player.cardsAvailable == 0) {

            printf("\n¡Has ganado la partida!\n");

            // Safe stats
            PlayerStats playerStats = FILE_export_player_stats();

            playerStats.wonGames = playerStats.wonGames + 1; // Add win to player

            BotsStats botsStats = FILE_export_bots_stats();

            for (int i = 0; i < botsStats.maxBots; i++) {
                botsStats.bots[i].lostGames = botsStats.bots[i].lostGames +1;
                if (gamePlayers.bots[i].status == AGGRSSIVE) {
                    botsStats.bots[i].agressiveGamesLost = botsStats.bots[i].passiveGamesLost + 1;
                } else {
                    botsStats.bots[i].passiveGamesLost = botsStats.bots[i].passiveGamesLost + 1;
                }
            }

            // Add data to playerStats
            FILE * fp;
            fp = fopen ("playerData.txt","w");

            int aux = 0;
            int i = 0;

            int totalLines = playerStats.cardsGamesSize + 3;

            while (i < totalLines) {
                switch (aux) {
                    case 0:
                        fprintf (fp, playerStats.name);
                        break;
                    case 1:
                        fprintf (fp, playerStats.wonGames);
                        break;
                    case 2:
                        fprintf (fp, playerStats.lostGames);
                        break;
                    default:
                        fprintf (fp, playerStats.cardsGames[i]);
                        i++;
                        break;
                }

                aux++;
            }

            fprintf (fp, gamePlayers.player.cardsAvailable); // Add cards en these game

            fclose (fp);

            // Add data to botsStats
            FILE * fb;
            fb = fopen ("botsStats.txt","w");

            aux = 0;
            i = 0;

            totalLines = botsStats.maxBots; // Each bot have 7 data

            while(i < totalLines){
                switch (aux) {
                    case 0:
                        fprintf (fb, botsStats.bots[i].name);
                        break;
                    case 1:
                        fprintf (fb, botsStats.bots[i].wonGames);
                        break;
                    case 2:
                        fprintf (fb, botsStats.bots[i].lostGames);
                        break;
                    case 3:
                        fprintf (fb, botsStats.bots[i].passiveGamesWon);
                        break;
                    case 4:
                        fprintf (fb, botsStats.bots[i].passiveGamesLost);
                        break;
                    case 5:
                        fprintf (fb, botsStats.bots[i].agressiveGamesWon);
                        break;
                    case 6:
                        fprintf (fb, botsStats.bots[i].agressiveGamesLost);
                        i++;
                        aux = -1;
                        break;
                    default:

                        break;
                }

                aux++;
            }

            fclose (fb);

            endGame == 1;

        } else {

            for (int i = 0; i < gamePlayers.numBots && endGame == 0; i++) {

               if (gamePlayers.bots[i].cardsAvailable == 0) {

                    printf("%s ha ganado la partida. Te quedaban %d cartas en mano.\n", gamePlayers.bots[i].name, gamePlayers.player.cardsAvailable);

                   // Safe stats
                   PlayerStats playerStats = FILE_export_player_stats("playerData.txt");

                   playerStats.wonGames = playerStats.lostGames + 1; // Add win to player

                   BotsStats botsStats = FILE_export_bots_stats();

                   botsStats.bots[i].wonGames = botsStats.bots[i].wonGames +1;
                   if (gamePlayers.bots[i].status == AGGRSSIVE) {
                       botsStats.bots[i].agressiveGamesWon = botsStats.bots[i].passiveGamesWon + 1;
                   } else {
                       botsStats.bots[i].passiveGamesWon = botsStats.bots[i].passiveGamesWon + 1;
                   }

                   for (int j = 0; j < gamePlayers.numBots; j++) { // Other bots

                       if (i != j) {
                           botsStats.bots[j].lostGames = botsStats.bots[j].lostGames +1;
                           if (gamePlayers.bots[j].status == AGGRSSIVE) {
                               botsStats.bots[j].agressiveGamesLost = botsStats.bots[j].passiveGamesLost + 1;
                           } else {
                               botsStats.bots[j].passiveGamesLost = botsStats.bots[j].passiveGamesLost + 1;
                           }
                       }

                   }

                    endGame == 1;

                }

            }

        }

        if (endGame == 0) {

            if (cardInGame.number == 10) { // change sense

                if (senseOfTurns == 0) {

                    senseOfTurns = 1;

                } else {

                    senseOfTurns = 0;
                }
            }

            GAME_turns(); // Change sense of the game TODO: IMPLEMENT

            if (cardInGame.number == 12 || cardInGame.number == 14) { // Check if the card in game it's +2 or +4

                if (strcmp(gamePlayers.player.name, gameTurns[indexTurns]) == 0) { // Player turn

                    if (cardInGame.number == 12) { // +2

                        for (int i = 0; i < 2; i++) {

                            GAME_player_steel_card;

                        }

                    } else { // +4

                        for (int i = 0; i < 4; i++) {

                            GAME_player_steel_card;

                        }

                    }


                } else { // Bot turn

                    for (int i = 0; i < gamePlayers.numBots; i++) {

                        if (strcmp(gamePlayers.bots[i].name, gameTurns[indexTurns]) == 0) { // Bot turn found

                            if (cardInGame.number == 12) { // +2

                                for (int i = 0; i < 2; i++) {

                                    GAME_bot_steel_card(&gamePlayers.bots[i]);

                                }

                            } else { // +4

                                for (int i = 0; i < 4; i++) {

                                    GAME_bot_steel_card(&gamePlayers.bots[i]);

                                }

                            }

                        }

                    }

                }

            } else if (cardInGame.number == 10) { // Check if the card in game it's block

                if (strcmp(gameTurns[indexTurns], gamePlayers.player.name) == 0) { // Player blocked

                    printf("Has sido bloqueado\n\n");

                    indexTurns++; // Next turn

                    if (indexTurns == MAXPLAYERSGAME) { // Check if last player array
                        indexTurns = 0;
                    }

                }

            }

        }


    } while (endGame == 0);

}