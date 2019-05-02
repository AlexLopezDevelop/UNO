//
//  jugador.h
//  UNO
//
//  Created by Alex Lopez on 24/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#ifndef jugador_h
#define jugador_h

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
} PlayerStats;


#endif /* jugador_h */
