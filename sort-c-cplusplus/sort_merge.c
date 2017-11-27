#include "list.h"

void link_nodes_merge(link_list_t *l, int s, int m, int e) {
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

/*******************************
 * Average Time O(nlog2n)
 * Space O(1)
 *******************************/
void SORT__MERGE(link_list_t *list) {
  int len = list->len;
  int i = 1, j, k;
  int s, m, e;/* start, middle, end */
  int merge_len = 2;
  while( merge_len / 2 < len ) {
    s = 0;
    m = merge_len / 2 - 1;
    e = merge_len - 1;
    if(e >= len)
      e = len - 1;

    while( e < len ) {
      printf(" 1 ---> index: start %d, middle %d, end %d\n", s, m, e);
      link_nodes_merge(list, s, m, e);
      s += merge_len;
      m += merge_len;
      e += merge_len;
      //print_link_list(list);
    }
    if( s < len && ( len - s ) > ( merge_len / 2 )) {
      printf(" 2 ---> index: start %d, middle %d, end %d\n", s, m, len - 1);
      link_nodes_merge(list, s, m, len - 1);
      //print_link_list(list);
    }
    merge_len *= 2;
  }
}

void list_merge2(link_list_t *list, int startIdx, int mergeLen) {
  int endIdx = startIdx+mergeLen-1;
  if(endIdx>=list->len) endIdx = list->len-1;
  printf("end index %d\n", endIdx);
  link_nodes_merge(list, startIdx, startIdx+mergeLen/2-1, endIdx);
}

void SORT_MERGE2(link_list_t *list) {
  printf("list length %d\n", list->len);
  int merge_len = 2;
  int start_idx;
  int remain_len;
  for(; (merge_len/2)<list->len; merge_len*=2) {
    start_idx = 0;
    remain_len = list->len;
    while(remain_len > (merge_len/2)) {
      printf("start index %d, remain len %d ", start_idx, remain_len);
      list_merge2(list, start_idx, merge_len);
      remain_len -= merge_len;
      start_idx += merge_len;
    }
  }
}

