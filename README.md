# Cellular-Automata-on-Fire-Forest-Simulation

This cellular automata aim at creating a two-dimensional fire forest simulation using C. This project is initially an assignment in TU Dublin. It was initiated by professor Kevin Farell.

## Cellular automata planing

**Cell states**

We can use a simple set of states, as shown in the paper :
•	FUEL
•	NON FUEL
•	BURNING
•	BURNT

**Transitions rules**

The rules are initially simple. Only the fuel cell can turn into burning. These burning cells become burnt after a certain time.
We have : FUEL → BURNING → BURNT

**Probabilities formulas**

For the beginning, we will be using the formula described in the paper:

P(burning) = (number of burning neighbours) / 8
We will need to modify the formula when we add new variables.

**Constants**

We need to define some constants, as the size of the map. We can begin with a 100×100 map. Furthermore, we will define the number of generation/steps for the simulation. Let’s start with 100 and adapt it later.
We can add more variables, such as wind, density, …
Those variables can be discrete value (e.g. LOW FLAMMABILITY and HIGH FLAMMABILITY), or continuous (density : 1.25)…


**Terrains generation**
I still don’t know how to create a map for simulation, but we can test different configurations, such as :
•	Only fuel
•	2 fuels areas with a non-fuel middle with a small fuel path to see how non-fuel can prevent fire propagation.
•	Fully random map
UPDATE : The map will be created by hand, within a simple file. The program will read this file to generate the map. It will be possible to generate this terrain using a procedural algorithm, such as a Perlin noise.

## Further planning and flow-charts
The goal of this practical is to continue the planning of the project and set up Flowcharts, pseudocode and start the project structure.

**Data structures**

Our simulation concerns a 2-dimensional array of cells (excluding the time dimension). We need to define exactly what is a cell. In the first version, the cells will contain all the variables, except for the wind:
•	The state 
•	Flammability
•	Other variables

The cell will change during the development. Using a structure will make it modular. For the values like the states, we can use an enumeration, which will be mapped to integer (this will permit a better readability). 

**Formulas**
During the simulation, the goal will be to evaluate each cell and modify (or not) its state. The first thing to evaluate is the current state of the cell. It will define which transformations can be applied. For example, if a cell is in a burning state, it can only go burnt (or also still burning, depending on how we manage burning cells). 
The main interesting state is Fuel. We need to calculate the probability of being burnt. To do so, we can use the formula specified in the Quateri and Al paper : 

Where P is the probability of burning, and n the number of burning neighbours.

Furthermore, we can modify the formula depending on the other variables. For example, we can add a constant to the probability formula when the cell is highly flammable, or If there is wind in this direction.

**Simple flowchart**
![image](https://github.com/Piryth/Cellular-Automata-on-Fire-Forest-Simulation/assets/94105105/f9ed7a6b-5f18-4811-8cf6-b62a5496f07f)

 
**Planning the program**

Constants 
•	Map Width: Default to 100
•	Map Height: Default to 100

**UPDATE :** 
The final program will not require a constant size. As I implemented a map file reading function, the size of the map will depend on the number of characters of the file.

**Modularity**
To improve code quality and readability, we can add modularity to our program. We can separate the different parts of the project in several files. According to the flowchart above, we can separate files for each part of the process:
•	The main program will manage everything. 
•	The generation program will handle the map creation and cell allocation.
•	Structure file will contain all the data structure definitions.
•	Simulation file: will contain the code for evaluating the change of state.
•	Persistence file will manage the output of the program.

**Main program**
The main program is the entry point. It is where we will call the other modules. The main program has to follow the flowchart. It will generate the map, start the simulation, handle the persistence, and so on. It should also handle the N+1 map, by copying the map at the beginning of each iteration.  

Pseudo code example :
 
The C version can look like it (as of now it only creates a simple map with only fuel) :
```
int main(void) {

    //Allocating the ressources	
    Cell **grid = allocateMemory();
    //Initialing all the cells
    initMap();

    //Printing the map
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            printf(" %d ", grid[i][j].state);
        }
        printf("\n");
    }
    
    //Freeing the memory
    for (int i = 0; i < MAP_WIDTH; i++) {
        free(grid[i]);
    }
    free(grid);
    
}

```

**Generation file**
The generation file will provide everything related to the map creation and generation. The following functions can be used in the project :
•	AllocateMemory() allocates the memory for the map
•	GenerateMap() will add the different variables to the cells. We can create different versions of this, with different strategies of map generation (random, full fuel, …).
AllocateMemory() example :
```
Cell** allocateMemory() {
    Cell **grid = (Cell **) malloc(MAP_WIDTH * sizeof(Cell *));
    for (int i = 0; i < MAP_WIDTH; i++)
        grid[i] = (Cell *) malloc(MAP_HEIGHT * sizeof(Cell));
    return grid;
}
```

**Structure file**
The structure file will contain the structure definition of the cell, with the different variables. It will also contain several enumerations, such as State, which specifies the state of the cell.
Structures examples in C:
``` 
typedef enum State {
    FUEL, BURNING, BURNT, NON_FUEL
} State;
typedef enum Flammability{LOW,MEDIUM,HIGH} Flammability;

typedef struct Cell {
    State state;
    Flammability flammability;
} Cell;
```

**Simulation file**
The simulation file contains different functions related to cell evaluating. 
•	startSimulation() sets a cell to burning
•	evaluateCell(&Cell cell) evaluates a cell and changes its state
•	simulate() evaluates all the cells and modifies the map


**Persistance file**
This file will contain all the I/O related functions to write the results on a file.






