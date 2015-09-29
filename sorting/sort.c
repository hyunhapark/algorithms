#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

#define ISWAP(a,b)    int tmp=(a); (a)=(b); (b)=tmp
#define MAX(a,b)      ((a)>(b)?(a):(b))
#define MAX3I(a,b,c)  MAX(MAX(a,b),c)

static void
bubble_sort(int size, int *arr) {
	int i, j;
	for(i = 0; i < size-2; i++)  for(j = 0 ; j < size-i-1 ; j++) {{
			if (arr[j] > arr[j+1]) {
				ISWAP (arr[j], arr[j+1]);
			}
	}}
}

static void
insertion_sort(int size, int *arr) {
	int i, j;
	for(i=1; i < size; i++){
		int arr_i = arr[i];
		for(j=i-1 ; j >= 0 && arr[j] > arr_i ; j--)
			arr[j+1] = arr[j];
		arr[j+1] = arr_i;
	}
}

static void
selection_sort(int size, int *arr) {
	int i, j;
	for(i=0;i<size-1;i++){
		int min_i = i;
		for(j=i+1;j<size;j++){
			if(arr[min_i]>arr[j])
				min_i = j;
		}
		ISWAP (arr[i], arr[min_i]);
	}
}

static int
split(int size, int *arr){
	int i = 0, j;
	for(j=0; j<size-1; j++){
		if (arr[j]<arr[size-1]) {
			ISWAP (arr[i], arr[j]);
			i++;
		}
	}
	ISWAP (arr[i], arr[size-1]);
	return i;
}
static void
quick_sort(int size, int *arr) {
	if (size > 0) {
		int p = split(size, arr);
		quick_sort (p, arr);            /* 0   ~ p-1  */
		quick_sort (size-p-1, arr+p+1); /* p+1 ~ size */
	}
}

static void
merge_sort(int size, int *arr) {
	if (size > 1) {
		int i=0;
		int half = size>>1;
		int l = 0, r = half;
		int *arr2 = malloc(sizeof(int) * size);

		merge_sort (half, arr);
		merge_sort (size - half, arr + half);

		while (i<size) {
			if (arr[l] < arr[r])  arr2[i++] = arr[l++];
			else                  arr2[i++] = arr[r++];
			if (l >= half)
				while (r < size) arr2[i++] = arr[r++];
			else if (r >= size)
				while (l < half) arr2[i++] = arr[l++];
		}
		memcpy (arr, arr2, size*sizeof(int));
		free(arr2);
	}
}

static void
heap_sort(int size, int *arr) {
	int *heap = malloc(sizeof(int) * size);
	int i;
	for(i=0; i<size; i++){ /* Gen heap. */
		heap[i] = arr[i];
		int p = i;
		int pp = (p-1)/2;
		while ( p > 0 && heap[pp] < heap[p] ){
			ISWAP (heap[pp], heap[p]);
			p = pp;
			pp = (p-1)/2;
		}
	}
	
	for(i=size-1; i>=1; i--){ /* repeatedly pop the root(max) */
		ISWAP (heap[0], heap[i]);
		int p = 0;
		while( p < i )
			if ( 2*p+2 <= i-1 )
				if ( heap[p] == MAX3I (heap[p], heap[2*p+1], heap[2*p+2]) ) {
					break;
				} else if ( heap[2*p+1] > heap[2*p+2] ) {
					ISWAP (heap[p], heap[2*p+1]);
					p = 2*p+1;
				} else {
					ISWAP (heap[p], heap[2*p+2]);
					p = 2*p+2;
				}
			else if ( 2*p+1 == i-1 )
				if ( heap[p] == MAX (heap[p], heap[2*p+1] ) ) {
					break;
				} else {
					ISWAP(heap[p], heap[2*p+1]);
					break;
				}
			else
				break;
	}
	memcpy(arr, heap, sizeof(int) * size);
	free(heap);
}

int *
sort(int mode, int size, int *arr) {
	void (*do_sort[10])(int, int *) = { NULL,
			&bubble_sort,    &insertion_sort,
			&selection_sort, &quick_sort,
			&merge_sort,     &heap_sort  };
	(*do_sort[mode])(size, arr);
	return arr;
}
