#pragma once

#include <string.h>
#include <bmp.h>

typedef struct coord {
    int x, y;
    char channel;
} coord;

int *read_message(const char *infile, int *length);

coord *read_coords(const char *infile, int *length);

void insert(BMP *pic, const int *message, int m_length, coord *coords);

char *extract(BMP *pic, coord *coords, int r_length);

int print_msg(const char *outfile, const char *message, int m_length);