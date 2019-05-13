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