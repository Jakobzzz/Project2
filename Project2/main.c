#define _CRT_SECURE_NO_WARNINGS
#define DATA_SIZE 102400
#define BUFFER_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void LoadDataset(char *filename, float* ds) 
{
	FILE *fp;
	fp = fopen(filename, "r");

	for (int i = 0; i < DATA_SIZE; i++)
	{
		fscanf(fp, "%f", &ds[i]);
	}

	fclose(fp);	
}

void WriteDataset(char *filename, float* sds, float avg, float min, float max)
{
	FILE *fp;

	fp = fopen(filename, "w");

	//Write the average, min and max values to the first three lines of the file
	fprintf(fp, "%f\n", avg);
	fprintf(fp, "%f\n", min);
	fprintf(fp, "%f\n", max);
	
	for (int i = 0; i < DATA_SIZE; i++)
	{
		fprintf(fp, "%f\n", sds[i]);
	}

	fclose(fp);
}

float GenerateRandom(int rmax)
{
	//Generate a floating point random number between 0 and rmax
	return ((float)rand() / (float)(RAND_MAX)) * rmax;
}

void CreateDataset(char *filename)
{
	FILE *f;

	//Init array with a fixed size
	float* v = malloc(BUFFER_SIZE * DATA_SIZE);

	//Create a floating point random number between 0 and 100
	for (int i = 0; i < DATA_SIZE; i++) 
	{
		v[i] = GenerateRandom(100);
	}
	
	f = fopen(filename, "w");

	for (int i = 0; i < DATA_SIZE; i++)
	{
		fprintf(f, "%f\n", v[i]);
	}

	free(v);
	fclose(f);
}


void Swap(float *xp, float *yp)
{
	float temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void SelectionSort(float* ds)
{
	int i, j, min_idx;

	//One by one move boundary of unsorted subarray
	for (i = 0; i < DATA_SIZE - 1; i++)
	{
		//Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < DATA_SIZE; j++)
		{
			if (ds[j] < ds[min_idx])
				min_idx = j;
		}

		//Swap the found minimum element with the first element
		Swap(&ds[min_idx], &ds[i]);
	}
}

float Average(float* ds)
{
	float sum = 0.f;

	//Create the sum of dataset values
	for (int i = 0; i < DATA_SIZE; i++)
	{
		sum += ds[i];
	}

	return sum / DATA_SIZE;
}

float Maximum(float* ds)
{
	float maxValue = 0.f;
	
	//Find maximum value in the dataset array
	for (int i = 0; i < DATA_SIZE; i++)
	{
		if (ds[i] > maxValue)
			maxValue = ds[i];
	}
	
	return maxValue;
}

float Minimum(float* ds)
{
	float minValue = 100.f;

	//Find maximum value in the dataset array
	for (int i = 0; i < DATA_SIZE; i++)
	{
		if (ds[i] < minValue)
			minValue = ds[i];
	}

	return minValue;
}

int main()
{
	//Init srand once with the system clock
	srand((unsigned int)time(NULL));

	//Create the dataset
	CreateDataset("dataset.txt");

	//Load the dataset in the memory area addressed by ds
	float* ds = malloc(BUFFER_SIZE * DATA_SIZE);
	LoadDataset("dataset.txt", ds);

	//Compute the average value of the dataset
	float avg = Average(ds);

	//Find the max value in the dataset
	float max = Maximum(ds);

	//Find the min value in the dataset
	float min = Minimum(ds);

	//Sort the dataset and put the new data in ds
	SelectionSort(ds);

	//Write sorted array to a new file
	WriteDataset("sorted.txt", ds, avg, min, max);

	free(ds);

	return 0;
}
