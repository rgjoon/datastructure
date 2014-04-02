#include <stdio.h>
#include <string.h>

#include "heap.h"

void heap_init(struct Heap * p)
{
	memset(p, 0, sizeof(struct Heap));
}

void heap_print(struct Heap * p)
{
	int i;

	for( i = 0; i < p->size; i++ )
	{
		printf("%2d ", p->array[i].key);
	}

	printf("\n");
}

int heap_push(struct Heap * p, int key)
{
	unsigned long pos = p->size;

	if( pos >= MAX_HEAPSIZE )
	{
		return 0;
	}

	// find adjust cell for new element
	while( pos > 0 && p->array[pos / 2].key < key )
	{
		int parent = (pos - 1) / 2;
		p->array[pos].key = p->array[parent].key;

		pos = parent;
	}

	p->array[pos].key = key;
	p->size++;

	return 1;
}

int heap_pop(struct Heap * p, int * value)
{
	int pos = 0;
	int key;

	if( p->size == 0 )
	{
		*value = 0;
		return 0;
	}

	*value = p->array[0].key;
	p->size--;

	if( p->size > 0 )
	{
		key = p->array[p->size].key;

		while( 1 )
		{
			int right = (pos + 1) * 2;
			int left = right - 1;
			int next = pos;
			int max = key;

			// find position which is bigger among pos, right, left
			if( right < p->size && max < p->array[right].key )
			{
				next = right;
				max = p->array[right].key;
			}

			if( left < p->size && max < p->array[left].key )
			{
				next = left;
				max = p->array[left].key;
			}

			if( next != pos )
			{
				p->array[pos].key = max;
				pos = next;
			}
			else
			{
				break;
			}
		}

		p->array[pos].key = key;
	}

	return 1;
}
