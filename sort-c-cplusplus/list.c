#include "list.h"

link_list_t *create_random_list() {
  link_list_t *list = calloc(1, sizeof(link_list_t));
  list->tree = calloc(1, sizeof(avl_tree_t));
  int len = (time(0) % 10 + 10); /* 10 ~ 20 */
  int i = 0;
  link_node_t **n = &list->head;
  link_node_t **p = NULL;
  for(; i < len; i++) {
    if(*n == NULL) {
      *n = calloc(sizeof(link_node_t), 1);
      (*n)->val  = rand() % 100; //len - i;//rand() % 100;
      if(*n == list->head)
        (*n)->pre = NULL;
      else
        (*n)->pre = *p;
      list->len++;
      list->tail = *n;

      insert_avl_node(&list->tree->top, (*n)->val);
      p = n;
      n = &((*n)->next);
    }
  }
  traversal(list->tree->top);
  return list;
}

void print_link_list(link_list_t *list) {
  int i = 0;
  link_node_t *n = list->head;
  printf(" Begin -----> head %p\n", list->head);
  for(; i < list->len; i++) {
    printf(" list index is %02d : val %02d, pre %p,< self %p > ,next %p\n", i, n->val, n->pre, n, n->next);
    n = n->next;
  }
  printf(" End -----> tail is %p, total len is %d\n", list->tail, list->len);
}

void exchange_node_val(link_node_t *p, link_node_t *n) {
  if(!p || !n)
    return;

  if(p == n || p->val == n->val)
    return;

  int tval = p->val;
  p->val = n->val;
  n->val = tval;
}

void exchange_link_node(link_list_t *l, link_node_t *p, link_node_t *n) {
  if(p == n)
    return;

  if(p == l->head)
	l->head = n;
  if(n == l->tail)
	l->tail = p;

  if(p->pre) /* p is not head */
    p->pre->next = n;
  if(n->next) /* n is not tail */
    n->next->pre = p;

  if(p->next == n) {
    p->next = n->next;
    n->pre = p->pre;

    p->pre = n;
    n->next = p;
  } else {
    n->pre->next = p;
    p->next->pre = n;

	link_node_t t; /* temp */
    t.next = n->next;
    t.pre = n->pre;

    n->next = p->next;
    n->pre = p->pre;
    p->next = t.next;
    p->pre = t.pre;
  }
}

link_node_t *get_list_node(link_list_t *list, int index) {
  int i = 0;
  link_node_t *n = NULL;
  for(; i <= index; i++) {
    if(i == 0)
      n = list->head;
    else
      n = n->next;
  }
  return n;
}

int main() {
  link_list_t *s = NULL;
  s = create_random_list();
  print_link_list(s);
  //SORT_INSERT(s); /* OK */ //O(n^2)
  //SORT__SHELL(s); /* OK */ //O(n^1.3)
  //SORT_SHELL2(s); /* OK */ //O(n^1.3)
  //SORT_BUBBLE(s); /* OK */ //O(n^2)
  //SORT__QUICK(s); /* OK */ //O(nlog2n)
  //SORT_MERGE2(s); /* OK */ //O(nlog2n)
  SORT___HEAP(s); /* OK */ //O(nlog2n)
  //SORT_SIMPLE(s); /* OK */ //O(n^2)
  //SORT__RADIX(s);
  //SORT_BUCKET(s); 
  print_link_list(s);
  return 0;
}

