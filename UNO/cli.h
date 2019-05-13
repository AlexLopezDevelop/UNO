//
// Created by Alex Lopez on 2019-05-07.
//

#ifndef UNO_CLI_H
#define UNO_CLI_H
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

// Show stats options
#define CLI_STATS_PLAYER            1
#define CLI_STATS_BOTS              2
#define CLI_STATS_BACK_MENU         3

int CLI_menu(void); // Start Menu

int CLI_game_first(void); // Options: -Ver mano, -Robar carta

int CLI_game_second(void); // Options: -Jugar carta, -Robar carta

int CLI_stats(void);

#endif //UNO_CLI_H