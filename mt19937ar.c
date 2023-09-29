#include <stdio.h>
#include <stdlib.h>

#include "mt/matsumoto.h"
#include "simulation/simulation.h"
#include "imath/math_utility.h"
#include "display/display_utility.h"

/* Testing functions */

void test_uniform(double a, double b, int sample)
{
    // Sample = 100000
    double mean;
    double array[sample];
    int    size;

    size = (int) (b - a);

    int histogram[size];
    int bins = 10;

    printf("\n -- Test uniform --\n");
    for (int i = 0; i < sample; i++)
    {
        array[i] = uniform(a, b);
    }

    createHistogram(a, b, bins, histogram, array, sample);
    mean = calculateMeanInt(histogram, bins);
    printf("\nStandard deviation for generated values by uniform() : %f \n", calculateStandardDeviationInt(histogram, bins, mean));

}

void test_empirical_distributions()
{
    simulateClasses_1();
}


int main(void)
{
    
    // 1 - Matsumoto
    //matsumoto_main();

    // 2 - Generation of uniform random numbers between A and B
    //test_uniform(-89.2, 56.7, 100000);
    
    // 3 - Reproduction of discrete empirical distributions
    //test_empirical_distributions();
    
    // HDL Probabilities
    /*double HDLcumulProbabilities[6];
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
    displayClass(HDLSimulation, 6);*/


    // 4 - Reproduction of continuous distributions
    double r;

    double mean = 11;
    double sum  = 0;

    int test20bins1    [20] = {0};
    double dataNegExp1 [1000];

    printf("\n -- NegExp (Drawing = 1000) -- \n");
    for (int i = 0; i < 1000; i++)
    {
        r              = negExp(mean);
        dataNegExp1[i] = r;
    }

    createHistogram(0, 20, 20, test20bins1, dataNegExp1, 1000);
    
    printf("\n -- Average (Drawing = 1000) : %f \n", calculateMean(dataNegExp1, 1000));

    /*int test20bins2    [20] = {0};
    double dataNegExp2 [1000000];

    printf("\n -- NegExp (Drawing = 1000000) -- \n");
    for (int i = 0; i < 1000000; i++)
    {
        r              = negExp(mean);
        dataNegExp2[i] = r;
    }

    createHistogram(0, 20, 20, test20bins2, dataNegExp2, 1000000);
    
    printf("\n -- Average (Drawing = 1000000) : %f \n", calculateMean(dataNegExp2, 1000000));*/
    
    // Gaussian distribution with a common dice (drawing 20 times then sum)
    //simulateRoll20DiceSum();

    // Box-Muller
    //simulateBMDistribution();*/
    
}
