#ifndef __MATH_UTILITY__
#define __MATH_UTILITY__


double gaussianDensityFunction          (double x, double mean, double stdDeviation);

double calculateMean                    (double * array, int size);
double calculateMeanInt                 (int * array, int size);
double calculateStandardDeviation       (const double * array, int size, double mean);
double calculateStandardDeviationInt    (const int * array, int size, double mean);
void   calculateProbabilities           (const double * array, double * proba, int size, int sizeSample);
void   calculateCumulativeProbabilities (const double * probaArray, double * cumulativeArray, int size);

void createHistogram                    (double a, double b, int bins, int * histogram, double * data, int sample);

#endif