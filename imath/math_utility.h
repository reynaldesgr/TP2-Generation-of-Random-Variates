#ifndef __MATH_UTILITY__
#define __MATH_UTILITY__


#define M_PI (3.14159265358979323846)

double * calculateProbabilities(const double * array, int size, int sizeSample);
double * calculateCumulativeProbabilities(const double * probaArray, int size);

#endif