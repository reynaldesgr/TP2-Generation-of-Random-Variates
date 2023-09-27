/**
 * @file This file implements utility math functions for this lab.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Calcule the standard deviation of simulation's values.
 * 
 * @param array Values of a simulation
 * @param size Size of the simulation/Number of experiments
 * @param mean Mean of simulation's values
 * 
 * @return Standard deviation of simulation's values
 * 
*/

double calculateStandardDeviation(const double * array, int size, double mean)
{
    double sumSquare = 0.0;

    for (int i = 0; i < size; i++)
    {
        double diff = array[i] - mean;
        sumSquare  += diff * diff;
    }
    
    return sqrt(sumSquare / size);
}


/**
 * @brief This function compute the probability array of being in each class.
 * ( 3 - Reproduction of discrete empirical distributions)
 * 
 * @param array Array of the number of individual of each class
 * @param probability Array of the probability of being in a class
 * @param size Size of array / Number of class
 * @param sizeSample Size of a sample : ex. : [40..45] is size 5
 * 
*/

void calculateProbabilities(const double * array, double * probability, int size, int sizeSample)
{
    for (int i = 0; i < size; i++)
    {
        probability[i] = array[i] / sizeSample;
    }

}

/**
 * @brief This function compute a array giving the cumulative probabilities of being
 * in each class.
 * 
 * @param probaArray Array of the probability of being in a class
 * @param cumulativeArray Array of the cumulative probability
 * @param size Number of class
*/
void calculateCumulativeProbabilities(const double * probaArray, double * cumulativeArray, int numberClass)
{
    cumulativeArray[0] = probaArray[0];
    for (int i = 1; i <= numberClass; i++)
    {
        cumulativeArray[i] = cumulativeArray[i - 1] + probaArray[i];
    }

}
