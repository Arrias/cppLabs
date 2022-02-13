#include <bmp.h>

static uint32_t get_addition(uint32_t width) {
    uint32_t cnt_of_bytes_in_row = width * sizeof(pixel);
    return ((cnt_of_bytes_in_row + sizeof(pixel)) / sizeof(int)) * sizeof(int) - cnt_of_bytes_in_row;
}

static void calc_sizes(BMP *pic) {
    int w = pic->info_header.width;
    int h = pic->info_header.height;
    pic->info_header.size_image = h * (w * sizeof(pixel) + pic->addition);
    pic->file_header.size = sizeof(bit_map_file_header) + sizeof(bit_map_info_header) + pic->info_header.size_image;
}

int init_pixels_array(pixel ***mem, uint32_t height, uint32_t width) {
    char *space = malloc(width * height * sizeof(pixel));
    *mem = malloc(height * sizeof(pixel *));

    if (mem == NULL || space == NULL)
        return 0;

    for (uint32_t i = 0; i < height; ++i) {
        (*mem)[i] = (pixel *) space;
        space += width * sizeof(pixel);
    }
    return 1;
}

int load_bmp(const char *infile, BMP *pic) {
    FILE *f = fopen(infile, "rb");

    if (f == NULL)
        return 0;

    fread(&pic->file_header, sizeof(bit_map_file_header) + sizeof(bit_map_info_header), 1, f);
    pic->addition = get_addition(pic->info_header.width);
    if (!init_pixels_array(&pic->tab, pic->info_header.height, pic->info_header.width))
        return 0;

    for (int i = 0; i < pic->info_header.height; ++i) {
        fread(pic->tab[i], sizeof(pixel), pic->info_header.width, f);
        fseek(f, pic->addition, SEEK_CUR);
    }

    fclose(f);
    return 1;
}

int crop(const BMP *pic, BMP *new_pic, int x, int y, int w, int h) {
    new_pic->file_header = pic->file_header;
    new_pic->info_header = pic->info_header;

    new_pic->info_header.width = w;
    new_pic->info_header.height = h;
    new_pic->addition = get_addition(new_pic->info_header.width);
    calc_sizes(new_pic);

    if (!init_pixels_array(&new_pic->tab, h, w))
        return 0;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            new_pic->tab[i][j] = pic->tab[x + i][y + j];
        }
    }

    return 1;
}

int rotate(const BMP *pic, BMP *new_pic) {
    new_pic->file_header = pic->file_header;
    new_pic->info_header = pic->info_header;

    new_pic->info_header.width = pic->info_header.height;
    new_pic->info_header.height = pic->info_header.width;
    new_pic->addition = get_addition(new_pic->info_header.width);
    calc_sizes(new_pic);

    if (!init_pixels_array(&new_pic->tab, new_pic->info_header.height, new_pic->info_header.width))
        return 0;

    for (int i = 0; i < new_pic->info_header.height; ++i) {
        for (int j = 0; j < new_pic->info_header.width; ++j) {
            new_pic->tab[i][j] = pic->tab[j][pic->info_header.width - i - 1];
        }
    }

    return 1;
}

int save_bmp(const BMP *pic, const char *outfile) {
    FILE *f = fopen(outfile, "wb");
    if (f == NULL)
        return 0;

    fwrite(&pic->file_header, sizeof(bit_map_info_header) + sizeof(bit_map_file_header), 1, f);
    int null = 0;

    for (int i = 0; i < pic->info_header.height; ++i) {
        fwrite(pic->tab[i], sizeof(pixel), pic->info_header.width, f);
        fwrite(&null, sizeof(char), pic->addition, f);
    }

    fclose(f);
    return 1;
}

void clear_table(BMP *pic) {
    free(*(pic->tab));
    free(pic->tab);
}

void debug(const BMP *pic) {
    printf("height:%d, width:%d\n", pic->info_header.height, pic->info_header.width);

    for (int i = 0; i < pic->info_header.height; ++i) {
        for (int j = 0; j < pic->info_header.width; ++j) {
            printf("(%d %d %d) ", pic->tab[i][j].red, pic->tab[i][j].green, pic->tab[i][j].blue);
        }
        printf("\n");
    }
}

