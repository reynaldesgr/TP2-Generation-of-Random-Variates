#ifndef __SIMULATION__
#define __SIMULATION__

#define NUM_SIMULATIONS 1000      // Number of simulations
#define NUM_ROLLS 20             // Number of dice rolls
#define NUM_BINS 120            // Number of bins for the histogram

// Randomess
double uniform(double a, double b);
double negExp(double mean);
double randomIndividual();
void boxMuller(double * x1, double * x2);
double genericRejectionBM(double * x1, double * x2, double minX, double maxX, double minY, double maxY);

// Simulation
void simulateClasses_1();
void simulateClassesBound(double a, double b, int sizeSample, int drawings, int numberClasses);
int  simulateHDLClass(const double * cumulativeArray, double individualPSR);
void simulateRoll20DiceSum();
double roll20Dice();


// Utility
void accumulateClass(int * t, double x);

#endif