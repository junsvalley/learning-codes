#ifndef __SORT_LIST_H__
#define __SORT_LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "avl_tree.h"

typedef struct link_node {
  struct link_node *pre;
  struct link_node *next;
  int val;
} link_node_t;

typedef struct link_list {
  link_node_t *head;
  link_node_t *tail;
  unsigned int len;
  avl_tree_t *tree;
} link_list_t;

void print_link_list(link_list_t *list) ;
void exchange_node_val(link_node_t *m, link_node_t *n);
void exchange_link_node(link_list_t *l, link_node_t *m, link_node_t *n);
link_node_t *get_list_node(link_list_t *list, int index);

extern void SORT_INSERT(link_list_t *list);
extern void SORT__SHELL(link_list_t *list);
extern void SORT_BUBBLE(link_list_t *list);
extern void SORT__QUICK(link_list_t *list);
extern void SORT__MERGE(link_list_t *list);
extern void SORT___HEAP(link_list_t *list);
extern void SORT_SIMPLE(link_list_t *list);
extern void SORT__RADIX(link_list_t *list);
extern void SORT_BUCKET(link_list_t *list);

#endif

