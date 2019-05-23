//
//  cli.c
//  UNO
//
//  Created by Alex Lopez on 29/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

// file decriptors

int CLI_menu() {

    char str_option[5];

    //Print menu
    printf("1. Jugar\n");
    printf("2. Mostrar estadisticas\n");
    printf("3. Salir\n");
    printf("\nOpción: ");

    //User selected option
    fgets(str_option, 5, stdin);
    str_option[strlen(str_option) - 1] = '\0';

    return atoi(str_option);
}

char CLI_game_first() {

    char str_option[5];

    printf("A. Ver mano\n");
    printf("B. Robar carta\n");
    printf("\nOpción: ");

    fgets(str_option, 5, stdin);
    str_option[strlen(str_option) - 1] = '\0';

    return str_option[0];
}

char CLI_game_second() {

    char str_option[5];

    printf("A. Jugar carta\n");
    printf("B. Robar carta\n");
    printf("\nOpción: ");

    fgets(str_option, 5, stdin);
    str_option[strlen(str_option) - 1] = '\0';

    return atoi(str_option);
}

int CLI_stats() {

    char str_option[5];

    printf("\nUNO - Estadísticas \n");
    printf("\nElige el tipo de estadísticas a visualizar: \n");
    printf("1. Jugador\n");
    printf("2. Bots\n");
    printf("3. Regresar al menú principal\n");
    printf("\nOpción: ");

    fgets(str_option, 5, stdin);
    str_option[strlen(str_option) - 1] = '\0';

    return atoi(str_option);
}