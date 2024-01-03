//
// Created by Arnaud on 06/10/2023.
//

#ifndef FIRE_PROJECT_STATES_H
#define FIRE_PROJECT_STATES_H
typedef enum State {
    BURNING, BURNT, NON_FUEL, LOW_FLAMMABILITY, MEDIUM_FLAMMABILITY, HIGH_FLAMMABILITY
} State;

typedef struct CELL {
    State state;
    int generationsBurning;
} CELL;
#endif //FIRE_PROJECT_STATES_H
