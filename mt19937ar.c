#include <stdio.h>
#include <stdlib.h>

#include "mt/matsumoto.h"
#include "simulation/simulation.h"
#include "imath/math_utility.h"
#include "display/display_utility.h"

/**
 * @brief Test the generation of uniform random numbers using uniform().
 *
 * This function generates a sample of random numbers uniformly distributed in the
 * interval [a, b] and calculates statistics on these values, such as the mean and
 * standard deviation. The results are displayed to the console.
 *
 * @param a Lower bound of the interval.
 * @param b Upper bound of the interval.
 * @param sample Number of random numbers to generate.
 * 
 */

void test_uniform(double a, double b, int sample)
{
    double mean;
    double array[sample];
    int    size;

    size = (int) (b - a);

    int    histogram[size];
    int    bins = 10;

    printf("\n -- Test uniform --\n");
    for (int i = 0; i < sample; i++)
    {
        array[i] = uniform(a, b);
    }

    createHistogram(a, b, bins, histogram, array, sample);
    mean = calculateMeanInt(histogram, bins);
    printf("\nStandard deviation for generated values by uniform() : %f \n", calculateStandardDeviationInt(histogram, bins, mean));

}


/**
 * @brief Test empirical distributions using simulateClasses1().
 *
 * This function serves as a test function to demonstrate the use of the
 * simulateClasses1() function, which simulates and calculates the probabilities
 * of different classes A, B and C. 
 * 
 */

void test_empirical_distributions()
{
    simulateClasses1();
}




/**
 * @brief The main function.
 */

int main(void)
{
    
    // 1 - Matsumoto
    matsumoto_main();

    // 2 - Generation of uniform random numbers between A and B
    test_uniform(-89.2, 56.7, 100000);
    
    // 3 - Reproduction of discrete empirical distributions
    test_empirical_distributions();
    
    // HDL Probabilities
    double HDLcumulProbabilities[6];
    double HDLproba[6];

    printf("\n -- HDL Probabilities calculation -- \n");
    const double HDLarray[6] = {100, 400, 600, 400, 100, 200};
    calculateProbabilities(HDLarray, HDLproba, 6, 1800);
    displayArray(HDLproba, 6);


    // HDL Cumulatives Probabilities
    printf("\n -- HDL Cumulatives Probabilities calculation -- \n");
    calculateCumulativeProbabilities(HDLproba, HDLcumulProbabilities, 6);
    displayArray(HDLcumulProbabilities, 6);

    // HDL Simulation
    printf("\n -- HDL Simulation (Sample = 1000) -- \n");
    double individualPSR;
    int individualClass = 0;
    int HDLSimulation[6] = {0};

    for (int i = 0; i < 1000; i++)
    {
        individualPSR = randomIndividual();
        individualClass = simulateHDLClass(HDLcumulProbabilities, individualPSR);
        HDLSimulation[individualClass]++;
    }
    displayClass(HDLSimulation, 6);

    printf("\n -- HDL Simulation (Sample = 1000000) -- \n");
    for (int i = 0; i < 1000000; i++)
    {
        individualPSR = randomIndividual();
        individualClass = simulateHDLClass(HDLcumulProbabilities, individualPSR);
        HDLSimulation[individualClass]++;
    }
    displayClass(HDLSimulation, 6);


    // 4 - Reproduction of continuous distributions
    double r;

    // Mean = 11
    double mean = 11;

    int test20bins1    [40] = {0};
    double dataNegExp1 [1000];

    printf("\n -- NegExp (Drawing = 1000) -- \n");
    for (int i = 0; i < 1000; i++)
    {
        r              = negExp(mean);
        dataNegExp1[i] = r;
    }

    createHistogram(0, 20, 20, test20bins1, dataNegExp1, 1000);
    
    mean    = calculateMean(dataNegExp1, 1000);
    printf("\n -- Average (Drawing = 1000) : %f \n", mean);
    printf("\n -- Standard deviation (Drawing = 1000) : %f \n", calculateStandardDeviation(dataNegExp1, 1000, mean));

    
    int test20bins2    [40] = {0};
    double *dataNegExp2 = (double *) malloc(1000000 * sizeof(double));
    
    printf("\n -- NegExp (Drawing = 1000000) -- \n");
    mean = 11;
    
    for (int i = 0; i < 1000000; i++)
    {
        r              = negExp(mean);
        dataNegExp2[i] = r;
    }

    createHistogram(0, 20, 20, test20bins2, dataNegExp2, 1000000);
    
    mean    = calculateMean(dataNegExp2, 1000000);
    printf("\n -- Average (Drawing = 1000000) : %f \n", mean);
    printf("\n -- Standard deviation (Drawing = 1000000) : %f \n", calculateStandardDeviation(dataNegExp2, 1000000, mean));

    free(dataNegExp2);

    // Mean = 10

    mean = 10;

    int test20bins3    [40] = {0};
    double dataNegExp3 [NUM_SIMULATIONS];

    printf("\n -- NegExp (Drawing = 101000) -- \n");
    for (int i = 0; i < NUM_SIMULATIONS; i++)
    {
        r              = negExp(mean);
        dataNegExp3[i] = r;
    }

    createHistogram(0, 20, 20, test20bins3, dataNegExp3, NUM_SIMULATIONS);
    
    mean    = calculateMean(dataNegExp3, 101000);
    printf("\n -- Average (Drawing = 101000) : %f \n", mean);
    printf("\n -- Standard deviation (Drawing = 101000) : %f \n", calculateStandardDeviation(dataNegExp3, 101000, mean));
    
    // Gaussian distribution with a common dice (drawing 20 times then sum)
    printf("\n -- Simulate a roll-dice (20 times) -- \n");
    simulateRoll20DiceSum();

    printf("\n -- Box Muller -- \n");
    // Box-Muller
    simulateBMDistribution();

    // Testing rejection
    printf("\n -- Generic Rejection (Gaussian Law) -- \n"); 
    genericRejection(100, 10, 3, -8, 8, 0, 1);
}
