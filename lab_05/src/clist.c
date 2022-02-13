#include <clist.h>

void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data) {
    intrusive_node *cur_node = list->head;

    while (cur_node && cur_node->next) {
        op(cur_node->next, data);
        cur_node = cur_node->next;
    }
}

void init_list(intrusive_list *list) {
    list->head = list->tail = malloc(sizeof(intrusive_node));
    list->head->prev = list->head->next = NULL;
}

void add_node(intrusive_list *list, intrusive_node *node) {
    list->tail->next = node;
    node->prev = list->tail;
    node->next = NULL;
    list->tail = list->tail->next;
}

void remove_node(intrusive_list *list, intrusive_node *node) {
    intrusive_node *cur_node = list->head;

    while (cur_node != node) {
        cur_node = cur_node->next;
    }
    cur_node->prev->next = cur_node->next;

    if (cur_node == list->tail) {
        list->tail = list->tail->prev;
    } else {
        cur_node->next->prev = cur_node->prev;
    }
}

int get_length(intrusive_list *list) {
    int len = 0;
    intrusive_node *head = list->head;

    while (head->next) {
        len++;
        head = head->next;
    }
    return len;
}