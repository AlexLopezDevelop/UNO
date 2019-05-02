//
//  cli.c
//  UNO
//
//  Created by Alex Lopez on 29/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#include <stdio.h>

#include "cli.h"

int CLI_menu() {
    
    int option;
    
    //Print menu
    printf("1. Jugar\n");
    printf("2. Mostrar estadisticas\n");
    printf("3. Salir\n");
    
    //User selected option
    scanf("%d", &option);
    
    
    return option;
}
