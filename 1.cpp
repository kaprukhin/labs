#include <omp.h>
#include <iostream>
#include <time.h>

using namespace std;

void main()
{
	int m, n, i, j, k;
	int sums = 0;
	int sum = 0;
	srand(time(0));
	cin >> m;
	cin >> n;
	int** array = new int* [m];
	for (i = 0; i < m; i++)
		array[i] = new int[n];
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			array[i][j] = rand() % 100;
		}
	}
	double start1 = omp_get_wtime();
#pragma omp parallel private(i)
	{
#pragma omp for private(j,k)
		for (i = 0; i < m; i++)
		{
			sum = 0;
			sums = 0;
			for (j = 0; j < n; j++)
			{
				for (k = j + 1; k < n; k++)
				{
					sum += array[i][j] * array[i][k];
				}
			}
			while (sum >= 2)
			{
				if (sum % 2 == 1)
				{
					sums++;
				}
				sum = sum / 2;
			}
			sums++;
		}
	}
	double end1 = omp_get_wtime();
	double start2 = omp_get_wtime();
	for (i = 0; i < m; i++)
	{
		sum = 0;
		sums = 0;
		for (j = 0; j < n; j++)
		{
			for (k = j + 1; k < n; k++)
			{
				sum += array[i][j] * array[i][k];
			}
		}
		while (sum >= 2)
		{
			if (sum % 2 == 1)
			{
				sums++;
			}
			sum = sum / 2;
		}
		sums++;
	}
	double end2 = omp_get_wtime();
	cout << "time parallel = " << end1 - start1 << "\t";
	cout << "time = " << end2 - start2;
}
