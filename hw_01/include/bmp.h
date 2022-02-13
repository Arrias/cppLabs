#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bit_map_file_header {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1, reserved2;
    uint32_t offset_bits;
} __attribute__((packed)) bit_map_file_header;

typedef struct bit_map_info_header {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t x_pels_per_meter;
    int32_t y_pels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} __attribute__((packed)) bit_map_info_header;

typedef struct pixel {
    uint8_t blue, green, red;
} pixel;

typedef struct BMP {
    bit_map_file_header file_header;
    bit_map_info_header info_header;
    pixel **tab;
    int32_t addition;
} BMP;

int load_bmp(const char *infile, BMP *pic);

int crop(const BMP *pic, BMP *new_pic, int x, int y, int w, int h);

int rotate(const BMP *pic, BMP *new_pic);

int save_bmp(const BMP *pic, const char *outfile);

void debug(const BMP *pic);

void clear_table(BMP *pic);