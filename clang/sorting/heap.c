#include "sort.h"

void
heapsort(
		int*	heap,	/* Heap a ser passado para ordenacao*/
		int		n)		/* Numero de itens da Heap			*/
{
	int i;
	for (i = n / 2; i >= 0; i--) heapify(heap, i, n);
	for (i = n - 1; i>0; i--) {
		int temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;
		heapify(heap, 0, i - 1);
	}
}

static void
heapify(
	int*	heap,	/* Heap a ser manipulada	*/
	int		start,	/* Inicio da Heap			*/ 
	int		end)	/* Fim da Heap				*/
{
	int last = ((end + 1) >> 1);
	while (start < last) {
		int lson = (start << 1) + 1;
		int rson = lson + 1;
		int largest;
		if (rson <= end) {
			if (heap[lson] < heap[rson])
				largest = rson;
			else
				largest = lson;
		}
		else largest = lson;
		if (heap[largest] > heap[start]) {
			int temp = heap[start];
			heap[start] = heap[largest];
			heap[largest] = temp;
			start = largest;
		}
		else break;
	}
}