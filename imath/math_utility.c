#include <stdio.h>
#include <stdlib.h>

double * calculateProbabilities(const double * array, int size, int sizeSample)
{
    int      i;
    double * proba = (double *) calloc(size, sizeof(double));

    for (i = 0; i < size; i++)
    {
        *(proba + i) = (array[i] / sizeSample);
    }

    return proba;
}

double * calculateCumulativeProbabilities(const double * probaArray, int size)
{
    double * cumulativeArray = (double *) calloc(size, sizeof(double));

    for (int i = 0; i < size; i++)
    {
        cumulativeArray[i] = probaArray[i];
        for (int j = 0; j < i; j++)
        {
            cumulativeArray[i]+=probaArray[j];
        }
    }

    return cumulativeArray;
}
