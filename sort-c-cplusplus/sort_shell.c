#include "list.h"

/*
index 0 1 2 3 4 5 6 7 8 9
numbe 5 1 4 9 3 6 7 5 2 0
  delta = 5
  i = 5
numbe 5 1 4 9 3 6 7 5 2 0
                i(tmp=6)
      j(5>6 false)

numbe 5 1 4 9 3 6 7 5 2 0
                  i(tmp=7)
        j(1)

numbe 5 1 4 9 3 6 7 5 2 0
                    i(tmp=5)
          j(4)

numbe 5 1 4 9 3 6 7 5 2 0
                      i(tmp=2)
            j(9>2 true)
                      N[j+5]=9
j=-2
            N[j+5]=tmp=2

numbe 5 1 4 2 3 6 7 5 9 0
                        i
              j
                        N[j+5]=3
j=-1
              N[j+5]=0

---------------------------------
  delta = 2
numbe 5 1 4 2 3 6 7 5 9 0
          i
      j
         N[j+2]=5
j=-2
      N[j+5]=4

numbe 5 1 4 2 3 6 7 5 9 0
            i
        j(false)

numbe 5 1 4 2 3 6 7 5 9 0
              i tmp=3
          j(4>3)
              N[j+2]=4
j=0
          N[j+2]=3
      j(5>3)
          N[j+2]=5
j=-2
      N[j+2]=3

numbe 3 1 5 2 4 6 7 5 9 0
                i tmp=6
            j(false)
numbe 3 1 5 2 4 6 7 5 9 0
                  i tmp=7
              j(false)
numbe 3 1 5 2 4 6 7 5 9 0
                    i tmp=5
                j(6>5)
            j   5   6

numbe 3 1 5 2 4 6 7 5 9 0
                      i tmp=5
                  j(false)
numbe 3 1 5 2 4 6 7 5 9 0
                        i tmp=0
                    j(true)
                    0   5
                0   6
            0   2
        0   1

------------------------------
  delta=1
numbe 3 0 5 1 4 2 7 6 9 5
        i tmp=0
      j
      0 3
numbe 0 3 5 1 4 2 7 6 9 5
          i tmp=5
        j(false)
numbe 0 3 5 1 4 2 7 6 9 5
            i tmp=1
          j(false)
numbe 0 1 3 4 5 2 7 6 9 5               tmp=4
numbe 0 1 2 3 4 5 7 6 9 5               tmp=2
numbe 0 1 2 3 4 5 7 6 9 5               tmp=7
numbe 0 1 2 3 4 5 6 7 9 5               tmp=6
numbe 0 1 2 3 4 5 6 7 9 5               tmp=9
numbe 0 1 2 3 4 5 5 6 7 9               tmp=5
*/

/*******************************
 * Average Time O(n^1.3)
 * Space O(1)
 *******************************/
void SORT__SHELL(link_list_t *list) {
  link_node_t *n;
  link_node_t *c;
  int d = list->len / 2; /* delta */
  int i, j, tmp;
  while(d >= 1) {
    for(i = d; i < list->len; i++) {
      n = get_list_node(list, i);
      j = i - d;
      c = get_list_node(list, j);
      tmp = n->val;
      while( c && c->val > tmp ) {
        n->val = c->val;
        //c->val = tmp;

        /* check pres */
        n = c;
        j -= d;
        c = get_list_node(list, j);
      }
      n->val = tmp;
    }
    d = d / 2;
  }
}

void SORT_SHELL2(link_list_t *list) {
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
