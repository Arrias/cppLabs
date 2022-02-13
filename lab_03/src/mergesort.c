#include "mergesort.h"

void assign(char *varying, const char *assignable, size_t element_size) {
    for (size_t i = 0; i < element_size; ++i) {
        *(varying + i) = *(assignable + i);
    }
}

void merge(char *first1, char *last1, char *first2, char *last2, char *output, size_t element_size,
           int (*comparator)(const void *, const void *)) {
    while (first1 != last1 && first2 != last2) {
        if (comparator(first1, first2) < 0) {
            assign(output, first1, element_size);
            first1 += element_size;
        } else {
            assign(output, first2, element_size);
            first2 += element_size;
        }
        output += element_size;
    }

    while (first1 != last1) {
        assign(output, first1, element_size);
        output += element_size;
        first1 += element_size;
    }

    while (first2 != last2) {
        assign(output, first2, element_size);
        output += element_size;
        first2 += element_size;
    }
}

void sort_process(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *), char *output_array) {
    if (elements <= 1) {
        return;
    }
    size_t left_half_size = elements / 2;

    char *begin = (char *) array;
    char *left_half_end = begin + left_half_size * element_size;
    char *end = begin + elements * element_size;

    sort_process(array, left_half_size, element_size, comparator, output_array);
    sort_process((char *) array + left_half_size * element_size, elements - left_half_size, element_size, comparator, output_array);
    merge(begin, left_half_end, left_half_end, end, output_array, element_size, comparator);

    for (size_t i = 0; i < elements; ++i) {
        assign((char *) array + i * element_size, output_array + i * element_size, element_size);
    }
}

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *)) {
    char *output_array = (char *) (malloc(element_size * elements));

    if (output_array == NULL) {
        return -1;
    }

    sort_process(array, elements, element_size, comparator, output_array);
    free(output_array);
    return 0;
}
