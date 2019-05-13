//
//  file.c
//  UNO
//
//  Created by Alex Lopez on 30/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#include "file.h"

#define MAXCHAR 100


PlayerStats FILE_export_player_stats(char nameFile[]) {

    PlayerStats playerStats;

    // Opening file

    FILE * dataFile = fopen(nameFile, "r");

    if (dataFile == NULL) {

        printf("No se ha podido abrir el archivo %s.\n", nameFile);
        return playerStats;

    } else {

        printf("Se ha cargado correctamente el archivo %s\n\n", nameFile);


        char lineFile[MAXCHAR];

        int aux = 0;
        int i   = 0;

        do {

            // Reading file

            lineFile[strlen(lineFile) - 1] = '\0';
            fgets(lineFile, MAXCHAR, dataFile);

            // Adding data to the structure

            switch (aux) {
                case 0:
                    strcpy(playerStats.name, lineFile);
                    break;
                case 1:
                    playerStats.wonGames = atoi(lineFile);
                    break;
                case 2:
                    playerStats.lostGames = atoi(lineFile);
                    break;
                default:
                    playerStats.cardsGames[i] = atoi(lineFile);
                    playerStats.cardsGamesSize = i;
                    i++;
                    break;
            }

            aux++;

        } while (!feof(dataFile));
    }

    return playerStats;
}


