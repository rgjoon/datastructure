#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void display(int arr[], int size)
{
	int i;

	for( i = 0; i < size; i++ )
	{
		printf("%2d ", arr[i]);
	}

	printf("\n");
}

void selection(int arr[], int size)
{
	int i, n;

	for( i = 0; i < size; i++ )
	{
		int min = i;

		for( n = i + 1; n < size; n++ )
		{
			if( arr[n] < arr[min] )
			{
				min = n;
			}
		}

		swap(&(arr[i]), &(arr[min]));
		display(arr, size);
	}
}

int main()
{
	void (* sort)(int arr[], int size);
	int arr[MAX_SIZE] = {0, };
	int i;

	sort = selection;

	srand(time(NULL));

	// init data
	for( i = 0; i < MAX_SIZE; i++ )
	{
		arr[i] = rand() % 99 + 1;
	}

	display(arr, MAX_SIZE);
	sort(arr, MAX_SIZE);
	display(arr, MAX_SIZE);

	printf("\n");
	return 0;
}