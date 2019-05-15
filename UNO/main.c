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


int main(int argc, const char * argv[]) {

    if (argc >= 3) { // Check if are 3 arguments or more

        PlayerStats playerStats;

        int option, optionStats;

        do {

            option = CLI_menu();

            switch (option) {

                case CLI_MENU_PLAY:
                    FILE_export_bots_config(argv[2]); // Load bots conf
                    GAME_start();

                    break;


                case CLI_MENU_SHOW_STATISTICS:
                    optionStats = CLI_stats();

                    switch (optionStats) {
                        case 1:
                            playerStats = FILE_export_player_stats(argv[1]);
                            STATS_show_player_stats(playerStats);
                            break;
                        case 2:

                            break;
                        case 3:
                            // Back to menu
                            break;
                    }

                    break;


                case CLI_MENU_EXIT:

                    break;


            }
        } while(option != CLI_MENU_EXIT);

    } else {
        printf("Error, numero de argumentos incorrecto\n\n");
        printf("Programa Finalizado...\n");
    }
}
