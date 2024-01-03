//Author : Arnaud Endignous
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "structures.h"
#include "functions.h"
#include "constants.h"
//Grids
CELL **gridCurr;
CELL **gridFuture;

pthread_mutex_t mutex;
pthread_cond_t cond;
int n = 0;
int counter = 0;
int main(void) {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                     INITIALISATION                                             ////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //Reading the map file and assigning the size. WARNING : the size must be correct and the map must be square
    gridCurr = initializeMap();

    gridFuture = (CELL **) malloc(MAP_WIDTH * sizeof(CELL *));
    for (int i = 0; i < MAP_WIDTH; i++) {
        gridFuture[i] = (CELL *) malloc(MAP_HEIGHT * sizeof(CELL));
    }

    //Copying the data to the future grid
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            gridFuture[i][j] = gridCurr[i][j];
        }
    }

    printf("Parallel execution\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                     START FIRE                                             ////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Start the fire at 1,1 (debug)
    int x_start = 5;
    int y_start = 5;
    //NOTE : at the beginning, we do not take into account whether the cell is fuel or not
    gridFuture[x_start][y_start].state = BURNING;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                     THREADS                                                ////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pthread_t *threadHandle = malloc(THREAD_COUNT * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC,&start);

    long rank;
    for (rank = 0; rank < THREAD_COUNT; ++rank) {
        pthread_create(&threadHandle[rank], NULL, &thread_simulation, (void*) rank);
    }

    for (rank = 0; rank < THREAD_COUNT ; ++rank) {
        pthread_join(threadHandle[rank], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec);
    elapsed+= (end.tv_nsec - start.tv_nsec)/ 1000000000.0;
    printf("Time elapsed according to clock_gettime : %lf sec\n",elapsed);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    //Freeing the grids
    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(gridCurr[i]);
        free(gridFuture[i]);
    }

    free(gridCurr);
    free(gridFuture);

}
