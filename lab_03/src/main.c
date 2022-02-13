#include "mergesort.h"
#include "stdio.h"
#include "string.h"

int int_comparator(const void *a, const void *b) {
    int *pi1 = (int *) a;
    int *pi2 = (int *) b;
    return *pi1 - *pi2;
}

int char_comparator(const void *a, const void *b) {
    char *pi1 = (char *) a;
    char *pi2 = (char *) b;
    return *pi1 - *pi2;
}

int str_comparator(const void *a, const void *b) {
    char **pi1 = (char **) a;
    char **pi2 = (char **) b;
    return strcmp(*pi1, *pi2);
}

size_t get_element_size(char **arg) {
    if (!strcmp("int", *arg)) {
        return sizeof(int);
    }
    if (!strcmp("char", *arg)) {
        return sizeof(char);
    }
    return sizeof(char *);
}

int main(int argc, char *argv[]) {
    size_t elements = argc - 2;
    size_t element_size = get_element_size(&argv[1]);
    void *array_ptr = malloc(element_size * elements);

    if (element_size == sizeof(int)) {
        int *array = array_ptr;

        for (size_t i = 0; i < elements; ++i) {
            *(array + i) = atoi(argv[i + 2]);
        }

        if (mergesort(array, elements, element_size, &int_comparator)) {
            printf("Error: memory allocation failed.\n");
            return 1;
        }

        for (size_t i = 0; i < elements; ++i) {
            printf("%d ", *(array + i));
        }
        printf("\n");

        free(array);
    } else if (element_size == sizeof(char)) {
        char *array = array_ptr;

        for (size_t i = 0; i < elements; ++i) {
            *(array + i) = *(argv[i + 2]);
        }

        if (mergesort(array, elements, element_size, &char_comparator)) {
            printf("Error: memory allocation failed.\n");
            return 1;
        }

        for (size_t i = 0; i < elements; ++i) {
            printf("%c ", *(array + i));
        }
        printf("\n");

        free(array);
    } else {
        char **array = array_ptr;

        for (size_t i = 0; i < elements; ++i) {
            *(array + i) = argv[i + 2];
        }

        if (mergesort(array, elements, element_size, &str_comparator)) {
            printf("Error: memory allocation failed.\n");
            return 1;
        }

        for (size_t i = 0; i < elements; ++i) {
            printf("%s ", *(array + i));
        }
        printf("\n");

        free(array);
    }

    return 0;
}