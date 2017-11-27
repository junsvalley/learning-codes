#include "list.h"

#define MAX_NUMERAL_BUCKETS 10

typedef struct {
  int number;
} numeral_bucket;

void build_numeral_buckets() {
}

/*******************************
 * Average Time O(d(r+n))
 * Space O(rd+n)
 *******************************/
void SORT__RADIX(link_list_t *list) {
#if 0
  link_node_t *node = list->head;
  while(node) {
    bucket[node->data%10][idx] = node->data;
    node = node->next;
  }

  node = list->head;
  while(bucket_index<MAX_NUMERAL_BUCKETS) {
    while(!is_bucket_empty()) {
      node->data = bucket[bucket_index][idx];
      node = node->next;
    }
  }
#endif






}

