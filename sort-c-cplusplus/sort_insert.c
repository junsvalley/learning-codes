#include "list.h"

void remove_link_node(link_list_t *l, link_node_t *n) {
    if(n->pre)
      n->pre->next = n->next;
    else
      l->head = n->next;

    if(n->next)
      n->next->pre = n->pre;
    else
      l->tail = n->pre;

}

void insert_node_before(link_list_t *l, link_node_t *p, link_node_t *n) {
  /* set node new position */
  n->next = p;
  n->pre = p->pre;

  /* then insert before node p */
  if(p->pre)
    p->pre->next = n;
  else
    l->head = n;
  p->pre = n;
}

/*******************************
 * Average Time O(n^2) 
 * Space O(1)
 *******************************/
void SORT_INSERT(link_list_t *list) {
#if 1
  int tmpval;
  link_node_t *cnode; //check node
  link_node_t *snode; //stationary
  link_node_t *tnode; //tmp node

  snode = list->head->next; //start from the second node
  for(; snode!=NULL; snode=snode->next) {
    for(cnode=list->head; cnode!=snode; cnode=cnode->next) {
      if(cnode->val > snode->val) {
        tmpval = snode->val;
        for(tnode=snode; tnode!=cnode; tnode=tnode->pre)
          tnode->val = tnode->pre->val;
        cnode->val = tmpval;
        break;
      }
    }
  }
#else
  int tmpval;
  link_node_t *cnode; //check node
  link_node_t *snode; //stationary
  link_node_t *tnode; //tmp node

  snode = list->head->next; //start from the second node
  while(snode) {
    for(cnode=list->head; cnode!=snode; cnode=cnode->next) {
      if(cnode->val > snode->val) {
        if(cnode->next == snode) {
          exchange_node_val(snode, cnode);
          snode = snode->next;
        } else {
          /* for next loop */
          tnode = snode;
          snode = snode->next;
          remove_link_node(list, tnode); /* remove node */
          insert_node_before(list, cnode, tnode); /* insert before cnode */
        }
        break;
      }
    }
    if(cnode == snode) snode = snode->next; /* no exchage exist in this loop */
  }
#endif
}

void SORT_INSERT_OLD(link_list_t *list) {
  int i;
  link_node_t *n;
  link_node_t *c;
  link_node_t *s = list->head; /* stationary */
  for(i = 1; i < list->len; i++) {
    n = list->head;
    c = s->next;
    while(n != s) {
      if(c->val < n->val) {
        if(n == list->head)
          list->head = c;
        if(c == list->tail)
          list->tail = s;

        s->next = c->next;
        if(c->next)
          c->next->pre = s;

        c->next = n;
        c->pre = n->pre;

        if(n->pre)
          n->pre->next = c;
        n->pre = c;

        break;
      }
      n = n->next;
    }
    if(n == s) {
      if(c->val < n->val) {
        exchange_link_node(list, n, c);
      } else {
        s = s->next;
      }
    }
  }
}

