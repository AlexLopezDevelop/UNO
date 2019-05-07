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


int main(int argc, const char * argv[]) {
    
    if (argc >= 3) { // Check if are 3 arguments or more
        
        PlayerStats playerStats;
        
        FILE_export_player_stats(argv[1]);
    
        int option;
        
        do {
            
            option = CLI_menu();
            
            switch (option) {
                case CLI_MENU_PLAY:
                        CLI_game();
                    break;
                    
                case CLI_MENU_SHOW_STATISTICS:

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
