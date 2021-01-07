#include "fastInverseSqrt.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef struct
{
	int elapsed_sec;		//elapsed time in seconds, full int
	double elapsed_usec;	//elapsed time in microseconds
	double accuracy;		//accuracy of the test. Actual / calc * 100
} testStats_t;

/**
 * get a random number in [0,upperBound]
 * @param upperBound - inclusive max upper bound of random num
 * @return float random number between [0,upperBound]
 */
float randRange(float upperBound)
{
	return (rand() / (float)(RAND_MAX / upperBound)); //rand num between 0 and the bound
}

/**
 * Run test given, can pass any function that takes and returns a float
 * @param test_function - function to test. Takes and returns float
 * @param num - float to pass to function. For sqrts, should be >0
 * @param iters - iterations to sqrt the same number. Very quick operations generally now so 1000+ times to register
 * @param testStats - pointer to testStats stuct for time spent and accuracy
 * @return double, result of the test, so the value returned by test_function
 */
float runSqrtTest(float (*test_function)(float), float num, int iters, testStats_t *testStats)
{
	float testResult, actual;
	struct timeval firstTimeVal, newTimeVal;

	gettimeofday(&firstTimeVal, NULL);
	for (int i = 0; i < iters; i++)
	{
		testResult = test_function(num);
	}
	gettimeofday(&newTimeVal, NULL);

	if (testStats != NULL)
	{
		testStats->elapsed_sec = (int)difftime(newTimeVal.tv_sec, firstTimeVal.tv_sec);
		testStats->elapsed_usec = difftime(newTimeVal.tv_usec, firstTimeVal.tv_usec);

		actual = basicInverseSqrt(num);
		testStats->accuracy = (testResult / actual) * 100;
	}
	return testResult;
}

int main(void)
{
	//test iters is number of random nums sqrt, sqrtIters is iterations of a particular sqrt
	int squareRootIters = 1000, testIters = 100; 
	float num, upperBound = 100; //UB is max of the random nums
	testStats_t testBase, testShort, testFast, testFast2;
	char* fileName="InverseTest.csv";
	
	//setup file, file headers and string formatting
	FILE *outFile = fopen(fileName, "w");
	char *outFormat = "%.2f,%d,%.5f,%d,%.5f,%.2f,%d,%.5f,%.2f,%d,%.5f,%.2f\n";
	char *outStr = "Number,Inverse Sqrt Time (sec), Inverse Sqrt Time (usec),"
				   "Fast Sqrt No Iteration Time (sec), Fast Sqrt No Iteration Time (usec),Fast Sqrt No Iteration Accuracy,"
				   "Fast Sqrt Time (sec),Fast Sqrt Time (usec),Fast Sqrt Accuracy,"
				   "Fast Sqrt 2 Iterations Time (sec),Fast Sqrt 2 Iterations Time (usec),Fast Sqrt 2 Iterations Accuracy\n";
	
	//print the header to file and stdout
	fprintf(outFile, "%s", outStr);

	for (int i = 0; i < testIters; i++)
	{
		//get random number  run the base test, then run 0-2 iteration tests
		num = randRange(upperBound);
		runSqrtTest(basicInverseSqrt,num,squareRootIters,&testBase);
		runSqrtTest(Q_rsqrt_short, num, squareRootIters, &testShort);
		runSqrtTest(Q_rsqrt, num, squareRootIters, &testFast);
		runSqrtTest(Q_rsqrt_two_iter, num, squareRootIters, &testFast2);

		//results to file as CSV
		fprintf(outFile, outFormat, num, testBase.elapsed_sec, testBase.elapsed_usec,
				testShort.elapsed_sec, testShort.elapsed_usec, testShort.accuracy,
				testFast.elapsed_sec, testFast.elapsed_usec, testFast.accuracy,
				testFast2.elapsed_sec, testFast2.elapsed_usec, testFast2.accuracy);
	}

	fprintf(stdout, "Tests Completed and results are in %s\n", fileName);

	return 0;
}
