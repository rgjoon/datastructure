#ifndef __heap_h__
#define __heap_h__

#define MAX_HEAPSIZE 64

struct Element
{
	int key;
};

struct Heap
{
	struct Element array[MAX_HEAPSIZE];
	unsigned long size;
};

#ifdef __cplusplus
extern "C" {
#endif

void heap_init(struct Heap * p);
int heap_push(struct Heap * p, int key);
int heap_pop(struct Heap * p, int * value);
void heap_print(struct Heap * p);

#ifdef _cplusplus
}
#endif

#endif // __heap_h__
