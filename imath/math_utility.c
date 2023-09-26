#include <stdio.h>
#include <stdlib.h>

void calculateProbabilities(const double * array, double * proba, int size, int sizeSample)
{
    for (int i = 0; i < size; i++)
    {
        proba[i] = array[i] / sizeSample;
    }

}

void calculateCumulativeProbabilities(const double * probaArray, double * cumulativeArray, int size)
{
    cumulativeArray[0] = probaArray[0];
    for (int i = 1; i <= size; i++)
    {
        cumulativeArray[i] = cumulativeArray[i - 1] + probaArray[i];
    }

}
