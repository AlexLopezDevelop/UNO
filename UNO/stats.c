//
// Created by Alex Lopez on 2019-05-10.
//

#include <stdio.h>

#include "stats.h"

int STATS_show_player_stats(PlayerStats playerStats) {

    printf("\nUNO - Estadísticas del jugador \n");
    printf("\nNombre: %s\n", playerStats.name);
    printf("\nEstadísticas de partidas:");
    printf("\n   Ganadas: ...... %d\n", playerStats.wonGames);
    printf("\n   Perdidas: ..... %d\n", playerStats.lostGames);
    printf("\nPresiona Enter para volver al menú principal.\n");

}

int STATS_show_bots_stats(BotsStats botsStats) {

    int totalAgresiveWon = 0;
    int totalAgresiveLost = 0;
    int totalPassiveWon = 0;
    int totalPassiveLost = 0;

    printf("\nUNO - Estadísticas de bots\n");
    printf("\n-------------------------------\n");
    printf("\nNombre - P.Ganadas - P.Perdidas\n");

    for (int i = 0; i < botsStats.maxBots; i++) {
        printf("\n%s - %d - %d\n", botsStats.bots[i].name, botsStats.bots[i].wonGames, botsStats.bots[i].lostGames);

        // Plus passive and agressive
        totalPassiveWon = totalPassiveWon + botsStats.bots[i].passiveGamesWon;
        totalPassiveLost = totalPassiveLost + botsStats.bots[i].passiveGamesLost;
        totalAgresiveWon = totalAgresiveWon + botsStats.bots[i].agressiveGamesWon;
        totalAgresiveLost = totalAgresiveLost + botsStats.bots[i].agressiveGamesLost;
    }

    printf("\n-------------------------------\n");

    printf("\nCalmados: %d - %d\n", totalPassiveWon, totalPassiveLost);
    printf("\nAgresivos: %d - %d\n", totalAgresiveWon, totalAgresiveLost);

    printf("\n-------------------------------\n");

    printf("\nTotal: %d - %d\n\n\n", totalAgresiveWon + totalPassiveWon, totalAgresiveLost + totalPassiveWon);


}