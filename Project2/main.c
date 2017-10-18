#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float* LoadDataset(int dataSetSize, char *filename) 
{
	FILE *fp;
	float *v = NULL;
	fp = fopen(filename, "r");

	for (int i = 0; i <= dataSetSize; i++) 
	{
		fread(&v[i], 1, sizeof(float), fp);
	}

	fclose(fp);
	return v;
}

void WriteDataset(int dataSetSize, char *filename, float* sds, float avg, float min, float max)
{
	FILE *fp;

	fp = fopen(filename, "w");

	//Write the average, min and max values to the first three lines of the file
	fwrite(&avg, 1, sizeof(float), fp);
	fwrite(&min, 1, sizeof(float), fp);
	fwrite(&max, 1, sizeof(float), fp);
	
	for (int i = 1; i <= dataSetSize; i++) 
	{
		fwrite(&sds[i], 1, sizeof(float), fp);
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
	float v[100 + 1];
	int totalSize = sizeof(v) / sizeof(float);

	//Create a floating point random number between 0 and 100
	for (int i = 0; i < totalSize - 1; i++) 
	{
		v[i] = GenerateRandom(100);
	}
	
	f = fopen(filename, "w");

	for (int i = 0; i < totalSize - 1; i++)
	{
		fprintf(f, "%f\n", v[i]);
	}

	fclose(f);
}


void Swap(float *xp, float *yp)
{
	float temp = *xp;
	*xp = *yp;
	*yp = temp;
}

float* SelectionSort(float* arr)
{
	int i, j, min_idx;
	int n = sizeof(arr) / sizeof(float);

	//One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		//Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
		}

		//Swap the found minimum element with the first element
		Swap(&arr[min_idx], &arr[i]);
	}

	return arr;
}

float Average(float* ds)
{
	int totalSize = sizeof(ds) / sizeof(float);
	float sum = 0.f;

	//Create the sum of dataset values
	for (int i = 0; i <= totalSize; i++)
	{
		sum += ds[i];
	}

	return sum / totalSize;
}

float Maximum(float* ds)
{
	int totalSize = sizeof(ds) / sizeof(float);
	float maxValue = 0.f;
	
	//Find maximum value in the dataset array
	for (int i = 0; i <= totalSize; i++)
	{
		if (ds[i] > maxValue)
			maxValue = ds[i];
	}
	
	return maxValue;
}

float Minimum(float* ds)
{
	int totalSize = sizeof(ds) / sizeof(float);
	float minValue = 100.f;

	//Find maximum value in the dataset array
	for (int i = 0; i <= totalSize; i++)
	{
		if (ds[i] < minValue)
			minValue = ds[i];
	}

	return minValue;
}

int main()
{
	srand((unsigned int)time(NULL));

	//Create the dataset
	CreateDataset("dataset.txt");

	//Load the dataset in the memory area addressed by ds
	//float* ds = LoadDataset(102400, "dataset.txt");

	////Compute the average value of the dataset
	//int avg = Average(ds);

	////Find the max value in the dataset
	//float max = Maximum(ds);

	////Find the min value in the dataset
	//float min = Minimum(ds);

	////Sort the dataset and copy it into the memory area pointed by sds
	//float* sds = SelectionSort(ds);

	return 0;
}




//input: DataSetSize, BufferSize, DatasetFilename, OutputFilename
//	Output : the file OutputFilename containing the sorted dataset.
//	main{
//	// load the dateset in the memory area addressed by ds
//	ds = loadDataset(dataset,DataSetSize,Buffersize);
//	  // compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
//	  avg = average(ds)
//		  // find the max value in the dataset
//		  max = maxvalue(ds)
//		  // find the min value in the dataset
//		  min = minvalue(ds)
//		  //sort the dataset and copy it into the memory area pointed by sds
//		  sds = sortDataset(ds,sortingAlgorithm);
//	  //write the sorted array into a new file plus the valies of the average, min and max as the first three records.
//	  writeDataset(OutputFilename,sds,Buffersize, avg, min, max)
//}
