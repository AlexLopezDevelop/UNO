//
// Created by Alex Lopez on 2019-05-07.
//

#ifndef UNO_BOT_H
#define UNO_BOT_H


#include "card.h"
#include "file.h"

#define MAXCHAR     100
#define MAXDECK     50

// Struct - Bot in game
typedef struct {
    Card deck[MAXDECK];
    char name[MAXCHAR];
    int cardsAvailable;
    int status; // 0: Normal, 1: Aggressive
} Bot;

/*typedef struct {
    char name[MAXCHAR];
    int status[MAXCHAR];
    int cards;
} BotStats;*/


#endif //UNO_BOT_H
