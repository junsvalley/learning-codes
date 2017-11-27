#include "list.h"

/*******************************
 * Average Time O(n^2)
 * Space O(1)
 *******************************/
void SORT_BUBBLE(link_list_t *list) {
  int i;
  link_node_t *n = list->head;
  link_node_t *c;
#ifndef __EXCHANGE_VAL__
  while(n) {
    c = n->next;
    while(c) {
      if(c->val < n->val) {
        exchange_link_node(list, n, c);
        n = c;
        c = n->next;
      } else {
        c = c->next;
      }
    }
    n = n->next;
  }
#else
  for( ; n; n=n->next) {
    c = n->next;
    for( ; c; c=c->next) {
      if(c->val < n->val) {
        exchange_node_val(n, c);
      }
    }
  }
#endif
}

