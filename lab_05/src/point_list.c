#include <point_list.h>

void add_point(intrusive_list *list, int x, int y) {
    point *p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    add_node(list, &p->node);
}

void remove_point(intrusive_list *list, int x, int y) {
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