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
    
    printf("%s\n", nameFile);
    
    FILE * dataFile = fopen(nameFile, "r");
    
    if (dataFile == NULL) {
        
        printf("No se ha podido abrir el archivo %s.\n", nameFile);
        return playerStats;
        
    } else {
        
        printf("Se ha cargado correctamente el archivo %s\n\n", nameFile);
        
        
        char lineFile[MAXCHAR];
        
        do {
            
            lineFile[strlen(lineFile) - 1] = '\0';
            fgets(lineFile, MAXCHAR, dataFile);
            
            printf("%s\n", lineFile);
            
        } while (!feof(dataFile));
    }
    
    return playerStats;
}
