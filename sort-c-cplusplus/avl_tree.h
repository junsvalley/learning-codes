#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#define MAX(a,b)((a)>(b)?(a):(b))
#define __FUNC_ENTER__ //{printf("Enter %s\n", __func__);}
#define __FUNC_EXIT__ //{printf("Exit  %s\n", __func__);}

typedef struct avl_node {
  int data;
  int high;
  struct avl_node *lson;
  struct avl_node *rson;
}avl_node_t;

typedef struct avl_tree {
  struct avl_node *top;
}avl_tree_t;

void new_avl_node(avl_node_t **node, int x);
void calc_avl_high(avl_node_t *node);
void rotate_LL(avl_node_t **top); /* left left */
void rotate_RR(avl_node_t **top); /* right right */
void rotate_LR(avl_node_t **top); /* left right */
void rotate_RL(avl_node_t **node); /* right left */
void insert_avl_node(avl_node_t **tree, int x);
void traversal(avl_node_t *tree);

#endif
