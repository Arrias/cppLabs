#include <string.h>
#include <point_list.h>
#include <assert.h>

static const int TERM_VALUE = (int) (1 << 24) - 1;
static const int BIN_SIZE = 3;
static const int NEG_BIT = (int) (1 << 23);

typedef struct io_helper {
    FILE *stream;
    intrusive_list *list;
    const char *format;
    char *space;
} io_helper;

void read_text_point(intrusive_node *node, void *helper) {
    io_helper *cur = (io_helper *) helper;
    point *cont = container_of(node, point, node);

    if (fscanf(cur->stream, "%d %d", &cont->x, &cont->y) == EOF) {
        remove_point(cur->list, TERM_VALUE, TERM_VALUE);
        return;
    }

    add_point(cur->list, TERM_VALUE, TERM_VALUE);
}

int get_int(const char *ptr) {
    int val = *(int *) ptr - (TERM_VALUE + 1) * (int) *(ptr + BIN_SIZE);
    if (val >= NEG_BIT) { // check if is negative
        val = -((val ^ TERM_VALUE) + 1);
    }
    return val;
}

void read_bin_point(intrusive_node *node, void *helper) {
    io_helper *cur = (io_helper *) helper;
    point *cont = container_of(node, point, node);

    if (fread(cur->space, BIN_SIZE, 2, cur->stream) == 0) {
        remove_point(cur->list, TERM_VALUE, TERM_VALUE);
        return;
    }

    cont->x = get_int((char *) cur->space);
    cont->y = get_int((char *) cur->space + BIN_SIZE);
    add_point(cur->list, TERM_VALUE, TERM_VALUE);
}

void print_text_point(intrusive_node *node, void *helper) {
    io_helper *cur = (io_helper *) helper;
    point *cont = container_of(node, point, node);
    fprintf(cur->stream, cur->format, cont->x, cont->y);
}

void print_bin_point(intrusive_node *node, void *helper) {
    io_helper *cur = (io_helper *) helper;
    point *cont = container_of(node, point, node);
    *(int *) cur->space = cont->x;
    *(int *) (cur->space + BIN_SIZE) = cont->y;
    fwrite(cur->space, BIN_SIZE, 2, cur->stream);
}

void inc(intrusive_node *node, void *value) {
    assert(node && "Node is null in inc()");
    (*(int *) value)++;
}

void read_list(intrusive_list *list, const char *type, const char *infile) {
    int cmp = strcmp(type, "loadtext");
    add_point(list, TERM_VALUE, TERM_VALUE);

    FILE *f = fopen(infile, !cmp ? "r" : "rb");
    void (*op)(intrusive_node *, void *) = !cmp ? read_text_point : read_bin_point;
    io_helper helper = {f, list, "", NULL};
    helper.space = calloc(2 * BIN_SIZE + 2, 1);

    apply(list, op, &helper);
    free(helper.space);
    fclose(f);
}

void save_list(intrusive_list *list, const char *type, const char *outfile) {
    int cmp = strcmp(type, "savetext");

    FILE *f = fopen(outfile, !cmp ? "w" : "wb");
    void (*op)(intrusive_node *, void *) = !cmp ? print_text_point : print_bin_point;
    io_helper helper = {f, list, "%d %d\n", NULL};
    helper.space = calloc(2 * BIN_SIZE + 2, 1);

    apply(list, op, &helper);
    free(helper.space);
    fclose(f);
}

int main(int argc, char *argv[]) {
    assert(argc > 1 && "argc is void");

    intrusive_list c;
    init_list(&c);
    read_list(&c, argv[1], argv[2]);

    if (!strcmp(argv[3], "print")) {
        io_helper helper = {stdout, &c, argv[4], NULL};
        apply(&c, print_text_point, &helper);
        printf("\n");
    } else if (!strcmp(argv[3], "count")) {
        int count = 0;
        apply(&c, inc, &count);
        printf("%d\n", count);
    } else {
        save_list(&c, argv[3], argv[4]);
    }

    remove_all_points(&c);
    free(c.head);
    return 0;
}