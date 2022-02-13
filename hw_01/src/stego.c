#include <stego.h>

static const int word_length = 5;
static const int buff_size = 100;

static int get_code(int c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A';
    } else if (c == '.') {
        return 26;
    } else if (c == ',') {
        return 27;
    }
    return 28;
}

static char get_decode(int c) {
    if (c <= 25) {
        return (char) (c + 'A');
    } else if (c == 26) {
        return '.';
    } else if (c == 27) {
        return ',';
    }
    return ' ';
}

static int get_msg_length(const char *infile) {
    int len = 0;
    FILE *f = fopen(infile, "r");
    char buf[buff_size];
    memset(buf, 0, buff_size);

    while (!feof(f)) {
        fgets(buf, buff_size, f);
        len += (int) strlen(buf);
    }

    fclose(f);
    return len;
}

static int get_coords_length(const char *infile) {
    int len = 0;
    FILE *f = fopen(infile, "r");
    char buf[buff_size];
    memset(buf, 0, buff_size);

    coord temp;
    while (fscanf(f, "%d %d %s", &temp.x, &temp.y, buf) != EOF) {
        len++;
    }

    fclose(f);
    return len;
}

int *read_message(const char *infile, int *length) {
    FILE *f = fopen(infile, "r");
    if (f == NULL)
        return NULL;

    *length = get_msg_length(infile) * word_length;
    int *array = malloc(sizeof(int) * *length);
    int ptr = 0;

    char buf[buff_size];
    memset(buf, 0, buff_size);

    while (!feof(f)) {
        fgets(buf, buff_size, f);
        int len = (int) strlen(buf);

        for (int i = 0; i < len; ++i) {
            int code = get_code(buf[i]);
            for (int j = 0; j < word_length; ++j) {
                array[ptr++] = code % 2;
                code /= 2;
            }
        }
    }

    fclose(f);
    return array;
}

coord *read_coords(const char *infile, int *length) {
    FILE *f = fopen(infile, "r");
    if (f == NULL)
        return NULL;

    *length = get_coords_length(infile);
    coord *mem = malloc(sizeof(coord) * *length);
    char buf[2];

    for (int i = 0; i < *length; ++i) {
        fscanf(f, "%d %d %s", &mem[i].x, &mem[i].y, buf);
        mem[i].channel = buf[0];
    }

    fclose(f);
    return mem;
}

void insert(BMP *pic, const int *message, int m_length, coord *coords) {
    for (int i = 0; i < m_length; ++i) {
        int x = coords[i].x;
        int y = coords[i].y;
        uint8_t *value;

        switch (coords[i].channel) {
            case 'R':
                value = &pic->tab[x][y].red;
                break;
            case 'B':
                value = &pic->tab[x][y].blue;
                break;
            case 'G':
                value = &pic->tab[x][y].green;
        }

        *value = ((*value) / 2) * 2;
        *value += message[i];
    }
}

char *extract(BMP *pic, coord *coords, int r_length) {
    char *msg = malloc(r_length / 5);

    for (int i = 0; i < r_length; i += 5) {
        int cur_code = 0;
        int cur_pwr = 1;

        for (int j = i; j < i + 5; ++j) {
            int x = coords[j].x;
            int y = coords[j].y;
            uint8_t *value;

            switch (coords[j].channel) {
                case 'R':
                    value = &pic->tab[x][y].red;
                    break;
                case 'B':
                    value = &pic->tab[x][y].blue;
                    break;
                case 'G':
                    value = &pic->tab[x][y].green;
            }
            cur_code += cur_pwr * (*value % 2);
            cur_pwr *= 2;
        }
        msg[i / 5] = get_decode(cur_code);
    }

    return msg;
}

int print_msg(const char *outfile, const char *message, int m_length) {
    FILE *f = fopen(outfile, "w");
    if (f == NULL)
        return 0;

    for (int i = 0; i < m_length; ++i) {
        fprintf(f, "%c", message[i]);
    }

    fclose(f);
    return 1;
}