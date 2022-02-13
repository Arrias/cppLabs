#include "str.h"

int my_strlen(char *s1) {
    char *begin = s1;
    while (*s1) {
        s1++;
    }
    return s1 - begin;
}

char *my_strcpy(char *s1, char *s2) {
    char *begin = s1;
    while (*s2) {
        *s1++ = *s2++;
    }
    *s1 = '\0';
    return begin;
}

char *my_strcat(char *s1, char *s2) {
    char *begin = s1;
    s1 += my_strlen(s1);
    while (*s2) {
        *s1++ = *s2++;
    }
    *s1 = '\0';
    return begin;
}

int my_strcmp(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
