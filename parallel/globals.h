//
// Created by arnaud on 10/12/23.
//

#ifndef CELLULAR_AUTOMATA_PARALLEL_EDIT_GLOBALS_H
#define CELLULAR_AUTOMATA_PARALLEL_EDIT_GLOBALS_H

extern CELL **gridCurr;
extern CELL **gridFuture;

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;

extern int counter;
extern int n;

#endif //CELLULAR_AUTOMATA_PARALLEL_EDIT_GLOBALS_H
