//
// Created by Alex Lopez on 2019-05-13.
//

#ifndef UNO_GAME_H
#define UNO_GAME_H

#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "player.h"
#include "file.h"


#define MAXCARDSGAMEDECK    108
#define MAXNUMCARDS         15
#define MAXBOTSGAME         10
#define MAXCARDSCOLORS      4
#define QUANTITYCARDSPLAYER 7


typedef struct {
    Bot bots[MAXBOTSGAME]; // Array bots for game
    int numBots;
    Player player;
}GamePlayers;

int GAME_start();


#endif //UNO_GAME_H
