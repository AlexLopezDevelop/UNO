//
// Created by Alex Lopez on 2019-05-07.
//

#ifndef UNO_FILE_H
#define UNO_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "bot.h"

#define MAXCHAR 100
#define PATHBOTSSTATS "botsStats.txt"

typedef struct {
    char name[MAXCHAR];
    int wonGames;
    int lostGames;
    int agressiveGamesWon;
    int agressiveGamesLost;
    int passiveGamesWon;
    int passiveGamesLost;
} BotStats;


typedef struct {
    BotStats bots[9];
    int maxBots;
} BotsStats;


PlayerStats FILE_export_player_stats();

BotsStats FILE_export_bots_stats();

int FILE_export_bots_config();

int FILE_clean_bots_stats();

char * FILE_get_player_name();


#endif //UNO_FILE_H
