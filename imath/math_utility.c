/**
 * @file This file implements utility math functions for this lab.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Calculate the mean of simulation's values.
 * 
 * @param array Values of a simulation
 * @param size Size of the simulation/Number of experiments
 * 
 * @return Mean of simulation's values
 * 
*/

double calculateMean(double * array, int size)
{
    int sum;

    for (int i = 0; i < size; i++)
    {
        sum+=array[i];
    }

    return (double) sum / size;

}

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

double calculateStandardDeviation(const int * array, int size, double mean)
{
    double sumSquare = 0.0;

    for (int i = 0; i < size; i++)
    {
        double diff = array[i] - mean;
        sumSquare  += diff * diff;
    }
    
    return sqrt(sumSquare / size);
}


double calculateStandardDeviationInt(const int * array, int size, double mean)
{
    double sumSquare = 0;

    for (int i = 0; i < size; i++)
    {
        double diff = array[i] - mean;
        sumSquare  += diff * diff;
    }
    
    return sqrt(sumSquare / size);
}

double calculateMeanInt(int * array, int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum+=array[i];
    }
    return (double) sum / size;

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

/**
 * @brief This function creates a histogram from a data array by specifying the interval
 *  [a, b], the number of bins, and the histogram array to store the results
 *
 * @param a Lower bound of the interval
 * @param b Upper bound of the interval
 * 
 * @param bins Number of bins (bars) in the histogram
 * @param histogram Array where the histogram will be stored
 * @param data Data array from which the histogram will be constructed
 * @param sample Size of the sample 
 * 
 */

void createHistogram(double a, double b, int bins, int * histogram, double * data, int sample)
{
    int    index;
    double width = (b - a) / bins;

    for (int i = 0; i < bins; i++){
        histogram[i] = 0;
    }

    for (int i = 0; i < sample; i++ )
    {
            index = (int) ((data[i] - a) / width);
            histogram[index]++;
    }

    printf("\n -- Histogram : -- \n");
    for (int i = 0; i < bins; i++) {
        printf("Bin %d [%.2lf, %.2lf] \t : \t %d\n", i + 1, a + i * (b - a) / bins, a + (i + 1) * (b - a) / bins, histogram[i]);
    }
    
}
