#ifndef HEAP_H
#define HEAP_H
    
    /*
     * heap_type:
     * an enumeration whose variables determine the type of the heap requested
     * by the user: 0 for minimum heap and 1 for maximum heap.
     */
    typedef enum heap_type {min_heap, max_heap} heap_type;

    /*
     * heap:
     * this structure contains the heap's data array stored in the int pointer
     * named "data". "max_size" indicates the maximum number of members allowed,
     * "last_index" indicates the location of the last member of the data array,
     * and thus can run up to "max_size" - 1. "heap_type" indicates the type of
     * the heap as described above. "compare_function" is a pointer to function
     * which sets a criteria for sorting the members in a way that satisfies the
     * appropriate heap property: such function should take 2 integers, compare
     * them and return an integer (usually 1 or zero) which indicates if the input
     * integers satisfy the heap property or not.
     */
    typedef struct heap{
        int max_size;
        int last_index;
        int *data;
        int heap_type : 1;
        int (*compare_function)(int, int);
    } heap;
    
    int max_compare(int, int);
    int min_compare(int, int);
    heap *construct_heap(int, heap_type);
    void free_heap(heap*);
    void heapify(heap*, int);
    heap *array_to_heap(int*, int, int);
    void heap_insert(heap*, int);
    int heap_extract(heap*);
    int heap_top(heap*);

#endif