#pragma once

#include <clist.h>
#include <stdio.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct point {
    int x, y;
    intrusive_node node;
} point;

void add_point(intrusive_list *list, int x, int y);

void remove_point(intrusive_list *list, int x, int y);

void show_all_points(intrusive_list *list);

void remove_all_points(intrusive_list *list);
