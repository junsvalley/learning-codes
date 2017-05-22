#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX(a,b)((a)>(b)?(a):(b))
#define __FUNC_ENTER__ {printf("Enter %s\n", __func__);}
#define __FUNC_EXIT__ {printf("Exit  %s\n", __func__);}

typedef struct avl_node {
  int data;
  int high;
  struct avl_node *lson;
  struct avl_node *rson;
}avl_node_t;

typedef struct avl_tree {
  struct avl_node *top;
}avl_tree_t;

void new_avl_node(avl_node_t **node, int x) {
  __FUNC_ENTER__
  *node = calloc(1, sizeof(avl_node_t));
  (*node)->data = x;
  (*node)->high = 0;
  __FUNC_EXIT__
}

void calc_avl_high(avl_node_t *node)
{
  if(node->lson && node->rson) {
    node->high = MAX(node->lson->high, node->rson->high) + 1;
  } else {
    if(node->lson)
      node->high = node->lson->high + 1;
    else if(node->rson)
      node->high = node->rson->high + 1;
    else
      node->high = 0;
  }
}

/* left left */
void rotate_LL(avl_node_t **top) {
  __FUNC_ENTER__
  avl_node_t *oldtop = *top;
  avl_node_t *newtop = oldtop->lson;

  oldtop->lson = newtop->rson;
  calc_avl_high(oldtop);

  newtop->rson = oldtop;
  calc_avl_high(newtop);

  *top = newtop;
  __FUNC_EXIT__
}

/* right right */
void rotate_RR(avl_node_t **top) {
  __FUNC_ENTER__
  avl_node_t *oldtop = *top;
  avl_node_t *newtop = oldtop->rson;

  oldtop->rson = newtop->lson;
  calc_avl_high(oldtop);

  newtop->lson = oldtop;
  calc_avl_high(newtop);

  *top = newtop;
  __FUNC_EXIT__
}

/* left right */
void rotate_LR(avl_node_t **top) {
  __FUNC_ENTER__
  /* first step change to LL */
  /* execute RR for left son */
  rotate_RR(&((*top)->lson));

  /* second step rotate as LL */
  rotate_LL(top);
  __FUNC_EXIT__
}

/* right left */
void rotate_RL(avl_node_t **node) {
  __FUNC_ENTER__
  /* first step change to RR */
  /* execute LL for right son */
  rotate_LL(&((*node)->rson));

  /* second step rotate as RR */
  rotate_RR(node);
  __FUNC_EXIT__
}

void insert_avl_node(avl_node_t **tree, int x) {
  __FUNC_ENTER__
  if(*tree == NULL) {
    new_avl_node(tree, x);
    goto exit_insert;
  }

  if(x < (*tree)->data) {
    insert_avl_node(&((*tree)->lson), x);
    calc_avl_high(*tree);
    printf("node %x 's high is %d\n", (*tree)->data, (*tree)->high);
    if((*tree)->rson)
    {
      if((*tree)->lson->high - (*tree)->rson->high == 2)
      {
        if(x < (*tree)->lson->data)
          rotate_LL(tree);
        else
          rotate_LR(tree);
      }
    }
    else if((*tree)->high == 2)
    {
      if(x < (*tree)->lson->data)
        rotate_LL(tree);
      else
        rotate_LR(tree);
    }
  } else if(x > (*tree)->data) {
    insert_avl_node(&((*tree)->rson), x);
    calc_avl_high(*tree);
    printf("node %x 's high is %d\n", (*tree)->data, (*tree)->high);
    if((*tree)->lson)
    {
      if((*tree)->rson->high - (*tree)->lson->high == 2)
      {
        if(x < (*tree)->rson->data)
          rotate_RL(tree);
        else
          rotate_RR(tree);
      }
    }
    else if((*tree)->high == 2)
    {
      if(x < (*tree)->rson->data)
        rotate_RL(tree);
      else
        rotate_RR(tree);
    }
  } else {
    printf("data %d already exists.\n", x);
  }


exit_insert:
  __FUNC_EXIT__
  return;
}

void traversal(avl_node_t *tree)
{
  if(!tree)return;
  printf("{\nint top = %d;\n", tree->data);
  traversal(tree->lson);
  printf("printf(\"data  %d, - high %d\");\n", tree->data, tree->high);
  traversal(tree->rson);
  printf("}\n");
}

int main() {
  avl_tree_t *avltree = calloc(1, sizeof(avl_tree_t));
  int n[17] = {2,54,312,5,1,454,12,344,546,6,79,43,33,45,21,57, 10};
  int i;

  for(i=0;i<17;i++)
  {
    printf("\n>>>>>>insert %d\n", n[i]);
    insert_avl_node(&avltree->top, n[i]); 
    printf("TOP - data %d, - high %d\n", avltree->top->data, avltree->top->high);
    traversal(avltree->top);
  }

  //traversal(avltree->top);
  return 0;
}
