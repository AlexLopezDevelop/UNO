//
//  file.c
//  UNO
//
//  Created by Alex Lopez on 30/04/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#include "file.h"
#include "game.h"

int FILE_clean_bots_stats() {
    // Reset bot stats file

    FILE * fb;
    fb = fopen ("botsStats.txt","w");

    int i = 0;

    while(i < 50){

        fprintf(fb, "");

        i++;
    }


}

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

char * FILE_get_player_name(char nameFile[]) {

    // Opening file

    FILE *dataFile = fopen(nameFile, "r");

    if (dataFile == NULL) {

        printf("No se ha podido abrir el archivo %s.\n", nameFile);
        return "";

    } else {

        char lineFile[MAXCHAR];
        char playerName[MAXCHAR];
        int aux = 0, end = 0;

        do {

            // Reading file

            lineFile[strlen(lineFile) - 1] = '\0';
            fgets(lineFile, MAXCHAR, dataFile);

            // Get player name
            if (aux == 0) {
                strcpy(playerName, lineFile);
                end = 1;
            }

        } while (end != 1);

        return playerName;
    }
}

BotsStats FILE_export_bots_stats() {

    BotsStats botsStats;

    FILE *dataFile = fopen(PATHBOTSSTATS, "r");

    if (dataFile == NULL) {

        printf("No se ha podido abrir el archivo %s.\n", PATHBOTSSTATS);
        return botsStats;

    } else {

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
                    strcpy(botsStats.bots[i].name, lineFile);
                    break;
                case 1:
                    botsStats.bots[i].wonGames = atoi(lineFile);
                    break;
                case 2:
                    botsStats.bots[i].lostGames = atoi(lineFile);
                    break;
                case 3:
                    botsStats.bots[i].passiveGamesWon = atoi(lineFile);
                    break;
                case 4:
                    botsStats.bots[i].passiveGamesLost = atoi(lineFile);
                    break;
                case 5:
                    botsStats.bots[i].agressiveGamesWon = atoi(lineFile);
                    break;
                case 6:
                    botsStats.bots[i].agressiveGamesLost = atoi(lineFile);
                    i++;
                    aux = -1;
                    break;
                default:

                    break;
            }

            aux++;

        } while (!feof(dataFile));

        fclose(dataFile);

        botsStats.maxBots = i; // Add total bots

    }

    return botsStats;

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


