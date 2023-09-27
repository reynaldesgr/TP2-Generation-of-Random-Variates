#ifndef __MATH_UTILITY__
#define __MATH_UTILITY__


#define M_PI (3.14159265358979323846)

double calculateStandardDeviation       (const double * array, int size, double mean);
void   calculateProbabilities           (const double * array, double * proba, int size, int sizeSample);
void   calculateCumulativeProbabilities (const double * probaArray, double * cumulativeArray, int size);
#endif