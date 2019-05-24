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


PlayerStats FILE_export_player_stats();

int FILE_export_bots_config();

char * FILE_get_player_name();


#endif //UNO_FILE_H
