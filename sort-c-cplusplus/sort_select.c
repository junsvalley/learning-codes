#include "list.h"


/*******************************
 * Average Time O(n^2)
 * Space O(1)
 *******************************/
void SORT_SIMPLE(link_list_t *list) {
  int i;
  link_node_t *n = list->head;
  link_node_t *c;
  link_node_t *t;
  while(n) {
    t = n;
    for(c = n->next; c; c = c->next) {
      if(c->val < t->val)
        t = c; /* select the smallest firstly */
    }

    /* lastly, exchange */
    exchange_link_node(list, n, t);

    n = t->next;
  }
}

