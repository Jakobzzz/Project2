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

	/*char buffer[BUFFER_SIZE];
	setvbuf(fp, buffer, _IOFBF, sizeof(buffer));*/

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

	for (int i = 0; i < DATA_SIZE; i++)
	{
		fwrite(&v[i], sizeof(float), 1, f);
	}

	free(v);
	fclose(f);
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

//void Swap(float *xp, float *yp)
//{
//	float temp = *xp;
//	*xp = *yp;
//	*yp = temp;
//}
//
//void SelectionSort(float* ds)
//{
//	int i, j, min_idx;
//
//	//One by one move boundary of unsorted subarray
//	for (i = 0; i < DATA_SIZE - 1; i++)
//	{
//		//Find the minimum element in unsorted array
//		min_idx = i;
//		for (j = i + 1; j < DATA_SIZE; j++)
//		{
//			if (ds[j] < ds[min_idx])
//				min_idx = j;
//		}
//
//		//Swap the found minimum element with the first element
//		Swap(&ds[min_idx], &ds[i]);
//	}
//}

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
	//CreateDataset("dataset.dat");

	//Load the dataset in the memory area addressed by ds
	float* ds = malloc(sizeof(float) * DATA_SIZE);
	LoadDataset("dataset.dat", ds);

	//Compute the average value of the dataset
	float avg = Average(ds);

	//Find the max value in the dataset
	float max = Maximum(ds);

	//Find the min value in the dataset
	float min = Minimum(ds);

	//Sort the dataset and put the new data in ds
	InsertionSort(ds);

	//Write sorted array to a new file
	WriteDataset("sorted.dat", ds, avg, min, max);

	free(ds);

	return 0;
}
