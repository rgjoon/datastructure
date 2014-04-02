#include <stdio.h>

#define MAX_SIZE 4

void func(char arr[], int size, int n)
{
	if( n == size )
	{
		printf("%s\n", arr);
	}
	else
	{
		arr[n] = '0';
		func(arr, size, n + 1);

		arr[n] = '1';
		func(arr, size, n + 1);
	}
}

int main()
{
	char arr[MAX_SIZE + 1] = {'\0', };

	func(arr, MAX_SIZE, 0);
}