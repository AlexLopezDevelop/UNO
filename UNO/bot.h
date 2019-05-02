//
//  bot.h
//  UNO
//
//  Created by Alex Lopez on 30/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#ifndef bot_h
#define bot_h

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


#endif /* bot_h */
