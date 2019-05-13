//
// Created by Alex Lopez on 2019-05-07.
//

#ifndef UNO_BOT_H
#define UNO_BOT_H


#include "card.h"

#define MAXCHAR 100
#define MAXDECK 50

// Struct - Bot in game
typedef struct {
    Card deck[MAXDECK];
    int cardsAvailable;
    int rager;
} Bot;

typedef struct {
    char name[MAXCHAR];
    char status[MAXCHAR];
    int cards;
} BotStats;


#endif //UNO_BOT_H
