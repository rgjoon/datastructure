#include "heap.h"
#include <stdio.h>

int main()
{
	struct Heap h;
	struct Heap * p = &h;
	int v[] = {7, 16, 49, 82, 5, 31, 6, 2, 44};
	int i;

	heap_init(p);

	for( i = 0; i < sizeof(v) / sizeof(v[0]); i++ )
	{
		heap_push(p, v[i]);
	}

	while( h.size )
	{
		int value;

		if( heap_pop(p, &value) )
		{
			printf("[%2d] ", value);
			heap_print(p);
		}
		else
		{
			printf("*** error ***\n");
			break;
		}
	}

	return 0;
}