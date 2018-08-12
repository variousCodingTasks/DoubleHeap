/*
 * this file implements a heap and some of its related methods and functions,
 * as described in Cormen, Leiserson, Riverst, Stein "Introduction To Algorithms, 
 * Third Edition", 2009. the file's header includes a structure used by this
 * file to store the heap's data and some other descriptive parameters. the heap
 * can be either min or max and its max size is set upon its construction and can't be
 * changed afterwards. the functions implemented here are relevant to the data
 * structure "double heap" which can retrieve the median of its keys in constant
 * time (so methods like delete and increase key were not implemented).
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/*
 * max_compare:
 * takes to integers and returns 1 if the first is greater or equal
 * to the second, else, it returns 0. this is the comparison function
 * to go with a maximum heap. 
 */
int max_compare(int x, int y){
    return x >= y;
}

/*
 * min_compare:
 * takes to integers and returns 1 if the first is smaller or equal
 * to the second, else, it returns 0. this is the comparison function
 * to go with a minimum heap. 
 */
int min_compare(int x, int y){
    return x <= y;
}

/*
 * swap_elements:
 * takes an array of integers and swaps the elements at indexes
 * i and j, returns nothing.
 */
static void swap_elements(int *data,int i, int j){
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

/*
 * construct_heap:
 * a constructor.
 * creates and initializes a heap of size "max_size" and type, which can be
 * "min_heap" or "max_heap". the function creates a pointer to the heap, sets
 * the different parameters and returns the pointer to the caller.
 * the "last index" is set to -1 to indicate that the heap is empty upon its
 * initialization.
 */
heap *construct_heap(int max_size, heap_type type){
    heap *new_heap = (heap*)malloc(sizeof(heap));
    new_heap->max_size = max_size;
    new_heap->last_index = -1;
    new_heap->data = (int *)malloc(max_size * sizeof(int));
    new_heap->heap_type = type;
    if (type == min_heap)
        new_heap->compare_function = min_compare;
    else
        new_heap->compare_function = max_compare;        
    return new_heap;
}

/*
 * free_heap:
 * takes a pointer to a heap and frees its data array, which was dynamically
 * allocated when the heap was constructed, it then calls free on the heap's
 * pointer itself, returning nothing.
 */
void free_heap(heap *heap_object){
    free(heap_object->data);
    free(heap_object);
}

/*
 * parent:
 * returns the index of the parent node of a given node  located at
 * index "i" in the heap's data array.
 * if "i" is odd, the fractional part is truncated since the result
 * is implicitly cast to int, so the floor value of the division is
 * returned.
 */
static int parent(int i){
    return (i - 1)/2;
}

/*
 * left:
 * returns the index of the left son of a parent node located at index "i"
 * in the heap's data array.
 */
static int left(int i){
    return 2*i + 1;
}

/*
 * right:
 * returns the index of the right son of a parent node located at index "i"
 * in the heap's data array.
 */
static int right(int i){
    return 2*i + 2;
}

/*
 * heapify:
 * given a heap and a node (located at index "i" in the heap's data array),
 * the function applies the heapify algorithm which restores the heap property
 * along a path starting from the given node down to a leaf at the bottom of
 * the path. since the algorithm is recursive, the function calls itself as long
 * as it has detected a violation in its last call.
 */
void heapify(heap *heap_object, int i){
    int selection, l, r;
    int *data = heap_object->data;    
    l = left(i);
    r = right(i);
    if (l <= heap_object->last_index && (heap_object->compare_function)(data[l], data[i]))
        selection = l;
    else selection =i;
    if (r <= heap_object->last_index && (heap_object->compare_function)(data[r], data[selection]))
        selection = r;
    if (selection != i){
        swap_elements(heap_object->data, i, selection);
        heapify(heap_object, selection);
    }
}

/*
 * array_to_heap:
 * this function constructs a heap from an array of integers "elements"
 * of given "size" and "type" (min_heap or max_heap). after constructing
 * a heap structure, it copies the data from the source "elements" to the
 * heap's data array (so it wouldn't alter the input) and calls heapify
 * on the members of the upper half of the data array starting from the last
 * one. the function returns a pointer to the result heap to the caller.
 */
heap *array_to_heap(int *elements, int size, int type){
    int i;
    heap *elements_heap = construct_heap(size, type);
    elements_heap->last_index = size - 1;
    for(i = 0; i < size; i++)
        (elements_heap->data)[i] = elements[i];
    for(i = (elements_heap->last_index)/2 ; 0 <= i ; i--)
        heapify(elements_heap, i);
    return elements_heap;
}

/*
 * heap_insert:
 * this function inserts the new "key" into the heap_object: since last_index
 * represents an array index, it starts counting from 0, and the last available
 * cell should be located at max_size - 1, if the current last_index is indeed
 * at max_size - 1, then the heap is full and the new element can not be added,
 * otherwise, the new element is pushed at "last_index" of the data array, which
 * may present a violation to the heap property which needs to be fixed.
 * the while loop takes care of fixing any violations along a path starting
 * at the leaf, where the new element was pushed, up to the root, by swapping
 * each node and its parent in case a violation is present. the loop terminates
 * when no further violation is detected.
 */
void heap_insert(heap *heap_object, int key){
    int i, *data= heap_object->data;
    if (heap_object->last_index == heap_object->max_size - 1)
        fprintf(stderr, "\nError: heap overflow, element was not added.\n");
    else {
        data[i = ++(heap_object->last_index)] = key;
        while(i > 0 && (heap_object->compare_function)(data[i], data[parent(i)])){
            swap_elements(data, i, parent(i));
            i = parent(i);           
        }
    }    
}

/*
 * heap_extract:
 * this function takes a pointer to a heap structure and extracts its extreme
 * member (located at the 0 cell of the data array, the root), and returns it 
 * the user.
 * if the heap is empty, an error is printed to stderr, else, in case there's
 * only one member in the heap, the last_index of the heap is decremented, and
 * the first element is returned (nothing further needs to be done), otherwise,
 * the last element of the array is copied to the first cell and to fix any violations
 * to the heap property, the heapify function is called on the root, of course, after
 * decrementing the last_index of the data array here as well.
 */
int heap_extract(heap *heap_object){
    int output = 0;
    int *data = heap_object->data;
    if (heap_object->last_index == -1){
        fprintf(stderr, "\nError: heap underflow\n");
    }
    output = data[0];
    if (heap_object->last_index == 0)
        (heap_object->last_index)--;        
    else {
        data[0] = data[(heap_object->last_index)-- - 1];
        heapify(heap_object, 0);
    }
    return output;
}

/*
 * heap_top:
 * peaks into the min/max element of the heap and returns it to the user,
 * -1 is returned in case the heap is empty.
 */
int heap_top(heap *heap_object){
    if (heap_object->last_index == -1){
        fprintf(stderr, "Error: the heap is empty");
        return -1;
    }
    else
        return (heap_object->data)[0];
}