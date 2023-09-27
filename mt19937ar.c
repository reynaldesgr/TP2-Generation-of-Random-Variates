#include <stdio.h>
#include <stdlib.h>

#include "mt/matsumoto.h"
#include "simulation/simulation.h"
#include "imath/math_utility.h"
#include "display/display_utility.h"

/* Testing functions */

void test_uniform(double a, double b)
{
    printf("\n -- Test uniform --\n");
    printf("Resultat : %.4f \n", uniform(a, b));
}

void test_empirical_distributions()
{
    simulateClasses_1();
}


int main(void)
{
    // 1 - Matsumoto
    matsumoto_main();

    // 2 - Generation of uniform random numbers between A and B
    test_uniform(-89.2, 56.7);
    
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

    double mean = 10;
    double sum  = 0;

    int test20bins[20] = {0};

    printf("\n -- NegExp (Drawing = 100) -- \n");
    for (int i = 0; i < 100; i++)
    {
        r = negExp(mean);
        sum+=r;
        test20bins[(int) r]++;
    }

    printf("\n * Average \t : %f \n", sum/100);

    sum = 0;

    //printf("\n -- NegExp (Drawing = 1000 000) -- \n");
    
    for (int i = 0; i < 1000000; i++)
    {
        r = negExp(mean);
        sum+=r;
        test20bins[(int) r]++;
    }
    
    // This come close to the mean = 11
    printf("\n * Average \t : %f \n", sum/1000000);

    // Discrete Distribution
    printf(" \n -- Checking discrete distribution -- \n");

    for (int i = 0; i < 20; i++)
    {
        printf("%d-%d \t: %d \n", i, i+1, test20bins[i]);
    }

    // Gaussian distribution with a common dice (drawing 20 times)
    simulateRoll20DiceSum();

    // Box-Muller
    simulateBMDistribution();
}
