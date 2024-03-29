//
//  main.c
//  UNO
//
//  Created by Alex Lopez on 24/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#include <stdio.h>

#include "cli.h"
#include "file.h"
#include "player.h"
#include "stats.h"
#include "game.h"
#include "bot.h"

#define MAXARGUMENTS 3


int main(int argc, const char * argv[]) {

    if (argc >= MAXARGUMENTS) { // Check if are 3 arguments or more

        PlayerStats playerStats;
        BotsStats botsStats;

        int option, optionStats;

        do {

            option = CLI_menu();

            switch (option) {

                case CLI_MENU_PLAY:

                    GAME_start(argv[1], argv[2]);

                    break;


                case CLI_MENU_SHOW_STATISTICS:
                    optionStats = CLI_stats();

                    switch (optionStats) {
                        case 1:
                            playerStats = FILE_export_player_stats(argv[1]);
                            STATS_show_player_stats(playerStats);
                            break;
                        case 2:
                            botsStats = FILE_export_bots_stats();
                            STATS_show_bots_stats(botsStats);
                            break;
                        case 3:
                            // Back to menu
                            break;
                    }

                    break;


                case CLI_MENU_EXIT:

                    FILE_clean_bots_stats();

                    printf("Programa finalizado.");

                    break;


            }
        } while(option != CLI_MENU_EXIT);

    } else {
        printf("Error, numero de argumentos incorrecto\n\n");
        printf("Programa Finalizado...\n");
    }
}
