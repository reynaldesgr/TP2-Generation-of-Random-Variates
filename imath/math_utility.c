/**
 * @file This file implements utility math functions for this lab.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief This function implements the density function of a Gaussian distribution.
 * 
 * This function calculates the value of the Gaussian density function (PDF) at a given point 'x'.
 * 
 * @param x The value at which to calculate the PDF.
 * @param mean The mean of the Gaussian distribution.
 * @param stdDeviation The standard deviation of the Gaussian distribution.
 * 
 * @return The value of the Gaussian density function at 'x' (f(x)).
 */

double gaussianDensityFunction(double x, double mean, double stdDeviation)
{
    double coefficient = 1. / stdDeviation * (sqrt(2.0 * M_PI));
    double exponent    = - ((x*x) - stdDeviation)/(2 * (stdDeviation*stdDeviation));
    
    return coefficient * exp(exponent);
}

/**
 * @brief Calculate the mean of an array of values.
 * 
 * This function calculates the mean of a given array of values.
 * 
 * @param array The array of values.
 * @param size The size of the array.
 * 
 * @return The mean of the values in the array.
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
 * @brief Calculate the standard deviation of an array of values.
 * 
 * This function calculates the standard deviation of a given array of values.
 * 
 * @param array The array of values.
 * @param size The size of the array.
 * @param mean The mean of the values in the array.
 * 
 * @return The standard deviation of the values in the array.
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
 * @brief Calculate the standard deviation of an array of integer values.
 * 
 * This function calculates the standard deviation of a given array of integer values.
 * 
 * @param array The array of integer values.
 * @param size The size of the array.
 * @param mean The mean of the integer values in the array.
 * 
 * @return The standard deviation of the integer values in the array.
 */

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


/**
 * @brief Calculate the mean of an array of integer values.
 * 
 * This function calculates the mean of a given array of integer values.
 * 
 * @param array The array of integer values.
 * @param size The size of the array.
 * 
 * @return The mean of the integer values in the array.
 */

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
 * @brief Calculate the probabilities for discrete empirical distributions.
 * 
 * This function computes the probabilities for each class in a discrete empirical distribution
 * based on the counts of individuals in each class and the total sample size.
 * 
 * @param array Array of the number of individuals in each class.
 * @param probability Array to store the computed probabilities.
 * @param size Size of the arrays (number of classes).
 * @param sizeSample Size of the sample (total number of individuals).
 */

void calculateProbabilities(const double * array, double * probability, int size, int sizeSample)
{
    for (int i = 0; i < size; i++)
    {
        probability[i] = array[i] / sizeSample;
    }

}

/**
 * @brief Calculate the cumulative probabilities for discrete empirical distributions.
 * 
 * This function computes the cumulative probabilities for each class in a discrete empirical distribution
 * based on the probabilities of each class.
 * 
 * @param probaArray Array of the probabilities for each class.
 * @param cumulativeArray Array to store the computed cumulative probabilities.
 * @param size Number of classes.
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
 * @brief Create a histogram from data.
 * 
 * This function creates a histogram from a given data array by specifying the interval [a, b],
 * the number of bins, and the histogram array to store the results.
 * 
 * @param a Lower bound of the interval.
 * @param b Upper bound of the interval.
 * @param bins Number of bins (bars) in the histogram.
 * @param histogram Array where the histogram will be stored.
 * @param data Data array from which the histogram will be constructed.
 * @param sample Size of the sample (number of data points).
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
        if (data[i] >= a && data[i] <= b)
        {
            index = (int) ((data[i] - a) / width);
            histogram[index]++;
        }
    }

    printf("\n -- Histogram : -- \n");
    for (int i = 0; i < bins; i++) {
        printf("Bin %d [%.2lf, %.2lf] \t : \t %d\n", i + 1, a + i * (b - a) / bins, a + (i + 1) * (b - a) / bins, histogram[i]);
    }
    
}
