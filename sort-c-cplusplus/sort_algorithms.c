#include "list.h"



/******************************************************************************************
 * Average Time O(n^2)
 * Space O(1)
 ******************************************************************************************/
void __SORT_BUBBLE(link_list_t *list) {
  int i;
  link_node_t *n = list->head;
  link_node_t *c;
  for( ; n; n=n->next) {
    c = n->next;
    for( ; c; c=c->next) {
      if(c->val < n->val) {
        exchange_node_val(n, c);
      }
    }
  }
}


/******************************************************************************************
 * Average Time O(n^2) 
 * Space O(1)
 ******************************************************************************************/
void __SORT_INSERT(link_list_t *list) {
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
}

/******************************************************************************************
 * Average Time O(nlog2n)
 * Space O(1)
 ******************************************************************************************/
 void __link_nodes_merge(link_list_t *l, int s, int m, int e) {
  int len = e - s + 1;
  if(len == 1)
    return;

  int *vals = calloc(sizeof(int) * len, 1);
  int k = 0; /* vals index */

  /* first list start */
  link_node_t *fn = get_list_node(l, s);
  link_node_t *tn = fn;
  int i = 0; /* index for first list in vals */
  int len1 = m - s + 1;

  link_node_t *mn = get_list_node(l, m);
  link_node_t *nn = mn->next; /* next list first */
  int j = len1; /* index for next list in vals */

  while( k < len ) {
    if((i == len1) || (j < len && fn->val > nn->val)) {
      vals[k] = nn->val;
      nn = nn->next;
      j++;
    } else if((j == len) || (i < len1 && fn->val <= nn->val)) {
      vals[k] = fn->val;
      fn = fn->next;
      i++;
    }

    k++;
  }

  i = 0;
  while(i < len) {
    tn->val = vals[i++];
    tn = tn->next;
  }

  free(vals);
}

void __list_merge(link_list_t *list, int startIdx, int mergeLen) {
  int endIdx = startIdx+mergeLen-1;
  if(endIdx>=list->len) endIdx = list->len-1;
  printf("end index %d\n", endIdx);
  __link_nodes_merge(list, startIdx, startIdx+mergeLen/2-1, endIdx);
}

void __SORT_MERGE(link_list_t *list) {
  printf("list length %d\n", list->len);
  int merge_len = 2;
  int start_idx;
  int remain_len;
  for(; (merge_len/2)<list->len; merge_len*=2) {
    start_idx = 0;
    remain_len = list->len;
    while(remain_len > (merge_len/2)) {
      printf("start index %d, remain len %d ", start_idx, remain_len);
      __list_merge(list, start_idx, merge_len);
      remain_len -= merge_len;
      start_idx += merge_len;
    }
  }
}

/******************************************************************************************
 * Average Time O(nlog2n)
 * Space O(nlog2n)
 ******************************************************************************************/
int __link_list_split(link_list_t *l, int low, int high) {
  link_node_t *pn; /* pivot node */
  link_node_t *hn; /* high node */
  link_node_t *ln; /* low node */
  pn = get_list_node(l, low);

  while(low < high) {
    hn = get_list_node(l, high);
    while(low < high && pn->val <= hn->val) {
      hn = hn->pre;
      high--;
    }
    exchange_link_node(l, pn, hn);

    ln = get_list_node(l, low);
    while(low < high && pn->val >= ln->val) {
      ln = ln->next;
      low++;
    }
    exchange_link_node(l, ln, pn);
  }
  return low;
}

void __link_quick_sort(link_list_t *l, int low, int high) {
  if(low < high){
    int pivot = __link_list_split(l, low, high);
    __link_quick_sort(l, low, pivot - 1);
    __link_quick_sort(l, pivot + 1, high);
  }
}


void __SORT__QUICK(link_list_t *list) {
  __link_quick_sort(list, 0, list->len - 1);
}


/******************************************************************************************
 * Average Time O(n^2)
 * Space O(1)
 ******************************************************************************************/
void __SORT_SIMPLE_SELECT(link_list_t *list) {
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


/******************************************************************************************
 * Average Time O(n^1.3)
 * Space O(1)
 ******************************************************************************************/
void __SORT_SHELL(link_list_t *list) {
  link_node_t *current_node;
  int current_index;
  link_node_t *previous_node;
  int previous_index;

  int delta = list->len / 2;
  for(; delta>=1; delta/=2) {
    current_index = delta; /* index start from delta*/ 
    for(; current_index<list->len; current_index++) {
      current_node = get_list_node(list, current_index);

      previous_index = current_index - delta;
      previous_node = get_list_node(list, previous_index);

      while(current_node->val < previous_node->val) {
        exchange_node_val(previous_node, current_node);

        previous_index -= delta;
        if(previous_index >= 0) {
          current_node = previous_node;
          previous_node = get_list_node(list, previous_index);
        }
      }
    }
  }
}


/******************************************************************************************
 * Average Time O(nlog2n)
 * Space O(1)
 ******************************************************************************************/
 static int __heap_count = 0;
 
 void __build_min_heap(link_list_t *list, int node_index, int len /* length to check */) {
  int left_index =  (node_index + 1) * 2 - 1;
  int right_index = (node_index + 1) * 2;

  link_node_t *parent_node = NULL;
  link_node_t *left_node = NULL;
  link_node_t *right_node = NULL;

  parent_node = get_list_node(list, node_index);
  link_node_t *min_node = parent_node;
  int min_index = node_index;

  if(left_index < len){
    left_node = get_list_node(list, left_index);
    if(parent_node->val > left_node->val) {
      min_node = left_node;
      min_index = left_index;
    }
  }

  if(right_index < len) {
    right_node = get_list_node(list, right_index);
    if(min_node->val > right_node->val) {
      min_node = right_node;
      min_index = right_index;
    }
  }

  if(min_node != parent_node) {
    /* select smallest value to top */
    int tv = parent_node->val;
    parent_node->val = min_node->val;
    min_node->val = tv;
    __heap_count++;

    /* now the min index stored the bigger value */
    __build_min_heap(list, min_index, len); 
  }
}

void __SORT_HEAP(link_list_t *list) {
  if(list->len == 1)
    return;

  int i = list->len/2 - 1;
  while(i>=0){
    __heap_count++;
    __build_min_heap(list, i, list->len);
    i--;
  }

  link_node_t *inode = NULL;
  link_node_t *fnode = list->head; /* first node */

  int tv;
  for(i=list->len-1;i>0;i--){
    inode = get_list_node(list, i);
    tv = inode->val;
    inode->val = fnode->val;
    fnode->val = tv;

    __heap_count++;
    __build_min_heap(list, 0, i);
  }

  int ideal_cnt = list->len*(log(list->len)/log(2));
}
