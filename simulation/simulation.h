#ifndef __SIMULATION__
#define __SIMULATION__

#define NUM_SIMULATIONS 101000 // Number of simulations
#define NUM_ROLLS 20 // Number of dice rolls
#define NUM_BINS 20 // Number of bins for the histogram     


// Bound for X & Y (Box-Muller)
#define NUM_SIMULATIONS_BM 1000
#define MIN_X -1.0
#define MAX_X 1.0

#define MIN_Y -1.0
#define MAX_Y 1.0

// Randomess
double uniform                  (double a, double b);
double negExp                   (double mean);
double randomIndividual         (void);
void   boxMuller                (double * x1, double * x2);

// Simulation
void   simulateClasses1           (void);
void   simulateClassesBound       (double a, double b, int sizeSample, int drawings, int numberClasses);
int    simulateHDLClass           (const double * cumulativeArray, double individualPSR);
void   simulateRoll20DiceSum      (void);
void   simulateBMDistribution     (void);
void   genericRejection           (double numSimulation, double mean, double stdDeviation, double minX, double maxX, double minY, double maxY);



#endif