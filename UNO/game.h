//
// Created by Alex Lopez on 2019-05-13.
//

#ifndef UNO_GAME_H
#define UNO_GAME_H

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "player.h"
#include "file.h"
#include "bot.h"


#define MAXCARDSGAMEDECK    108
#define MAXNUMCARDS         15
#define MAXPLAYERSGAME      4
#define MAXBOTSGAME         9
#define MAXCARDSCOLORS      4
#define QUANTITYCARDSPLAYER 7

#define CLOCKWISE           0
#define COUNTERCLOCKWISE    1

#define AGGRSSIVE           1


typedef struct {
    Bot bots[MAXBOTSGAME]; // Array bots for game
    int numBots;
    Player player;
}GamePlayers;

int GAME_start();


#endif //UNO_GAME_H
