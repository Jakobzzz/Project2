#define _CRT_SECURE_NO_WARNINGS
#define DATA_SIZE 102400
#define BUFFER_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void LoadDataset(char *filename, float* ds) 
{
	FILE *fp;
	fp = fopen(filename, "r+b");

	char buffer[BUFFER_SIZE];
	setvbuf(fp, buffer, _IOFBF, sizeof(buffer));

	for (int i = 0; i < DATA_SIZE; i++)
	{
		fread(&ds[i], sizeof(float), 1, fp);
	}

	fclose(fp);	
}

void WriteDataset(char *filename, float* sds, float avg, float min, float max)
{
	FILE *fp;

	fp = fopen(filename, "w+b");

	//Write the average, min and max values to the first three lines of the file
	fwrite(&avg, sizeof(float), 1, fp);
	fwrite(&min, sizeof(float), 1, fp);
	fwrite(&max, sizeof(float), 1, fp);

	char buffer[BUFFER_SIZE];
	setvbuf(fp, buffer, _IOFBF, sizeof(buffer));
	
	for (int i = 0; i < DATA_SIZE; i++)
	{
		fwrite(&sds[i], sizeof(float), 1, fp);
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
	float* v = malloc(sizeof(float) * DATA_SIZE);

	//Create a floating point random number between 0 and 100
	for (int i = 0; i < DATA_SIZE; i++) 
	{
		v[i] = GenerateRandom(100);
	}
	
	f = fopen(filename, "w+b");

	char buffer[BUFFER_SIZE];
	setvbuf(f, buffer, _IOFBF, sizeof(buffer));

	for (int i = 0; i < DATA_SIZE; i++)
	{
		fwrite(&v[i], sizeof(float), 1, f);
	}

	free(v);
	fclose(f);
}

int Cmpfunc(const void * a, const void * b) 
{
	return (*(int*)a - *(int*)b);
}

void InsertionSort(float* ds)
{
	int j;
	float key = 0.f;

	for (int i = 1; i < DATA_SIZE; i++)
	{
		key = ds[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && ds[j] > key)
		{
			ds[j + 1] = ds[j];
			j = j - 1;
		}
		ds[j + 1] = key;
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
	return ds[DATA_SIZE - 1];
}

float Minimum(float* ds)
{
	return ds[0];
}

int main()
{
	//Init srand once with the system clock
	srand((unsigned int)time(NULL));

	//Create the dataset
	//CreateDataset("dataset.dat");

	//Load the dataset in the memory area addressed by ds
	float* ds = malloc(sizeof(float) * DATA_SIZE);
	LoadDataset("dataset.dat", ds);

	//Sort the dataset and put the new data in ds
	qsort(ds, DATA_SIZE, sizeof(float), Cmpfunc);

	//Compute the average value of the dataset
	float avg = Average(ds);

	//Find the max value in the dataset
	float max = Maximum(ds);

	//Find the min value in the dataset
	float min = Minimum(ds);

	//Write sorted array to a new file
	WriteDataset("sorted.dat", ds, avg, min, max);

	free(ds);

	return 0;
}
