#include <stdio.h>
#include <stdlib.h>
#include "double_heap.h"

/*
 * this file implements a data structure called "double_heap", which includes
 * two heaps of almost equal size: a minimum heap and a maximum heap. the minimum
 * heap's size can only exceed the maximum heap size by 1. the minimum heap always 
 * contains the larger members of all the elements in the data structure, and the 
 * maximum heap contains the rest. "double_heap_insert" function makes sure that
 * this order is preserved with each new element inserted, therefore, the upper median
 * should always lie at the root of the minimum heap (the minimum element), and
 * retrieving it should take constant time, given the fact that heap returns its
 * minimum in constant time. the header of this file contains the definition of
 * the structure.
 */

/*
 * construct_double_heap:
 * this function constructs a double_heap of size "max_size" and returns
 * a pointer to the caller. the function creates two heaps: a minimum heap
 * which contains at least half of the members, the large half, and a maximum
 * heap to store the lowest members. the minimum heap can be equal in size
 * to the maximum heap or greater by one. upon initialization, the total
 * number of elements in the structure is 0.
 */
double_heap *construct_double_heap(int max_size){
    double_heap *new_double_heap = (double_heap*)malloc(sizeof(double_heap));
    int min_heap_size = max_size % 2 == 0 ? max_size/2 : 1 + max_size/2;
    new_double_heap->max_size = max_size;
    new_double_heap->elements_count = 0;
    new_double_heap->min_heap = construct_heap(min_heap_size, min_heap);
    new_double_heap->max_heap = construct_heap(max_size/2, max_heap);
    return new_double_heap;
}

/*
 * free_double_heap:
 * frees the dynamically allocated memory to the "double_heap_object".
 */
void free_double_heap(double_heap *double_heap_object){
    free_heap(double_heap_object->max_heap);
    free_heap(double_heap_object->min_heap);
    free(double_heap_object);
}

/*
 * double_heap_insert:
 * inserts key in the double_heap "double_heap_object", in the appropriate
 * heap: if the double_heap is empty, the new key goes to the minimum heap,
 * otherwise there are two options:
 * 
 * 1. the number elements currently stored in the double_heap is even: in this
 * case, before inserting the key, both heaps contain an equal number of elements,
 * so if the new element is larger than (or equal to) the max of the maximum heap,
 * then the new key is inserted into the minimum heap, making it larger by 1 than
 * the maximum heap, otherwise the max is extracted and inserted in the minimum heap
 * and the new key is inserted in the maximum heap, again, guaranteeing that the
 * minimum heap is one element larger than the maximum heap.
 * 
 * 2. the total number of elements is odd: this means that the minimum heap is
 * one item larger than the maximum heap, therefore, after inserting the new key
 * the two heaps will contain an equal number of members. if the new key is smaller
 * than (or equal to) the min of the minimum heap, then it's inserted into the
 * maximum heap, making it equal in size to the minimum heap, otherwise, the min
 * is extracted and inserted into the maximum heap and the new key is inserted
 * in the minimum  heap, making both heaps equal in size and keeping all the elements
 * of the minimum heap larger than the elements of the maximum heap.
 * 
 * this function guarantees that the the minimum heap contains the larger elements
 * while the maximum heap contains the smaller elements. it also guarantees that both
 * heaps are either equal in size or the minimum heap is one element larger, so the
 * (upper) median is always the minimum element of the minimum heap.
 * 
 * this function runs in logarithmic time, Theta( log n ), since it can call heap_insert once,
 * which also has a time complexity of Theta( log n ), in addition to some other operations
 * which run in constant time, Theta( 1 ). 
 */
void double_heap_insert(double_heap *double_heap_object, int key){
    int count = double_heap_object->elements_count;
    if (count < double_heap_object->max_size){
        if (count == 0)
            heap_insert(double_heap_object->min_heap, key);
        else if (count%2 == 0){
            if (key >= heap_top(double_heap_object->max_heap))
                heap_insert(double_heap_object->min_heap, key);
            else {
                heap_insert(double_heap_object->min_heap, heap_extract(double_heap_object->max_heap));
                heap_insert(double_heap_object->max_heap, key);
            }
        }
        else {
            if (key <= heap_top(double_heap_object->min_heap))
                heap_insert(double_heap_object->max_heap, key);
            else {
                heap_insert(double_heap_object->max_heap, heap_extract(double_heap_object->min_heap));
                heap_insert(double_heap_object->min_heap, key);                
            }
        }
        (double_heap_object->elements_count)++;
    }
    else
        fprintf(stderr, "\nError: double heap overflow, element was not added.\n");
}

/*
 * double_heap_median:
 * as explained above, the median always lies at the root of the minimum heap,
 * and this function returns it, given a pointer to a double_heap. -1 is returned
 * in case the structure provided is empty. this function runs in constant time,
 * Theta(1), since it only calls "heap_top", which itself runs ins constant time.
 */
int double_heap_median(double_heap *double_heap_object){
    if (double_heap_object->elements_count == 0)
        return -1;
    else
        return heap_top(double_heap_object->min_heap);
}

/*
 * double_heap_items_count:
 * given a heap pointer, this function returns its elements count, the total
 * elements in both member heaps.
 */
int double_heap_items_count(double_heap *double_heap_object){
    return double_heap_object->elements_count;
}