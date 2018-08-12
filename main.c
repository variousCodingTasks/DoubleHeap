#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "double_heap.h"

#define LOW 0
#define HIGH 1023

int *generate_random_array(int, int, int);
void double_heap_demonstrate_phase(double_heap*, int*, int, int);
void double_heap_demonstrate(int);

/*
 * This program demonstrates the use of the "Double Heap" structure, which is
 * able to return the Median of its elements in constant time complexity and
 * inserts a new element in logarithmic time complexity. The structure is
 * implemented in the file "double_heap.c" and uses two heaps: a minimum heap
 * and a maximum heap. The insert function of the Double Heap preserves two
 * properties: 
 * 1. The minimum heap is either equal in size to the maximum heap
 * if their total number of elements is even, or has one more member than the
 * maximum heap, if the total member count is odd.
 * 2. The minimum heap members are larger than all the members of the maximum
 * heap.
 * These properties guarantee that the Median always lies at the root of the
 * minimum heap, which can be retrieved in constant time.
 * The "Double Heap" structure has two heaps as members, so the file "heap.c"
 * implements a heap which can be minimum or maximum, depends on the comparison
 * function set by the user. The heap can hold data of integer type but can easily
 * be adapted to hold other types of data as well.
 * The "main.c" file demonstrates how the data structure works: it creates three
 * Double Heaps of variable sizes and populates them with pseudo random numbers,
 * while gradually inserting the elements in the Double Heaps in chunks and printing
 * the Median after each phase.
 * 
 * This program is portable. A makefile for Unix based system is included (tested
 * on Ubuntu 16.04 32bit), and also an executable for Windows 64 bit systems (tested
 * on Windows 10 64bit), "gcc cygwin" should be installed for the executable to work.
 */
int main(int argc, char** argv) {
    
    printf("A \"Double Heap\" is a data structure which supports element insertion in\n"
			"logarithmic time complexity and returns the Median in constant time complexity.\n"
			"This program will create 3 Double Heaps sized 200, 400 and 800. Each of the Double\n"
			"Heaps will be populated with random integers in the range %d-%d, in chunks sized\n"
			"size * 0.25. After inserting each chunk, the program will report the Median of the\n"
			"elements inserted thus far.\n"
            "___________________________________________________________________\n", LOW, HIGH);
    
    double_heap_demonstrate(200);
    double_heap_demonstrate(400);
    double_heap_demonstrate(800);
   
    return (EXIT_SUCCESS);
}

/*
 * generate_random_array:
 * creates an array of integers of size "size". the numbers are in the range
 * "low"-"high" set to 0-1023 by default. the function uses the standard library
 * pseudo random number generator and sets the seed with each new call to the 
 * current time.
 */
int *generate_random_array(int size, int low, int high){
    int i;
    time_t t;
    int *output = (int *)malloc(size * sizeof(int));
    srand((unsigned) time(&t));
    for(i = 0; i < size; i++)
        output[i] = low + rand()%(high - low + 1);
    return output;
}

/*
 * double_heap_demonstrate_phase:
 * given an array of ints "data", the function inserts the items starting from
 * index "low" up to "high"-1 into the double heap, then prints the total number
 * of items in the Double Heap and the Median up to the point when it has finished.
 */
void double_heap_demonstrate_phase(double_heap *double_heap_object, int *data, int low, int high){
    int i;
    for (i = low; i < high; i++)
        double_heap_insert(double_heap_object, data[i]);
    printf("\nFinished inserting items %d to %d\n", low + 1, high);
    printf("Double Heap elements count is: %d. Current Median is: %d\n", double_heap_items_count(double_heap_object), double_heap_median(double_heap_object));
}

/*
 * double_heap_demonstrate:
 * creates a Double Heap of "size" elements, and creates an array of random
 * integers in the range "LOW"-"HIGH" (set to 0 - 1023 by default), by calling
 * "generate_random_array". the function adds the elements in chunks of 0.25 * size,
 * from the data array to the Double Heap by calling "double_heap_demonstrate_phase"
 * which reports its progress and prints the Median up to the point when it finishes.
 */
void double_heap_demonstrate(int size){
    int i, *data = generate_random_array(size, LOW, HIGH);
    double_heap *double_heap_object = construct_double_heap(size);
    printf("\nCreating a Double Heap of size %d:\n", size);
    for(i = 0; i < 4; i++)
        double_heap_demonstrate_phase(double_heap_object, data, i*size/4, (i + 1)*size/4);    
    free(data);
    free_double_heap(double_heap_object);
    puts("____________________________________________________________");
}