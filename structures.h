//
// Created by Pax on 06/10/2023.
//

#ifndef FIRE_PROJECT_STATES_H
#define FIRE_PROJECT_STATES_H
typedef enum State {
    FUEL, BURNING, BURNT, NON_FUEL
} State;
typedef enum Flammability{LOW,MEDIUM,HIGH} Flammability;

typedef struct CELL {
    State state;
    Flammability flammability;
    int generationsBurning;
} CELL;


#endif //FIRE_PROJECT_STATES_H
