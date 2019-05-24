//
//  file.c
//  UNO
//
//  Created by Alex Lopez on 30/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#include "file.h"
#include "game.h"


int FILE_export_bots_config(char nameFile[], GamePlayers * gamePlayers) {

    // Opening file

    FILE *dataFile = fopen(nameFile, "r");

    if (dataFile == NULL) {

        printf("No se ha podido abrir el archivo %s.\n", nameFile);
        return 0;

    } else {

        printf("Se ha cargado correctamente el archivo %s\n\n", nameFile);


        char lineFile[MAXCHAR];

        int aux = 0, i = 0, numBots = 0;

        fgets(lineFile, MAXCHAR, dataFile); // Pre-read
        lineFile[strlen(lineFile) - 1] = '\0';

        while (!feof(dataFile)) {

            // Adding data to the structure

            if (aux == 0) { // Num of bots

                gamePlayers->numBots = atoi(lineFile);

            } else {

                switch (aux) {

                    case 1: // Bot name

                        stpcpy(gamePlayers->bots[i].name, lineFile);

                        break;


                    case 2: // Aggressive or not

                        if (strcmp(lineFile, "Agresivo") == 0) { // Aggressive

                            gamePlayers->bots[i].status = 1;

                        } else {

                            gamePlayers->bots[i].status = 0;
                        }

                        break;


                    case 3: // Cards

                        gamePlayers->bots[i].cardsAvailable = atoi(lineFile);

                        aux = 0;
                        i++;

                        break;
                }
            }

            aux++;

            // Reading file

            fgets(lineFile, MAXCHAR, dataFile);
            lineFile[strlen(lineFile) - 1] = '\0';
        }

        fclose(dataFile);
    }

    return 1;
}

PlayerStats FILE_export_player_stats(char nameFile[]) {

    PlayerStats playerStats;

    // Opening file

    FILE *dataFile = fopen(nameFile, "r");

    if (dataFile == NULL) {

        printf("No se ha podido abrir el archivo %s.\n", nameFile);
        return playerStats;

    } else {

        printf("Se ha cargado correctamente el archivo %s\n\n", nameFile);


        char lineFile[MAXCHAR];

        int aux = 0;
        int i = 0;

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

        fclose(dataFile);
    }

    return playerStats;
}


