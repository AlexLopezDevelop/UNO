//
// Created by Alex Lopez on 2019-05-07.
//

#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H

#include "card.h"

#define MAXDECK         50
#define MAXCHAR         100
#define MAXCARDSGAMES   100


// Struct - Player in game
typedef struct {
    Card deck[MAXDECK];
    int cardsAvailable;
} Player;


// Struct - Player stats
typedef struct {
    char name[MAXCHAR];
    int wonGames;
    int lostGames;
    int cardsGames[MAXCARDSGAMES];
    int cardsGamesSize;
} PlayerStats;


#endif //UNO_PLAYER_H
