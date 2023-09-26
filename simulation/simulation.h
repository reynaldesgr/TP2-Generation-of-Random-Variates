#ifndef __SIMULATION__
#define __SIMULATION__


// Randomess
double uniform(double a, double b);
double negExp(double mean);
double randomIndividual();

// Simulation
void simulateClasses_1();
void simulateClassesBound(double a, double b, int sizeSample, int drawings, int numberClasses);
int  simulateHDLClass(const double * cumulativeArray, double individualPSR);

#endif