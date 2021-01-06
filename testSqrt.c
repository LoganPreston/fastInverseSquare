#include "fastInverseSqrt.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

typedef struct
{
	int elapsed_sec;
	double elapsed_msec;
	double accuracy;
} testStats_t;

double runSqrtTest(float num, int iters, testStats_t *testStats)
{
	float testResult;
	struct timeval firstTimeVal, newTimeVal;

	gettimeofday(&firstTimeVal, NULL);
	for (int i = 0; i < iters; i++)
	{
		testResult = 1 / sqrt(num);
	}

	gettimeofday(&newTimeVal, NULL);

	if (testStats != NULL)
	{
		testStats->elapsed_sec = (int)difftime(newTimeVal.tv_sec, firstTimeVal.tv_sec);
		testStats->elapsed_msec = difftime(newTimeVal.tv_usec, firstTimeVal.tv_usec);
	}
	return testResult;
}

double runFastInverseSqrtTest(float num, int iters, testStats_t *testStats)
{
	float testResult, actual;
	struct timeval firstTimeVal, newTimeVal;

	gettimeofday(&firstTimeVal, NULL);
	for (int i = 0; i < iters; i++)
	{
		testResult = Q_rsqrt(num);
	}
	gettimeofday(&newTimeVal, NULL);

	if (testStats != NULL)
	{
		testStats->elapsed_sec = (int)difftime(newTimeVal.tv_sec, firstTimeVal.tv_sec);
		testStats->elapsed_msec = difftime(newTimeVal.tv_usec, firstTimeVal.tv_usec);

		actual = 1 / sqrt(num);
		testStats->accuracy = (testResult / actual) * 100;
	}

	return testResult;
}
//results should be 10x more than iter
double runFastInverseSqrtTest2(float num, int iters, testStats_t *testStats)
{
	float testResult, actual;

	struct timeval firstTimeVal, newTimeVal;

	gettimeofday(&firstTimeVal, NULL);
	for (int i = 0; i < iters; i++)
	{
		testResult = Q_rsqrt2(num);
	}
	gettimeofday(&newTimeVal, NULL);

	if (testStats != NULL)
	{
		testStats->elapsed_sec = (int)difftime(newTimeVal.tv_sec, firstTimeVal.tv_sec);
		testStats->elapsed_msec = difftime(newTimeVal.tv_usec, firstTimeVal.tv_usec);

		actual = 1 / sqrt(num);
		testStats->accuracy = (testResult / actual) * 100;
	}
	return testResult;
}

int main(void)
{
	int iters = 1000;
	float end=100.0F;
	testStats_t testBase;
	testStats_t testFast;
	testStats_t testFast2;

	FILE *outFile = fopen("InverseTest.csv", "w");
	//char *outStr="Number,Inverse Sqrt Time (sec), Inverse Sqrt Time (msec),Fast Sqrt Time (sec),Fast Sqrt Time (msec),Fast Sqrt Accuracy,Fast Sqrt 2 Iterations Time (sec),Fast Sqrt 2 Iterations Time (msec), Fast Sqrt 2 Iterations Accuracy\n";
	char *outFormat = "%.1f,%d,%.5f,%d,%.5f,%.2f,%d,%.5f,%.2f\n";
	fprintf(outFile, "Number,Inverse Sqrt Time (sec), Inverse Sqrt Time (usec),Fast Sqrt Time (sec),Fast Sqrt Time (usec),Fast Sqrt Accuracy,Fast Sqrt 2 Iterations Time (sec),Fast Sqrt 2 Iterations Time (usec), Fast Sqrt 2 Iterations Accuracy\n");
	fprintf(stdout, "Number,Inverse Sqrt Time (sec), Inverse Sqrt Time (usec),Fast Sqrt Time (sec),Fast Sqrt Time (usec),Fast Sqrt Accuracy,Fast Sqrt 2 Iterations Time (sec),Fast Sqrt 2 Iterations Time (usec), Fast Sqrt 2 Iterations Accuracy\n");

	for (float i = 0.1; i < end; i += 0.1)
	{
		runSqrtTest(i, iters, &testBase);
		runFastInverseSqrtTest(i, iters, &testFast);
		runFastInverseSqrtTest2(i, iters, &testFast2);

		fprintf(outFile, outFormat, i, testBase.elapsed_sec, testBase.elapsed_msec,
				testFast.elapsed_sec, testFast.elapsed_msec, testFast.accuracy,
				testFast2.elapsed_sec, testFast2.elapsed_msec, testFast2.accuracy);

		fprintf(stdout, outFormat, i, testBase.elapsed_sec, testBase.elapsed_msec,
				testFast.elapsed_sec, testFast.elapsed_msec, testFast.accuracy,
				testFast2.elapsed_sec, testFast2.elapsed_msec, testFast2.accuracy);

		//TODO write a function call that pass function into for running
		//TODO think of a better way to loop this. Currently looping over tenths lowerBound to upperBound...
	}

	return 0;
}