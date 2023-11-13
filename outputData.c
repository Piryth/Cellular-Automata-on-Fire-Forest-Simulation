//
// Created by arnaud on 06/11/23.
//

#include "outputData.h"
#include "stdio.h"
#include "string.h"
#include "structures.h"
#include "constants.h"
void outputData(char* filename, CELL** grid) {
    //Clearing the previous file

    printf("%d", mapWidth);
    char* outputFolder = "/out";
    //Opening the file. Appending mode
    FILE *fp = fopen( "out/simulation.dat","a");
    if(fp != NULL) {
        for(int i = 0; i < mapWidth; i++) {
            for(int j=0;j<mapHeight; j++) {
                fprintf(fp,"%d",grid[i][j].state);
            }
            fprintf(fp,"\n");
        }
        fprintf(fp,";\n");

        fclose(fp);
    } else {
        //printf("Error : the output file couldn't be processed");
    }

}
