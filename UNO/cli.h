//
//  cli.h
//  UNO
//
//  Created by Alex Lopez on 29/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#ifndef cli_h
#define cli_h

#include <stdio.h>


// Main Menu options
#define CLI_MENU_PLAY               1
#define CLI_MENU_SHOW_STATISTICS    2
#define CLI_MENU_EXIT               3

// Game frist options
#define CLI_GAME_FIRST_SEE_HAND     1
#define CLI_GAME_FIRST_STEAL_CARD   2

// Game second options
#define CLI_GAME_SECOND_PLAY_CARD   1
#define CLI_GAME_FIRST_STEAL_CARD   2


int CLI_menu(void); // Start Menu

int CLI_game_first(void); // Options: -Ver mano, -Robar carta

int CLI_game_second(void); // Options: -Jugar carta, -Robar carta


#endif /* cli_h */
