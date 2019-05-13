//
//  cli.c
//  UNO
//
//  Created by Alex Lopez on 29/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#include <stdio.h>

#include "cli.h"


int option;

int CLI_menu() {

    //Print menu
    printf("1. Jugar\n");
    printf("2. Mostrar estadisticas\n");
    printf("3. Salir\n");
    printf("\nOpción: ");
    //User selected option
    scanf("%d", &option);

    return option;
}

int CLI_game_first() {

    printf("A. Ver mano\n");
    printf("B. Robar carta\n");
    printf("\nOpción: ");

    scanf("%d", &option);

    return option;
}

int CLI_game_second() {

    printf("A. Jugar carta\n");
    printf("B. Robar carta\n");
    printf("\nOpción: ");

    scanf("%d", &option);

    return option;
}

int CLI_stats() {

    printf("\nUNO - Estadísticas \n");
    printf("\nElige el tipo de estadísticas a visualizar: \n");
    printf("1. Jugador\n");
    printf("2. Bots\n");
    printf("3. Regresar al menú principal\n");
    printf("\nOpción: ");

    scanf("%d", &option);

    return option;
}