#include <bmp.h>
#include <stego.h>

static const int correct_args_crop = 8;
static const int correct_args_insert = 6;
static const int correct_args_extract = 5;

static void error() {
    printf("Error...\n");
    exit(0);
}

static void normalize_coords(int *x, int *y, int pic_height, int frame_height) {
    int t = *x;
    *x = *y;
    *y = t;
    *x = pic_height - (*x + frame_height - 1) - 1;
}

int main(int argc, char *argv[]) {
    if (!strcmp(argv[1], "crop-rotate")) {
        if (argc != correct_args_crop)
            error();

        BMP pic;
        if (!load_bmp(argv[2], &pic))
            error();
        int x = atoi(argv[4]);
        int y = atoi(argv[5]);
        int w = atoi(argv[6]);
        int h = atoi(argv[7]);

        if (!(0 <= x && x < x + w && x + w <= pic.info_header.width) || !(0 <= y && y < y + h && y + h <= pic.info_header.height))
            error();

        BMP cropped;
        normalize_coords(&x, &y, pic.info_header.height, h);
        if (!crop(&pic, &cropped, x, y, w, h))
            error();

        BMP rotated;
        if (!rotate(&cropped, &rotated))
            error();

        if (!save_bmp(&rotated, argv[3]))
            error();

        clear_table(&pic);
        clear_table(&cropped);
        clear_table(&rotated);
    } else if (!strcmp(argv[1], "insert")) {
        if (argc != correct_args_insert)
            error();

        int r_len = 0;
        coord *rules = read_coords(argv[4], &r_len);
        int m_len = 0;
        int *msg = read_message(argv[5], &m_len);

        if (!rules || !msg)
            error();

        BMP pic;
        if (!load_bmp(argv[2], &pic))
            error();
        for (int i = 0; i < r_len; ++i) {
            normalize_coords(&rules[i].x, &rules    [i].y, pic.info_header.height, 1);
        }

        insert(&pic, msg, m_len, rules);
        if (!save_bmp(&pic, argv[3]))
            error();

        free(rules);
        free(msg);
        clear_table(&pic);
    } else {
        if (argc != correct_args_extract)
            error();

        int r_len = 0;
        coord *rules = read_coords(argv[3], &r_len);
        BMP pic;
        if (!rules || !load_bmp(argv[2], &pic))
            error();

        for (int i = 0; i < r_len; ++i) {
            normalize_coords(&rules[i].x, &rules[i].y, pic.info_header.height, 1);
        }

        r_len = (r_len / 5) * 5;
        char *msg = extract(&pic, rules, r_len);
        if (msg == NULL)
            error();
        if (!print_msg(argv[4], msg, r_len / 5))
            error();

        clear_table(&pic);
        free(rules);
        free(msg);
    }

    return 0;
}