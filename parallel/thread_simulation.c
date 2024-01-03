//Author : Arnaud Endignous
#include <stdio.h>
#include <pthread.h>
#include "constants.h"
#include "globals.h"
#include <stdlib.h>
#include "functions.h"
float probabilities[] = {0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1};

void *thread_simulation(void *args) {
    long rank = (long) args;
    int minHeight = rank*(MAP_HEIGHT/THREAD_COUNT);
    int maxHeight= (rank+1)*(MAP_HEIGHT/THREAD_COUNT) -1;

    //Seed generation for random in evaluate cell
    /*
     * NOTE : Thread safe random implementation by Cédric Champeix
     */
    unsigned int thread_seed = (unsigned int) time(NULL);

    //printf("min/max height = (%d,%d), rank = %ld\n", minHeight,maxHeight,rank);

    while(n < NUMBEROFGENERATIONS) {
        //Grid evaluation
        for(int i = 0; i < MAP_WIDTH; i++) {
            for(int j = minHeight; j <= maxHeight; j++) {

                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //////////                                     CELL EVALUATION                                            //////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //Saving sate
                int state = gridCurr[i][j].state;
                //Check states
                //NOTE : I didn't use a switch because they are several fuel states (low, medium and high flammability)
                if (state == LOW_FLAMMABILITY || state == MEDIUM_FLAMMABILITY || state == HIGH_FLAMMABILITY) {

                    //Counting burning neighbours
                    int nbNeighbours = 0;
                    
                    //Saving x and y evaluation position to optimize computing
                    //NOTE : idea from Kevin Farell
                    int i_west = (i - 1 + MAP_WIDTH) % MAP_WIDTH;
                    int i_east = (i + 1 + MAP_WIDTH) % MAP_WIDTH;
                    int j_north = (j - 1 + MAP_HEIGHT) % MAP_HEIGHT;
                    int j_south = (j + 1 + MAP_HEIGHT) % MAP_HEIGHT;

                    if (gridCurr[i_west][j_north].state == BURNING) nbNeighbours++;
                    if (gridCurr[i][j_north].state == BURNING) nbNeighbours++;
                    if (gridCurr[i_east][j_north].state == BURNING) nbNeighbours++;

                    if (gridCurr[i_west][j].state == BURNING) nbNeighbours++;
                    if (gridCurr[i_east][j].state == BURNING) nbNeighbours++;
                    if (gridCurr[i_west][j_south].state == BURNING) nbNeighbours++;
                    if (gridCurr[i][j_south].state == BURNING) nbNeighbours++;
                    if (gridCurr[i_east][j_south].state == BURNING) nbNeighbours++;

                    float randFloat = (float) rand_r(&thread_seed) / (float) RAND_MAX;
                    drand48_r()
                    float probability = probabilities[nbNeighbours];

                    if (state == LOW_FLAMMABILITY) probability *= 0.8;
                    if (state == HIGH_FLAMMABILITY) probability *= 1.25;

                    if (randFloat < probability) {
                        gridFuture[i][j].state = BURNING;
                    }

                } else if (state == BURNING) {
                    gridFuture[i][j].generationsBurning++;
                    if (gridCurr[i][j].generationsBurning >= 3) {
                        gridFuture[i][j].state = BURNT;
                    }
                }

                //evaluateCell(i, j, gridCurr,gridFuture, &thread_seed);
            }
        }

        pthread_mutex_lock(&mutex);
        counter++;
        if(counter == THREAD_COUNT) {
            //Copy the future grid to the current (saves the change of the fire start)
            //printf("All the threads are at the same point. Processing to the copy and writing\n");

            for (int i = 0; i < MAP_WIDTH; i++) {
                for (int j = 0; j < MAP_HEIGHT; j++) {
                    gridCurr[i][j] = gridFuture[i][j];
                }
            }

            char* buffer = malloc(30*sizeof(char));
            sprintf(buffer,"out/%d.dat",n);
            outputData(buffer, gridCurr);

            counter = 0;
            n++;
            pthread_cond_broadcast(&cond);
        } else {
            //printf("Waiting on thread %ld\n",rank);
            while(pthread_cond_wait(&cond, &mutex) !=0);
        }

        pthread_mutex_unlock(&mutex);

    }
}
