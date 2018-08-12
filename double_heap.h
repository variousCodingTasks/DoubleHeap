#ifndef DOUBLE_HEAP_H
#define DOUBLE_HEAP_H
    
    #include "heap.h"
	
	/*
	 * double_heap:
	 * is a structure that holds the members of a double_heap, it contains
	 * two heaps: one minimum and one maximum. it also keeps track of the
	 * current elements count held in total by both heaps "elements_count", and
	 * the maximum number of elements allowed in total "max_size". of course,
	 * the underlying heaps have there own parameters encapsulated.
	 */
    typedef struct double_heap {
        heap *max_heap;
        heap *min_heap;
        int max_size;
        int elements_count;            
    } double_heap;

    double_heap *construct_double_heap(int);
    void free_double_heap(double_heap*);
    void double_heap_insert(double_heap*, int);
    int double_heap_median(double_heap*);
    int double_heap_items_count(double_heap*);

#endif