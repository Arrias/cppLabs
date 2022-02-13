#include <clist.h>
#include <stdio.h>
#include <string.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct point {
    int x, y;
    intrusive_node node;
} point;

void add_point(intrusive_list *list, int x, int y) {
    point *p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    add_node(list, &p->node);
}

void remove_point(intrusive_list *list, int x, int y) { // removes all (x, y) pairs
    intrusive_node *head = list->head;

    while (head->next) {
        point *cont = container_of(head->next, point, node);
        if (cont->x == x && cont->y == y) {
            remove_node(list, head->next);
            free(cont);
        } else {
            head = head->next;
        }
    }
}

void show_all_points(intrusive_list *list) {
    intrusive_node *tail = list->tail;

    while (tail != list->head) {
    	if (tail != list->tail) {
    		printf(" ");
    	}
        point *cont = container_of(tail, point, node);
        printf("(%d %d)", cont->x, cont->y);
        tail = tail->prev;
    }
    printf("\n");
}

void remove_all_points(intrusive_list *list) {
    while (list->tail != list->head) {
        point *cont = container_of(list->tail, point, node);
        intrusive_node *previous = list->tail->prev;
        free(cont);
        previous->next = NULL;
        list->tail = previous;
    }
}

int main() {
    intrusive_list c;
    init_list(&c);
    
    char str[239];

    while (scanf("%239s", str) == 1) {
        int x, y;

        if (!strcmp(str, "exit")) {
            break;
        } else if (!strcmp(str, "len")) {
            printf("%d\n", get_length(&c));

        } else if (!strcmp(str, "rma")) {
            remove_all_points(&c);

        } else if (!strcmp(str, "print")) {
            show_all_points(&c);

        } else if (!strcmp(str, "rm")) {
            scanf("%d %d", &x, &y);
            remove_point(&c, x, y);

        } else if (!strcmp(str, "add")) {
            scanf("%d %d", &x, &y);
            add_point(&c, x, y);

        } else {
            printf("Unknown command\n");
        }
    }

    remove_all_points(&c);
    free(c.head);

    return 0;
}
